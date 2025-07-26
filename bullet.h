#pragma once
#include "gameobject.h"

class Bullet : public GameObject
{
private:
	Vector2D velocity;
	float timer;
	Circle2D collisionShape;
	int bulletDuration;
public:
	void Update(float frametime);
	Bullet();
	void Initialise(Vector2D spawnPosition, float shipAngle, ObjectType objType);
	IShape2D& GetShape();
	void HandleCollision( GameObject& other );
};

//bullets used by player and enemy ships.
//objType is passed in initialise to see if its an enemy or friendly bullet