#include "MousePointer.h"
#include "myinputs.h"
//cursor for player to use
void MousePointer::Initialise() 
{
	position.set(0, 0);
	LoadImage(L"assets/crosshairblue.bmp"); // default to blue
	isActive = true;
	red = 0;
}

void MousePointer::Update(float frametime)
{
	red--;
	if (red <= 0)
	{
		LoadImage(L"assets/crosshairblue.bmp"); // blue default
	}
	else
	{
		LoadImage(L"assets/crosshairred.bmp"); // red state if hovering over enemy/rock
	}

	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleMouse();

	position.XValue = position.XValue + pInputs->GetMouseDX();
	position.YValue = position.YValue - pInputs->GetMouseDY();

	if (position.XValue > 1800) position.XValue = 1800; // clamp so it cant go offscreen
	if (position.XValue < -1800) position.XValue = -1800;
	if (position.YValue > 1000) position.YValue = 1000;
	if (position.YValue < -1000) position.YValue = -1000;

	angle = angle + 1 * frametime;
	collisionShape.PlaceAt(position, 60);

	if (pInputs->IfMouseNewLeftDown())
	{
		//shooting is handled inside the spaceship class
	}

}

MousePointer::MousePointer():GameObject(ObjectType::CURSOR)
{
	scale = 1.0f;
	angle = 0.0f;
	transparency = 0.0f;
}

void MousePointer::HandleCollision(GameObject& other)
{
	if (other.GetType() == ObjectType::ROCK || other.GetType() == ObjectType::ENEMYSHIP || other.GetType() == ObjectType::MISSILE)
	{
		red = 3;  // if hovering over enemy or rock, set cursor to be red
	}
}

IShape2D& MousePointer::GetShape()
{
	return collisionShape;
}