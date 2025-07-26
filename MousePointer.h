#pragma once
#include "gameobject.h"

class MousePointer : public GameObject
{
private:
	Circle2D shape;
	Circle2D collisionShape;
	int red;
public:
	void Initialise();
	void Update(float frametime);
	MousePointer();
	void HandleCollision(GameObject& other);
	IShape2D& GetShape();
};

// mousepointer with custom icon - it spins around and turns red when hovering over enemy objects or rocks