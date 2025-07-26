#pragma once
#include "mydrawengine.h"
#include "mysoundengine.h"
#include "ObjectManager.h"
#include "SoundSystem.h"
enum class ObjectType{ROCK, SPACESHIP, BULLET, ENEMYBULLET, CURSOR, EXPLOSION, POWERUP, POWERUP_ATK, POWERUP_LIFE, ENEMYSHIP, MISSILE};
// objectype allows for collision handling to work without having to include the relevant classes

class GameObject
{
protected:
	Vector2D position;
	float angle;
	float scale; 
	float transparency;
	PictureIndex LoadImage(const wchar_t* imageName);
	SoundSystem* p_soundSystem;
	ObjectType myType;
private:
	PictureIndex image;
public:
	bool isActive;
	virtual void Render();
	virtual Vector2D GetPosition();
	virtual float GetPositionX();
	virtual float GetPositionY();
	virtual void HandleMessage(ObjectManager::Message msg);
	virtual void Update(float frametime) = 0; // =0 means pure virtual, meaning no definition required
	GameObject(ObjectType objType); // Constructor 
	virtual ~GameObject(); // Destructor
	virtual IShape2D& GetShape() = 0; // returns pointer to an IShape2D object
	virtual void HandleCollision( GameObject& other ) = 0;
	bool IsActive();
	void Deactivate();
	ObjectType GetType();
};

// base gameobject class, has a variety of functions and variable