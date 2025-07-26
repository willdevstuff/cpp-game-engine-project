#include "EnemyShip.h"
#include "Missile.h"

void EnemyShip::Update(float frametime)
{
	if (p_PlayerShip != NULL)
	{
		shotTimer--;  // shot cooldown
		bonusShotTimer--;
		collisionShape.PlaceAt(position, 30);

		/////////////////////////// point to player
		const float TURNRATE = 5.0f;  
		Vector2D direction = p_PlayerShip->GetPosition() - position;
		float desiredAngle = direction.angle();

		float angleDifference = angle = desiredAngle;
		if (angleDifference > 3.141f) angleDifference -= 6.242f;
		if (angleDifference < -3.141f) angleDifference += 6.242f;

		if (angleDifference > 0) angle = angle - TURNRATE * frametime;
		else angle = angle + TURNRATE * frametime;


		if (shotTimer <= 0 && m_shipLevel == 1) // handle shooting for type 1 ships (bullet turrets)
		{
			p_soundSystem->PlayShot();
			Bullet* pBullet = new Bullet();
			Vector2D vel;
			vel.setBearing(angle, 400.0f);
			pBullet->Initialise(position + vel * 0.1, angle, ObjectType::ENEMYBULLET); // adjust the '0.1' value higher to spawn further away from ship. vice versa.
			pObjectManager->AddObject(pBullet);
			shotTimer = shotCooldown;
		}

		if (shotTimer <= 0 && m_shipLevel == 2) // handle shooting for type 2 ships (missile launchers)
		{
			p_soundSystem->PlayMissileLaunch();  // missle shoot SFX
			Missile* pMissile = new Missile();
			Vector2D vel;
			vel.setBearing(angle, 400.0f);
			pMissile->Initialise(position + vel * 0.1, p_PlayerShip, pObjectManager, p_soundSystem); // adjust the '0.1' value higher to spawn further away from ship. vice versa.
			pObjectManager->AddObject(pMissile);
			shotTimer = shotCooldown;
		}

		if (bonusShotTimer <= 0 && m_shipLevel == 3) // handle shooting missiles for boss ship
		{
			p_soundSystem->PlayMissileLaunch();
			Missile* pMissile = new Missile();
			Vector2D vel;
			vel.setBearing(angle, 400.0f);
			pMissile->Initialise(position + vel * 0.1, p_PlayerShip, pObjectManager, p_soundSystem); // adjust the '0.1' value higher to spawn further away from ship. vice versa.
			pObjectManager->AddObject(pMissile);
			bonusShotTimer = bonusShotCooldown;
		}

		if (shotTimer <= 0 && m_shipLevel == 3) // handle shooting bullets for boss ship 
		{
			p_soundSystem->PlayShot();
			Bullet* pBullet = new Bullet();
			Vector2D vel;
			vel.setBearing(angle, 400.0f);
			pBullet->Initialise(position + vel * 0.1, angle, ObjectType::ENEMYBULLET); // adjust the '0.1' value higher to spawn further away from ship. vice versa.
			pObjectManager->AddObject(pBullet);
			shotTimer = shotCooldown;
		}


		if (health <= 0) // die if at 0 health
		{
			Explosion* pExplosion = new Explosion();
			pExplosion->Initialise(position, 5.0, 0.1, p_soundSystem, 1);
			if (pObjectManager)
			{
				pObjectManager->AddObject(pExplosion);
			}

			ObjectManager::Message m;
			m.type = EventType::ENEMY_DOWN;
			m.location = position;
			m.pSource = this;
			pObjectManager->SendMsg(m);
			Deactivate();
		}
	}
}

EnemyShip::EnemyShip(int shipLevel):GameObject(ObjectType::ENEMYSHIP)
{
	scale = 1.0f;
	angle = 0.0f;
	transparency = 0.0f;
	m_shipLevel = shipLevel;

	// pass in the ship type ranging from 1,2,3 and set image/health etc accordingly 
	switch (m_shipLevel)
	{
	case 1:
		health = 2;
		shotCooldown = 20;
		LoadImage(L"assets/turret.bmp");
		break;
	case 2:
		health = 3;
		shotCooldown = 500;
		scale = 0.75;
		LoadImage(L"assets/harrasser.bmp");
		break;
	case 3:
		LoadImage(L"assets/boss.bmp");
		health = 25;
		shotCooldown = 10;
		bonusShotCooldown = 300;
		break;
	}

}

void EnemyShip::Initialise(Vector2D spawnPosition, ObjectManager* pObjMan, SoundSystem* pSoundSystem, Spaceship* pPlayerShip)
{
	pObjectManager = pObjMan;
	p_PlayerShip = pPlayerShip;
	position = spawnPosition;
	p_soundSystem = pSoundSystem;
	isActive = true;
}

IShape2D& EnemyShip::GetShape()
{
	return collisionShape;
}

void EnemyShip::HandleCollision(GameObject& other)
{
	if (other.GetType() == ObjectType::BULLET)
	{
		--health;
		p_soundSystem->PlayGetHit();
	}
}
