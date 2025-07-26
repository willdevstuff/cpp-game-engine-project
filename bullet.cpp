#include "bullet.h"
//Bullet used by enemies and the player

Bullet::Bullet():GameObject(ObjectType::BULLET) {
	scale = 1.0f;
	angle = 0.0f;
	transparency = 0.0f;
	velocity.set(0, 0);
	position.set(0, 0);
	timer = 0;
}

void Bullet::HandleCollision(GameObject& other)
{
	if (other.GetType() == ObjectType::ROCK || other.GetType() == ObjectType::ENEMYSHIP)
	{
		Deactivate();
	}
}

IShape2D& Bullet::GetShape() 
{
	return collisionShape;
}

void Bullet::Initialise(Vector2D spawnPosition, float shipAngle, ObjectType objType) { // pass in objectType to set certain variables
	isActive = true;
	position = spawnPosition;
	timer = 0;
	myType = objType;
	
	angle = shipAngle;
	velocity.setBearing(angle, 400.0f); //400 is ship speed

	if (myType == ObjectType::BULLET) // player bullets are purple and bigger
	{
		scale = 2.0f;
		LoadImage(L"assets/purpbullet.bmp");
		bulletDuration = 10;
	}
	if (myType == ObjectType::ENEMYBULLET) // enemy bullets are default colour and smaller
	{
		LoadImage(L"assets/bullet.bmp");
		bulletDuration = 5;
	}

}

void Bullet::Update(float frameTime) {
	
	position = position + velocity * frameTime;  // go forth
	timer += frameTime;

	 if (timer >= 10) 
		{
		 Deactivate();
	 }
	 switch (myType)
	 {
	 case ObjectType::BULLET:
		 collisionShape.PlaceAt(position, 10); // needs bigger collision if bigger
		 break;
	 case ObjectType::ENEMYBULLET:
		 collisionShape.PlaceAt(position, 5);
		 break;
	 }
}
