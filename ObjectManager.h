#pragma once
#include "mydrawengine.h"
#include "Shapes.h"
#include <list>
#include "gametimer.h"
enum class EventType { OBJECT_DESTROYED, EXPLOSION, BULLET_FIRED, LEVEL_START, ROCK_DESTROYED, PLAYERSHIP_DOWN, ENEMY_DOWN, GAME_OVER, GAME_WON, EXTRA_LIFE }; // types of event to handle
class GameObject;  // <- soft dependancy  (dont need to anything ABOUT the class. just that it exists)
class LevelManager;
class Game;

class ObjectManager
{
	private:
		std::list<GameObject*>pObjectList; // create the list of objects to iterate through when rendering/updating etc
		LevelManager* m_lvlManager;
		Game* m_gameRef;

	public:
		struct Message  // messages to be used by messaging system
		{
			EventType type;
			Vector2D location;
			GameObject* pSource;
			int otherData;
		};
		void AddObject(GameObject* pNewObject);
		void UpdateAll(float frametime);
		void RenderAll();
		void DeleteInactive();
		void DeleteAll();
		void CheckAllCollisions();
		void SendMsg(Message msg);
		void SetLvlManager(LevelManager* lvlManager);
		void SetGameCode(Game* gameRef);
		void HandleMessage(Message msg);
};
