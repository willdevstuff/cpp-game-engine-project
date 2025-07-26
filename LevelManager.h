#pragma once
#include "mydrawengine.h"
#include "ObjectManager.h"
#include "SoundSystem.h"
class Spaceship;

// Level Manager. Handles player stats, drawing info to screen, spawning enemies for each level, and other events.
// It is used by gamecode to make the game work.
class LevelManager
{
private:
	int levelNumber;
	int score;
	float endLevelTimer;
	int numEnemies;
	int playerLives;
	float m_framesToFreeze;
	PictureIndex shipImage;
	ObjectManager* m_objManager;
	SoundSystem* m_soundSystem;
	Spaceship* pship;
	bool isOver;
public:
	void StartLevel();
	void SetUp(ObjectManager* pObjManager, SoundSystem* pSoundSystem);
	void Render();
	void Update(float frameTime);
	void AddScore(int scoreGained);
	void EnemyDead();
	void PlayerDead();
	void HandleMessage(ObjectManager::Message msg);
	void GameOver();
};