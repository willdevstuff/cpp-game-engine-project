#pragma once
#include "gameobject.h"

class Missile : public GameObject
{
private:
	Vector2D velocity;
	float timer;
	Circle2D collisionShape;
	int bulletDuration;
	GameObject* pTarget;
	ObjectManager* om;
public:
	void Update(float frametime);
	Missile();
	void Initialise(Vector2D spawnPosition, GameObject* target, ObjectManager* pOM, SoundSystem* soundSys);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};

//missile fired by enemies that chases the player and explodes on impact