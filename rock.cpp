#include "rock.h"

Rock::Rock() :GameObject(ObjectType::ROCK)
{
	scale = 1.0f;
	angle = 0.0f;
	transparency = 0.0f;
	velocity.set(0, 0);
	position.set(0, 0);
	randNumber = rand() % 4;
	randSpin = rand() % 1;
	randAng = rand() % 628 / 100.0;
	randVelo = rand() % 100 + 40;
	health = 3;
	collisionSize = 60;
}

void Rock::HandleCollision( GameObject& other )
{
	if (other.GetType() == ObjectType::BULLET) // || other.GetType() == ObjectType::ENEMYBULLET)   // dont let enemies destroy rocks... 
		{
			--health;
			p_soundSystem->PlayGetHit();

			if (health <= 0) 
			{
				/*Explosion* pExplosion = new Explosion();
				pExplosion->Initialise(position, 5.0, 0.1, p_soundSystem, 2);
				if (om)
				{
					om->AddObject(pExplosion);
				}*/  //  the smoke puff looks rly ugly :(

				ObjectManager::Message m;
				m.type = EventType::ROCK_DESTROYED;
				m.location = position;
				m.pSource = this;
				om->SendMsg(m);
				Deactivate();

				for (int i = 0; i < 3; i++)
				{
					Rock* pRock = new Rock();
					Vector2D pos = position + Vector2D(rand() % 150 - 75, rand() % 150 - 75);
					//Vector2D vel(rand() % 200 - 100, rand() % 200 - 100);
					pRock->Initialise(pos, om, p_soundSystem, scale / 2);
					om->AddObject(pRock);
				}
			}
		}

	if (other.GetType() == ObjectType::ROCK || other.GetType() == ObjectType::ENEMYSHIP) // bouncing off rocks code
	{
		Vector2D normal = (position - other.GetPosition()).unitVector();
		if (normal * velocity < 0)
		{
			velocity = velocity - 2 * (velocity * normal) * normal;
			velocity = 0.5f * velocity;
		}
	}

}
void Rock::Initialise(Vector2D spawnPosition, ObjectManager* ObjectManager, SoundSystem* pSoundSystem, float theScale)
{
	if (theScale > 0.2f) // dont initialise beyond the small 0.2 scaled rock
	{
		if (theScale == 1.0f) health = 3; // big rocks have 3 health
		if (theScale == 0.5f) health = 2; // medium ones have 2
		if (theScale == 0.25f) health = 1; // smallest have 1

		collisionSize = 60 * theScale; // scale collision size to rock size
		scale = theScale; // set scale

		p_soundSystem = pSoundSystem;
		om = ObjectManager;
		isActive = true;
		velocity.setBearing(randAng, randVelo); 


		switch (randNumber)  // load random image from the 4 rock images
		{
		case 0: LoadImage(L"assets/rock1.bmp"); break;
		case 1: LoadImage(L"assets/rock2.bmp"); break;
		case 2: LoadImage(L"assets/rock3.bmp"); break;
		case 3: LoadImage(L"assets/rock4.bmp"); break;
		}
		position = spawnPosition;
	}
	else
	{
		Deactivate();
	}
}

IShape2D& Rock::GetShape() 
{
	return collisionShape;
}

void Rock::Update(float frameTime) {

	position = position + velocity * frameTime;  // go forth

	switch (randSpin)  // randomly decide to spin left or right
	{
	case 0: angle = angle + 1 * frameTime; break;
	case 1: angle = angle - 1 * frameTime; break;
	}

	collisionShape.PlaceAt(position, collisionSize);

	float screenWidth = MyDrawEngine::GetInstance()->GetViewport().GetBottomRight().XValue;
	float screenHeight = MyDrawEngine::GetInstance()->GetViewport().GetTopRight().YValue;
	// wraparound the screen
	if (position.XValue > screenWidth) {position.XValue = -screenWidth;}
	if (position.XValue < -screenWidth) {position.XValue = screenWidth;}
	if (position.YValue > screenHeight) {position.YValue = -screenHeight;}
	if (position.YValue < -screenHeight) {position.YValue = screenHeight;}

}

