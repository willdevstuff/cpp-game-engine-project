#include "Missile.h"
#include "Explosion.h"
// missiles shot by enemies at the player
void Missile::Update(float frametime)
{
	// point to playership
	const float TURNRATE = 5.0f;
	Vector2D direction = pTarget->GetPosition() - position;
	float desiredAngle = direction.angle();

	float angleDifference = angle = desiredAngle;
	if (angleDifference > 3.141f) angleDifference -= 6.242f;
	if (angleDifference < -3.141f) angleDifference += 6.242f;

	if (angleDifference > 0) angle = angle - TURNRATE * frametime;
	else angle = angle + TURNRATE * frametime;

	// move towards player
	velocity.setBearing(angle, 400);
	position += velocity * frametime;

	collisionShape.PlaceAt(position, 15);
}

Missile::Missile():GameObject(ObjectType::MISSILE)
{
	scale = 1.0f;
	transparency = 0.0f;
	isActive = true;
	LoadImage(L"assets/missile.bmp");
}

void Missile::Initialise(Vector2D spawnPosition, GameObject* target, ObjectManager* pOM, SoundSystem* soundSys)
{
	pTarget = target;
	position = spawnPosition;
	om = pOM;
	p_soundSystem = soundSys;

}

IShape2D& Missile::GetShape()
{
	return collisionShape;
}

void Missile::HandleCollision(GameObject& other)
{
	if (other.GetType() == ObjectType::SPACESHIP) // deactive if touch spaceship (even if phased) - cause otherwise it looks strange
	{
		Deactivate();
	}

	if (other.GetType() == ObjectType::BULLET)  // explode and destroy if shot
	{
		Explosion* pExplosion = new Explosion();
		pExplosion->Initialise(position, 5.0, 0.1, p_soundSystem, 1);
		if (om)
		{
			om->AddObject(pExplosion);
		}

		ObjectManager::Message m;
		m.type = EventType::ENEMY_DOWN;
		m.location = position;
		m.pSource = this;
		om->SendMsg(m);
		Deactivate();
	}
}


