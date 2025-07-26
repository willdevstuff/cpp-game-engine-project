#pragma once
#include "gameobject.h"

class PowerUp : public GameObject
{
private:
	ObjectManager* om;
	Vector2D velocity;
	Circle2D collisionShape;
public:
	void Update(float frametime);
	PowerUp();
	void Initialise(Vector2D spawnPosition, ObjectManager* ObjectManager, SoundSystem* pSoundSystem, ObjectType objType);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

// class for powerup objects. objType determines the type of powerup