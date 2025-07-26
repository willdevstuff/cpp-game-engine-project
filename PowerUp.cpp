#include "PowerUp.h"

//powerups for player to pickup 

void PowerUp::Update(float frametime)
{
	collisionShape.PlaceAt(position, 30);

}

PowerUp::PowerUp() : GameObject(ObjectType::POWERUP)
{
	scale = 1.0f;
	angle = 0.0f;
	transparency = 0.0f;
}

void PowerUp::HandleCollision(GameObject& other)
{
	//deletion is handled elsewhere (in the spaceship class)
}

void PowerUp::Initialise(Vector2D spawnPosition, ObjectManager* ObjectManager, SoundSystem* pSoundSystem, ObjectType objType) // objtype sets the type of powerup
{
	position = spawnPosition;
	om = ObjectManager;
	p_soundSystem = pSoundSystem;
	myType = objType; // set the type to the type that's passed in. either LIFE or ATK
	isActive = true;
	switch (myType) 
	{
		case ObjectType::POWERUP_ATK:
			LoadImage(L"assets/atkcrate.bmp");  //image for attack powerup
			break;

		case ObjectType::POWERUP_LIFE:
			LoadImage(L"assets/lifecrate.bmp"); // image for extra life powerup
			break;
	}
}

IShape2D& PowerUp::GetShape()
{
	return collisionShape;
}
