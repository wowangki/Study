#pragma once
#include "../Manager/Singleton/SingletonBase.h"
#include <map>
#pragma comment (lib, "Manager/Singleton/Resource/Sound/fmod/fmodex_vc.lib")
#include "fmod/fmod.hpp"

using namespace FMOD;

//Channel Buffer
#define EXTRA_CHANNELBUFFER 5
#define SOUNDBUFFER 10
#define TOTAL_SOUNDBUFFER EXTRA_CHANNELBUFFER + SOUNDBUFFER

class SoundModule : public SingletonBase<SoundModule>
{
private:
	typedef map<string, int> _mSoundIndex;
	_mSoundIndex mSound;
	typedef _mSoundIndex::iterator mIter;

private:
	int soundIndexNumber;
	System* pSystem;
	Sound** ppSound;
	Channel** ppChannel;

	float fEffectVolume;
	float fBgmVolume;

public:
	SoundModule();
	~SoundModule();

	void Update(void);

	void CreateSound(string nickName, string soundFile, bool bgm = true, bool loop = true);

	void Play(string nickName);
	void Stop(string nickName);
	void Pause(string nickName);
	void Resume(string nickName);
	void DeleteSound(string nickName);

	bool isPlay(string nickName);
	bool isPause(string nickName);

	float GetEffectVolume() { return fEffectVolume; }
	void SetEffectVolume(float value);

	float GetBgmVolume() { return fBgmVolume; }
	void SetBgmVolume(float value);
};

