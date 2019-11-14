#include "stdafx.h"
#include "SoundStore.h"


SoundStore::SoundStore()
	:pSystem(nullptr), ppSound(nullptr), ppChannel(nullptr),
	soundIndexNumber(0),
	fEffectVolume(1.0f),
	fBgmVolume(1.0f)
{
	System_Create(&pSystem);

	pSystem->init(TOTAL_SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	ppSound = new Sound*[TOTAL_SOUNDBUFFER];
	ppChannel = new Channel*[TOTAL_SOUNDBUFFER];

	memset(ppSound, 0, sizeof(Sound*) * TOTAL_SOUNDBUFFER);
	memset(ppChannel, 0, sizeof(Channel*) * TOTAL_SOUNDBUFFER);
}


SoundStore::~SoundStore()
{
	mIter iter = mSound.begin();
	for (iter; iter != mSound.end(); ++iter)
	{
		DeleteSound(iter->first);
	}

	SafeDeleteArray(ppSound);
	SafeDeleteArray(ppChannel);
}

void SoundStore::Update(void)
{
}

void SoundStore::CreateSound(string nickName, string soundFile, bool bgm, bool loop)
{
	if (loop) {
		if (bgm) {
			pSystem->createStream(soundFile.c_str(),
				FMOD_LOOP_NORMAL, 0,
				&ppSound[mSound.size()]);
		}
		else {
			pSystem->createStream(soundFile.c_str(),
				FMOD_LOOP_NORMAL, 0,
				&ppSound[mSound.size()]);
		}
	}
	else {
		if (bgm) {
			pSystem->createStream(soundFile.c_str(),
				FMOD_DEFAULT, 0,
				&ppSound[mSound.size()]);
		}
		else {
			pSystem->createStream(soundFile.c_str(),
				FMOD_DEFAULT, 0,
				&ppSound[mSound.size()]);
		}
	}

	mSound.insert(make_pair(nickName, soundIndexNumber));
	soundIndexNumber++;
}

void SoundStore::Play(string nickName)
{
	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			int temp = iter->second;
			pSystem->playSound(FMOD_CHANNEL_FREE,
				ppSound[temp],
				false,
				&ppChannel[temp]);

			ppChannel[temp]->setVolume(fEffectVolume);
			break;
		}
	}
}

void SoundStore::Stop(string nickName)
{
	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			int temp = iter->second;
			ppChannel[temp]->stop();
			break;
		}
	}
}

void SoundStore::Pause(string nickName)
{
	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			int temp = iter->second;
			ppChannel[temp]->setPaused(true);
			break;
		}
	}
}

void SoundStore::Resume(string nickName)
{
	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			int temp = iter->second;
			ppChannel[temp]->setPaused(false);
			break;
		}
	}
}

void SoundStore::DeleteSound(string nickName)
{
	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			if (isPlay(nickName)) Stop(nickName);

			int temp = iter->second;
			ppSound[temp]->release();
			break;
		}
	}

	soundIndexNumber--;
}

bool SoundStore::isPlay(string nickName)
{
	mIter iter = mSound.begin();
	bool isPlay = false;

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			int temp = iter->second;
			ppChannel[temp]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundStore::isPause(string nickName)
{
	mIter iter = mSound.begin();
	bool isPlay = false;

	for (iter; iter != mSound.end(); ++iter) {
		if (iter->first == nickName) {
			int temp = iter->second;
			ppChannel[temp]->getPaused(&isPlay);

			break;
		}
	}

	return isPlay;
}

void SoundStore::SetEffectVolume(float value)
{
	fEffectVolume = value;

	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		int temp = iter->second;
		ppChannel[temp]->setVolume(fEffectVolume);
	}
}

void SoundStore::SetBgmVolume(float value)
{
	fBgmVolume = value;

	mIter iter = mSound.begin();

	for (iter; iter != mSound.end(); ++iter) {
		int temp = iter->second;
		ppChannel[temp]->setVolume(fBgmVolume);
	}
}
