#include "ObjectManager.h"
#include "gametimer.h"
#include "gamecode.h"
#include "gameobject.h"
#include "LevelManager.h"


void ObjectManager::UpdateAll(float frameTime)
{
	for (GameObject* nextObj : pObjectList)
	{
		if (nextObj->isActive)
			nextObj->Update(frameTime);
	}
}

void ObjectManager::SendMsg(Message msg)
{
	for (GameObject* pNext : pObjectList)
	{
		if (pNext)
			pNext->HandleMessage(msg);  // let gameobjects handle messages
	}
	m_lvlManager->HandleMessage(msg);  // let lvlmanager handle messages
	m_gameRef->HandleMessage(msg); // let the gamecode handle messages
}
void ObjectManager::SetLvlManager(LevelManager* lvlManager)
{
	m_lvlManager = lvlManager;
}
void ObjectManager::SetGameCode(Game* gameRef)
{
	m_gameRef = gameRef;
}
void ObjectManager::HandleMessage(Message msg) // this isn't actually called because it caused a crash - so rocks remain between levels - this works well actually
{
	if (msg.type == EventType::LEVEL_START)
	{
		for (GameObject*& pNext : pObjectList) {
			if (pNext->GetType() != ObjectType::CURSOR ||pNext->GetType() != ObjectType::SPACESHIP)
			{
				delete pNext;
				pNext = nullptr;
			}
		}
		pObjectList.remove(nullptr);
	}
}
void ObjectManager::CheckAllCollisions()  // handle all collisions between gameobjects
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;
	for(it1 = pObjectList.begin(); it1!=pObjectList.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != pObjectList.end(); it2++)
		{
			if ( ((*it1) && (*it2)) &&
				 ((*it1)->IsActive() && (*it2)->IsActive()) &&
				 ((*it1)->GetShape().Intersects((*it2)->GetShape())))
			{
				(*it1)->HandleCollision( (**it2 )); // two asterisks because deferencing the iterator gives a pointer... (1 asterisk) 
				(*it2)->HandleCollision( (**it1 )); // and another will desference the pointer to get straight to the object.
			}
		}
	}
}

void ObjectManager::RenderAll() // call all render functions from gameobjects
{
	for (GameObject* nextObj : pObjectList) {
		if (nextObj->isActive)
		nextObj->Render();
	}
	MyDrawEngine::GetInstance()->WriteInt(300, 50, pObjectList.size(), MyDrawEngine::GREEN); // write number of gameobjects - to prove deletion works
}

void ObjectManager::AddObject(GameObject* pNewObject)
{
	pObjectList.push_back(pNewObject);
}

void ObjectManager::DeleteAll()  // delete all objs from list and set null pointers
{
	for (GameObject* nextObj : pObjectList) 
	{
		delete nextObj;
		nextObj = nullptr;
	}
	pObjectList.clear();
}

void ObjectManager::DeleteInactive() {
	for (GameObject*& pNext : pObjectList) {
		if (!pNext->IsActive()) 
		{ 
			delete pNext; 
			pNext = nullptr; 
		} 
	}
	pObjectList.remove(nullptr);
}
