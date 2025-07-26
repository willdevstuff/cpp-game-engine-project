#pragma once
#include "gameobject.h"

class Rock : public GameObject
{
private:
	ObjectManager* om;
	Vector2D velocity;
	int randNumber;
	int randSpin;
	int randVelo;
	float randAng;
	Circle2D collisionShape;
	int health;
	int collisionSize;
public:
	void Update(float frametime);
	Rock();
	void Initialise(Vector2D spawnPosition, ObjectManager* ObjectManager, SoundSystem* pSoundSystem, float theScale);
	IShape2D& GetShape();
	void HandleCollision( GameObject& other );
};
// rocks that float around the screen, bounce off each other and kill the player on impact. they also block enemy bullets