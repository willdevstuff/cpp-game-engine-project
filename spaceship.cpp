#include "spaceship.h"
#include "myinputs.h"


Spaceship::Spaceship():GameObject(ObjectType::SPACESHIP)
{
	//isActive = false;
	//health = 100;
	scale = 1.0f;
	angle = 0.0f;
	transparency = 0.0f;
	velocity.set(0, 0);
	position.set(0, 0);
	shotTimer = 0;
	shotCooldown = 20;
	phased = false;
	phaseTimer = 2.0f;
	invulTimer = 4.0f;
	phaseCooldown = 0.0f;
}

IShape2D& Spaceship::GetShape() 
{
	return collisionShape;
}

void Spaceship::PhaseShift() // handle the phaseshift ability
{
	p_soundSystem->PlayPhaseEnter();
	phaseTimer = 2.0f;
	//LoadImage(L"assets/ship_invul.bmp");
	phased = true;
}

void Spaceship::HandleCollision( GameObject& other )
{
	if (other.GetType() == ObjectType::POWERUP_ATK)  // when picking up atk powerup
	{
		shotCooldown = 10;
		other.Deactivate();
		powerUpDuration = 10;
		p_soundSystem->PlayPowerUp();
	}
	if (other.GetType() == ObjectType::POWERUP_LIFE) // when picking up bonus life powerup
	{
		ObjectManager::Message m;
		m.type = EventType::EXTRA_LIFE;
		m.location = position;
		m.pSource = this;
		pObjectManager->SendMsg(m);
		other.Deactivate();
		p_soundSystem->PlayPowerUp();
	}
	if (!invincible && !phased) // if not invulnerable, and colliding with hostile object, explode and lose life
	{
		if (other.GetType() == ObjectType::ROCK || other.GetType() == ObjectType::ENEMYBULLET || other.GetType() == ObjectType::MISSILE)
		{
			Explosion* pExplosion = new Explosion();
			pExplosion->Initialise(position, 5.0, 0.1, p_soundSystem, 1);
			if (pObjectManager) 
			{
				pObjectManager->AddObject(pExplosion);
			}
			other.Deactivate();
			ObjectManager::Message m;
			m.type = EventType::PLAYERSHIP_DOWN;
			m.location = position;
			m.pSource = this;
			pObjectManager->SendMsg(m);
			Respawn();
		}
	}
}

void Spaceship::Respawn() // respawn at center of screen and get given some temporary invincibility to move away from danger
{
	position.set(0, 0);
	invulTimer = 4.0f;
	invincible = true;
	//LoadImage(L"assets/ship_invul.bmp");
}

void Spaceship::Initialise(Vector2D spawnPosition, ObjectManager* pObjMan, SoundSystem* pSoundSystem, MousePointer* pMousePointer)
{
	pMP = pMousePointer;
	isActive = true;
	invulImage = LoadImage(L"assets/ship_invul.bmp");
	plasmaImage = LoadImage(L"assets/plasma.bmp");
	LoadImage(L"assets/ship.bmp");
	p_soundSystem = pSoundSystem;
	position = spawnPosition;
	pObjectManager = pObjMan;
}

