#include "LevelManager.h"
#include "ObjectManager.h"
#include "rock.h"
#include "PowerUp.h"
#include "spaceship.h"
#include "MousePointer.h"
#include "EnemyShip.h"
#include "Missile.h"
// Level Manager. Handles player stats, drawing info to screen, spawning enemies for each level, and other events

void LevelManager::SetUp(ObjectManager* pObjManager, SoundSystem* pSoundSystem)
{
	shipImage = MyDrawEngine::GetInstance()->LoadPicture(L"assets/ship.bmp");
	playerLives = 4;
	endLevelTimer = 5.0f;
	m_objManager = pObjManager;
	m_soundSystem = pSoundSystem;
	levelNumber = 0;
	m_framesToFreeze = 0;
	isOver = false;

	m_soundSystem->SetEngineVolume(1); // its quite loud otherwise

	MousePointer* pMousePointer = new MousePointer();
	pMousePointer->Initialise();
	m_objManager->AddObject(pMousePointer);

	pship = new Spaceship();
	pship->Initialise(Vector2D(0, 0), m_objManager, m_soundSystem, pMousePointer);
	m_objManager->AddObject(pship);
}
void LevelManager::StartLevel() 
{
	isOver = false;
	levelNumber++;

	int randX;
	int randY;

	int screenWidth = MyDrawEngine::GetInstance()->GetViewport().GetBottomRight().XValue;
	int screenHeight = MyDrawEngine::GetInstance()->GetViewport().GetTopRight().YValue;

	if (levelNumber == 1) // level one, create rocks and 6 turret enemies
	{
		
		for (int i = 0; i < 20; i++)
		{
			randX = rand() % (screenWidth * 2) + (-screenWidth);
			randY = rand() % (screenHeight * 2) + (-screenHeight);

			Rock* prock = new Rock();
			prock->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, 1.0f);
			m_objManager->AddObject(prock);
		}

		for (int i = 0; i < 6; i++)
		{
			randX = rand() % (screenWidth * 2) + (-screenWidth);
			randY = rand() % (screenHeight * 2) + (-screenHeight);

			EnemyShip* pEnemy = new EnemyShip(1);
			pEnemy->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, pship);
			m_objManager->AddObject(pEnemy);
		}
		numEnemies = 6;

		randX = rand() % (screenWidth * 2) + (-screenWidth);
		randY = rand() % (screenHeight * 2) + (-screenHeight);

		PowerUp* pPowerUp = new PowerUp();
		pPowerUp->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, ObjectType::POWERUP_ATK); // these create 2 powerups to pick up
		m_objManager->AddObject(pPowerUp);
		randX = rand() % (screenWidth * 2) + (-screenWidth);
		randY = rand() % (screenHeight * 2) + (-screenHeight);
		PowerUp* pPowerUp2 = new PowerUp();
		pPowerUp2->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, ObjectType::POWERUP_LIFE);
		m_objManager->AddObject(pPowerUp2);
	}

	
	if (levelNumber == 2) // lvl 2, create turret and missile launcher enemies
	{
		
		for (int i = 0; i < 4; i++)
		{
			randX = rand() % (screenWidth * 2) + (-screenWidth);
			randY = rand() % (screenHeight * 2) + (-screenHeight);

			EnemyShip* pEnemyShip = new EnemyShip(2);
			pEnemyShip->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, pship);
			m_objManager->AddObject(pEnemyShip);
		}
		for (int i = 0; i < 4; i++)
		{
			randX = rand() % (screenWidth * 2) + (-screenWidth);
			randY = rand() % (screenHeight * 2) + (-screenHeight);

			EnemyShip* pEnemy = new EnemyShip(1);
			pEnemy->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, pship);
			m_objManager->AddObject(pEnemy);
		}
		numEnemies = 8;

		randX = rand() % (screenWidth * 2) + (-screenWidth);
		randY = rand() % (screenHeight * 2) + (-screenHeight);

		PowerUp* pPowerUp = new PowerUp();
		pPowerUp->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, ObjectType::POWERUP_ATK);
		m_objManager->AddObject(pPowerUp);
		randX = rand() % (screenWidth * 2) + (-screenWidth);
		randY = rand() % (screenHeight * 2) + (-screenHeight);
		PowerUp* pPowerUp2 = new PowerUp();
		pPowerUp2->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, ObjectType::POWERUP_LIFE);
		m_objManager->AddObject(pPowerUp2);
	}

	if (levelNumber == 3) // level three, create boss
	{
		EnemyShip* pEnemy = new EnemyShip(3);
		pEnemy->Initialise(Vector2D(0, 100), m_objManager, m_soundSystem, pship);
		m_objManager->AddObject(pEnemy);
		numEnemies = 1;

		randX = rand() % (screenWidth * 2) + (-screenWidth);
		randY = rand() % (screenHeight * 2) + (-screenHeight);

		PowerUp* pPowerUp = new PowerUp();
		pPowerUp->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, ObjectType::POWERUP_ATK);
		m_objManager->AddObject(pPowerUp);
		randX = rand() % (screenWidth * 2) + (-screenWidth);
		randY = rand() % (screenHeight * 2) + (-screenHeight);
		PowerUp* pPowerUp2 = new PowerUp();
		pPowerUp2->Initialise(Vector2D(randX, randY), m_objManager, m_soundSystem, ObjectType::POWERUP_LIFE);
		m_objManager->AddObject(pPowerUp2);
	}
}

