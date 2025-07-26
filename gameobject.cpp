#include "gameobject.h"


PictureIndex GameObject::LoadImage(const wchar_t* imageName)
{
	image = MyDrawEngine::GetInstance()->LoadPicture(imageName);
	return image; // set AND return image, so if using multiple times, last one used will be the default 
}

void GameObject::Render()
{
	MyDrawEngine::GetInstance()->DrawAt(position, image, scale, angle, transparency); // use it to draw image taking 5 parameters
}

void GameObject::HandleMessage(ObjectManager::Message msg)
{
	
}
bool GameObject::IsActive() {
	return isActive;
}
Vector2D GameObject::GetPosition()
{
	return this->position;
}
float GameObject::GetPositionX()
{
	return this->position.XValue;
}
float GameObject::GetPositionY()
{
	return this->position.YValue;
}
void GameObject::Deactivate() {
	isActive = false;
}

ObjectType GameObject::GetType() 
{
	return myType;
}

GameObject::GameObject(ObjectType objType):myType(objType) // constant initialization done here (allowed to 'change' the const here) // i changed it from const so powerups can be varied
{
	
}

GameObject::~GameObject()
{
}