void Spaceship::Render()
{
	GameObject::Render();

	if (!phased && phaseCooldown <= 0) // tell player phase is ready
	{
		MyDrawEngine::GetInstance()->WriteText(1700, 50, L"Phase Shift Ready ", MyDrawEngine::GREEN);
	}
	if (!phased && phaseCooldown > 0) // show player phase cooldown
	{
		MyDrawEngine::GetInstance()->WriteText(1700, 50, L"Phase Shift Cooldown ", MyDrawEngine::GREEN);
		MyDrawEngine::GetInstance()->WriteInt(1750, 120, phaseCooldown, MyDrawEngine::GREEN);

	}
	if (phased) // show phase duration next to ship, also show white image on top of ship and slowly fade it away in line with the timer
	{
		MyDrawEngine::GetInstance()->DrawAt(position, invulImage, scale, angle, 2.0f - phaseTimer / 2); 
		MyDrawEngine::GetInstance()->WriteInt(GetPosition() + Vector2D(0, -20), phaseTimer, MyDrawEngine::GREEN);
	}

	if (invincible) // show shield around ship and slowly fade away as the timer ticks down
	{
		MyDrawEngine::GetInstance()->DrawAt(position, plasmaImage, 2.5, angle, 4.0f - invulTimer / 4);
	}

}
void Spaceship::Update(float frameTime)
{
	if (invincible) // tick invincibility timer down
	{
		invulTimer -= frameTime;
			if (invulTimer <= 0)
			{
				invincible = false;
			}
	}

	if (phased) // tick phase timer down
	{
		phaseTimer -= frameTime;
		//pDraw->WriteText(20, 50, L"PhaseShift ", MyDrawEngine::GREEN);
		if (phaseTimer <= 0)
		{
			phaseCooldown = 5.0f;
			p_soundSystem->PlayPhaseLeave();
			phased = false;
		}
	}

	if (phaseCooldown > 0 && !phased) // cooldown ability
	{
		phaseCooldown -= frameTime;
	}

	if (shotCooldown == 10) // if powerup active, tick down its timer
	{
		powerUpDuration -= frameTime;
			if (powerUpDuration <= 0)
			{
				shotCooldown = 40;
			}
	}
	collisionShape.PlaceAt(position, 30);
	shotTimer--;
	MyInputs* pInputs = MyInputs::GetInstance();
	pInputs->SampleKeyboard(); // sample the keyboard once per frame...
	pInputs->SampleMouse();

	const float TURNRATE = 5.0f; /// point towards the cursor
	Vector2D direction = pMP->GetPosition() - position;
	float desiredAngle = direction.angle();

	float angleDifference = angle = desiredAngle;
	if (angleDifference >  3.141f) angleDifference -= 6.242f;
	if (angleDifference < -3.141f) angleDifference += 6.242f;

	if (angleDifference > 0) angle = angle - TURNRATE * frameTime;
	else angle = angle + TURNRATE * frameTime;

	//handle movement inputs
	if (pInputs->KeyPressed(DIK_W)) { speed.YValue += 800 * frameTime; p_soundSystem->StartEngineSound(); }
	if (pInputs->KeyPressed(DIK_A)) { speed.XValue -= 800 * frameTime; p_soundSystem->StartEngineSound(); }
	if (pInputs->KeyPressed(DIK_S)) { speed.YValue -= 800 * frameTime; p_soundSystem->StartEngineSound(); }
	if (pInputs->KeyPressed(DIK_D)) { speed.XValue += 800 * frameTime; p_soundSystem->StartEngineSound(); }
	if (!pInputs->KeyPressed(DIK_W) && !pInputs->KeyPressed(DIK_A) && !pInputs->KeyPressed(DIK_S) && !pInputs->KeyPressed(DIK_D)) { p_soundSystem->StopEngineSound(); }
	speed -= speed * 2.0 * frameTime; // friction
	position += speed * frameTime;  // handle movement

	
	if (pInputs->IfMouseLeftDown() && (shotTimer <= 0)) // handle shooting
	{   
		p_soundSystem->PlayShot();
		Bullet* pBullet = new Bullet();
		Vector2D vel;
		vel.setBearing(angle, 400.0f);
		pBullet->Initialise(position + vel * 0.1, angle, ObjectType::BULLET); // adjust the '0.1' value higher to spawn further away from ship. vice versa.
		pObjectManager->AddObject(pBullet);
		shotTimer = shotCooldown;
	}

	if (pInputs->KeyPressed(DIK_LSHIFT) && !phased && phaseCooldown <= 0) PhaseShift(); //activate phase ability


	/// wraparound screen
	float screenWidth = MyDrawEngine::GetInstance()->GetViewport().GetBottomRight().XValue;
	float screenHeight = MyDrawEngine::GetInstance()->GetViewport().GetTopRight().YValue;

	if (position.XValue > screenWidth) { position.XValue = -screenWidth; }
	if (position.XValue < -screenWidth) { position.XValue = screenWidth; }
	if (position.YValue > screenHeight) { position.YValue = -screenHeight; }
	if (position.YValue < -screenHeight) { position.YValue = screenHeight; }

}