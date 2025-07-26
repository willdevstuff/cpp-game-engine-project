#pragma once
#include "gameobject.h"
#include "spaceship.h"

class EnemyShip : public GameObject
{
private:
	Vector2D velocity;
	Vector2D speed;
	ObjectManager* pObjectManager;
	Spaceship* p_PlayerShip;
	Vector2D currentPos;
	int health;
	float shotTimer;
	float shotCooldown;
	float bonusShotCooldown;
	float bonusShotTimer;
	Circle2D collisionShape;
	int m_shipLevel;
public:
	void Update(float frametime);
	EnemyShip(int shipLevel);
	void Initialise(Vector2D spawnPosition, ObjectManager* pObjMan, SoundSystem* pSoundSystem, Spaceship* pPlayerShip);
	IShape2D& GetShape();
	void HandleCollision(GameObject& other);
};
// class for enemy ships/turrets. the 'int shiplevel' determines the type of ship that will spawn