void LevelManager::Render()
{
	if (!isOver) // if game is active, draw some info to the the player
	{
		MyDrawEngine* pDraw = MyDrawEngine::GetInstance();
		pDraw->WriteText(20, 50, L"Level ", MyDrawEngine::GREEN);
		pDraw->WriteInt(20, 120, levelNumber, MyDrawEngine::GREEN);
		pDraw->WriteText(20, 400, L"Score ", MyDrawEngine::GREEN);
		pDraw->WriteInt(20, 470, score, MyDrawEngine::GREEN);
		pDraw->WriteText(20, 600, L"Time ", MyDrawEngine::GREEN);
		pDraw->WriteInt(20, 670, endLevelTimer, MyDrawEngine::GREEN);
		pDraw->WriteText(20, 700, L"Enemies ", MyDrawEngine::GREEN);
		pDraw->WriteInt(20, 770, numEnemies, MyDrawEngine::GREEN);


		for (int i = 0; i < playerLives; i++) // show loves
		{
			pDraw->DrawAt(Vector2D(700 + 80 * i, -900), shipImage);
		}
	}
}

void LevelManager::EnemyDead()
{
	numEnemies--;
	AddScore(50);

	if (numEnemies == 0 && levelNumber == 3) // if last enemy, and last level, you win
	{
		ObjectManager::Message gameWonMsg;
		gameWonMsg.type = EventType::GAME_WON;
		m_objManager->SendMsg(gameWonMsg);
		isOver = true;
		levelNumber = 0;
		m_soundSystem->StopEngineSound();
	}
}

void LevelManager::PlayerDead()
{
	playerLives--;
	m_framesToFreeze = m_framesToFreeze +  40;
}



void LevelManager::HandleMessage(ObjectManager::Message msg)
{
	if (msg.type == EventType::ROCK_DESTROYED)  // score for destroying rocks
	{
		AddScore(50);
	}

	if (msg.type == EventType::PLAYERSHIP_DOWN)
	{
		if (playerLives > 0) // reduce life
		{
			PlayerDead();
		}
		else // end game
		{
			GameOver();
		}
	}

	if (msg.type == EventType::ENEMY_DOWN)
	{
		m_framesToFreeze = m_framesToFreeze + 40;
		if(msg.pSource->GetType() != ObjectType::MISSILE) EnemyDead(); // dont count missiles as enemies, but still cause the explosion shake
	}

	if (msg.type == EventType::EXTRA_LIFE) // increase life
	{
		playerLives++;
	}
}

void LevelManager::GameOver() // send gameover message, and stop engine sound
{
	ObjectManager::Message gameOverMsg;
	gameOverMsg.type = EventType::GAME_OVER;
	m_objManager->SendMsg(gameOverMsg);
	isOver = true;
	m_soundSystem->StopEngineSound();
}

void LevelManager::AddScore(int scoreGained)
{
	score = score + scoreGained;
}

void LevelManager::Update(float frametime)
{
	if (m_framesToFreeze > 0) // screen shake on explosions
	{
		m_framesToFreeze--;

		MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(rand() % 24 - 12.0f, rand() % 24 - 12.0f));
	}
	else
	{
		MyDrawEngine::GetInstance()->theCamera.PlaceAt(Vector2D(0, 0));
	}


	if (numEnemies <= 0 && levelNumber != 3 && !isOver) // next level popup
	{
		MyDrawEngine* pDraw = MyDrawEngine::GetInstance();
		pDraw->WriteText(850, 400, L"Level Complete! ", MyDrawEngine::GREEN);
		pDraw->WriteText(850, 450, L"Next Level Starting in ", MyDrawEngine::GREEN);
		pDraw->WriteInt(850, 500, endLevelTimer, MyDrawEngine::GREEN);


		endLevelTimer -= frametime;
		if (endLevelTimer <=0) // start next level
		{
			ObjectManager::Message nextLevelMsg;
			nextLevelMsg.type = EventType::LEVEL_START;
			m_objManager->SendMsg(nextLevelMsg);

			StartLevel();
			endLevelTimer = 5.0f;
		}
	}
	
}

