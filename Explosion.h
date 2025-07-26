#pragma once
#include "gameobject.h"

class Explosion : public GameObject
{
private:
	PictureIndex imageArray[8];
	float currentImage;
	Circle2D collisionShape;
	float m_speed;
	Vector2D velocity;
public:
	Explosion();
	void Initialise(Vector2D startPos, float size, float speed, SoundSystem* soundSystem, int type);
	void Render() override;
	void Update(float frametime);
	IShape2D& GetShape();
	void HandleCollision(GameObject& obj);
	void SetVelocity(Vector2D v);
};

//explosion animation object