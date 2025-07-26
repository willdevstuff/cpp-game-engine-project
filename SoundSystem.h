#pragma once
#include "mysoundengine.h"
// SOUND SYSTEM - Can load and play/stop a variety of SFX
class SoundSystem 
{
private:	
	static const int numExplosionSounds = 5;
	SoundIndex explosionSounds[numExplosionSounds];
	SoundIndex Thrust;
	SoundIndex Shot;
	SoundIndex GetHit;
	SoundIndex PhaseEnter;
	SoundIndex PhaseLeave;
	SoundIndex PowerUp;
	SoundIndex MissileLaunch;
	bool enginePlaying;
	int m_volume;
	//SoundIndex explosionSingle;
public:
	void LoadSounds();
	void PlayPowerUp();
	void PlayShot();
	void PlayExplosion();
	void StartEngineSound();
	void StopEngineSound();
	void SetEngineVolume(int volume);
	void PlayGetHit();
	void PlayPhaseEnter();
	void PlayPhaseLeave();
	void PlayMissileLaunch();
};