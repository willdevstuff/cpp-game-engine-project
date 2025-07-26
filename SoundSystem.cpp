#include "SoundSystem.h"
// sound system
void SoundSystem::LoadSounds() // load all the sounds from files in the asset folder
{
	MySoundEngine* pSoundEngine = MySoundEngine::GetInstance();
	Shot = pSoundEngine->LoadWav(L"assets/shoot.wav");
	Thrust = pSoundEngine->LoadWav(L"assets/thrustloop2.wav");
	GetHit = pSoundEngine->LoadWav(L"assets/sonic3_hit.wav");
	PhaseEnter = pSoundEngine->LoadWav(L"assets/phaseEnter.wav");
	PhaseLeave = pSoundEngine->LoadWav(L"assets/phaseLeave.wav");
	PowerUp = pSoundEngine->LoadWav(L"assets/powerup.wav");
	MissileLaunch = pSoundEngine->LoadWav(L"assets/launch.wav");
	explosionSounds[0] = pSoundEngine->LoadWav(L"assets/explosion1.wav");
	explosionSounds[1] = pSoundEngine->LoadWav(L"assets/explosion2.wav");
	explosionSounds[2] = pSoundEngine->LoadWav(L"assets/explosion3.wav");
	explosionSounds[3] = pSoundEngine->LoadWav(L"assets/explosion4.wav");
	explosionSounds[4] = pSoundEngine->LoadWav(L"assets/explosion5.wav");

	//explosionSingle = pSoundEngine->LoadWav(L"assets/explosion4.wav");
}

void SoundSystem::PlayMissileLaunch()
{
	MySoundEngine::GetInstance()->Play(MissileLaunch);
}
void SoundSystem::PlayPowerUp()
{
	MySoundEngine::GetInstance()->Play(PowerUp);
}

void SoundSystem::PlayShot() 
{ 
	MySoundEngine::GetInstance()->Play(Shot); 
}

void SoundSystem::PlayGetHit()
{
	MySoundEngine::GetInstance()->Play(GetHit);
}
void SoundSystem::PlayPhaseEnter()
{
	MySoundEngine::GetInstance()->Play(PhaseEnter);
}
void SoundSystem::PlayPhaseLeave()
{
	MySoundEngine::GetInstance()->Play(PhaseLeave);
}
void SoundSystem::StartEngineSound() 
{ 
	if (!enginePlaying)MySoundEngine::GetInstance()->Play(Thrust, true);
	enginePlaying = true;
}

void SoundSystem::StopEngineSound() 
{ 
	if (enginePlaying)MySoundEngine::GetInstance()->Stop(Thrust);
	enginePlaying = false; 
}

void SoundSystem::SetEngineVolume(int volume) 
{ 
	m_volume = (volume - 100) * 35; 
	MySoundEngine::GetInstance()->SetVolume(Thrust, m_volume); 
}

void SoundSystem::PlayExplosion() 
{ 
	int choice = rand() % numExplosionSounds;
	MySoundEngine::GetInstance()->Play(explosionSounds[choice]);
}