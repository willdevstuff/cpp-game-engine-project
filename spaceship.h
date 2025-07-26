#pragma once
#include "gameobject.h"
#include "MousePointer.h"
#include "bullet.h"
#include "Explosion.h"

class Spaceship : public GameObject
{
private:
	Vector2D velocity;
	Vector2D speed;
	ObjectManager* pObjectManager;
	bool invincible;
	float invulTimer;
	bool phased;
	float phaseTimer;
	float phaseCooldown;
	float shotTimer;
	float shotCooldown;
	float powerUpDuration;
	Circle2D collisionShape;
	MousePointer* pMP;
	PictureIndex invulImage;
	PictureIndex plasmaImage;
public:
	void Update(float frametime);
	Spaceship();
	void Render() override;
	void Initialise(Vector2D spawnPosition, ObjectManager* pObjMan, SoundSystem* pSoundSystem, MousePointer* pMousePointer);
	IShape2D& GetShape();
	void HandleCollision( GameObject& other );
	void Respawn();
	void PhaseShift();
};

// the player's ship