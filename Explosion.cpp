#include "Explosion.h"
// explosion object 
Explosion::Explosion():GameObject(ObjectType::EXPLOSION)
{
	position.set(0, 0);
	isActive = false;
	velocity.set(0, 0);
}

void Explosion::Initialise(Vector2D startPos, float size, float speed, SoundSystem* soundSystem, int type)  // type allows for explosions of fire or smoke
{
	p_soundSystem = soundSystem;
	position = startPos;
	isActive = true;
	currentImage = 0;
	scale = size;
	m_speed = speed;

	p_soundSystem->PlayExplosion();

	if (type == 1) // load blast explosion
	{
		imageArray[0] = LoadImage(L"assets/explosion1.bmp");
		imageArray[1] = LoadImage(L"assets/explosion2.bmp");
		imageArray[2] = LoadImage(L"assets/explosion3.bmp");
		imageArray[3] = LoadImage(L"assets/explosion4.bmp");
		imageArray[4] = LoadImage(L"assets/explosion5.bmp");
		imageArray[5] = LoadImage(L"assets/explosion6.bmp");
		imageArray[6] = LoadImage(L"assets/explosion7.bmp");
		imageArray[7] = LoadImage(L"assets/explosion8.bmp");
	}

	if (type == 2) // load smoke puff
	{
		imageArray[0] = LoadImage(L"assets/puff1.bmp");
		imageArray[1] = LoadImage(L"assets/puff2.bmp");
		imageArray[2] = LoadImage(L"assets/puff3.bmp");
		imageArray[3] = LoadImage(L"assets/puff4.bmp");
		imageArray[4] = LoadImage(L"assets/puff5.bmp");
		imageArray[5] = LoadImage(L"assets/puff6.bmp");
		imageArray[6] = LoadImage(L"assets/puff7.bmp");
		imageArray[7] = LoadImage(L"assets/puff8.bmp");
	}
}

void Explosion::Render()
{
	if (isActive)
	{
		MyDrawEngine::GetInstance()->DrawAt(position, imageArray[(int)currentImage], scale, 0, 0); // override render and draw animation
	}
}

void Explosion::Update(float frametime) // move through images in array
{
	currentImage += m_speed;

	if (currentImage >= 8)
	{
		Deactivate();
	}
	position += velocity * frametime;
}

IShape2D& Explosion::GetShape()
{
	collisionShape.PlaceAt(position, 10);
	return collisionShape;
}

void Explosion::HandleCollision(GameObject& obj)
{

}

void Explosion::SetVelocity(Vector2D v)
{
	velocity = v;
}