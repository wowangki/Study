#include "stdafx.h"
#include "Animator.h"
#include "../GameObject/GameObject.h"
#include "../Component/Graphic/Image/Sprite.h"
#include "../Manager/Singleton/Resource/Image/ImageInfo/ImageInfo.h"

Animator::Animator()
{
}

Animator::Animator(GameObject * object)
	:currentTime(0.0f), frameTime(0.0f)
{
	this->object = object;
}


Animator::~Animator()
{
}

void Animator::AddSprite(int state, string nickName)
{
	Sprite* sprite = FindSprite(_IMAGE->FindImage(nickName));
	if (sprite) return;

	sprite = new Sprite(object);
	sprite->Init(nickName);
	
	frameTime = DEFAULT_FRAMETIME;
	mSprite.insert(make_pair(state, sprite));
}

void Animator::ChangeSprite(int state, string nickName)
{
	if (mSprite.empty()) return;
	mIter iter = mSprite.begin();

	for (iter; iter != mSprite.end(); ++iter) {
		if (iter->first == state) {
			iter->second = FindSprite(_IMAGE->FindImage(nickName));
			break;
		}
	}
}

void Animator::RemoveSprite(int state)
{
	if (mSprite.empty()) return;
	mSprite.erase(state);
}


Sprite * Animator::FindSprite(int state)
{
	if (mSprite.empty()) return nullptr;

	mIter iter = mSprite.begin();

	for (iter; iter != mSprite.end(); ++iter) {
		if (iter->first == state) {
			return iter->second;
		}
	}

	return nullptr;
}

Sprite * Animator::FindSprite(ImageInfo * img)
{
	if (mSprite.empty()) return nullptr;

	mIter iter = mSprite.begin();

	for (iter; iter != mSprite.end(); ++iter) {
		if (iter->second->GetImageInfo() == img) {
			return iter->second;
		}
	}

	return nullptr;
}

void Animator::Release(void)
{
	mIter iter = mSprite.begin();

	for (iter; iter != mSprite.end(); ++iter) {
		iter->second = nullptr;
	}

	map<int, Sprite*> mTemp;
	mTemp.swap(mSprite);
}

void Animator::Update(void)
{
	Sprite* temp = mSprite.find(object->GetState())->second;

	temp->Update();
	
	currentTime += _TIMER->GetElapsedTime();

	if (currentTime >= frameTime) {
		temp->IncreaseFrame({ 1,0 });
		currentTime -= frameTime;

		if (temp->GetFrame().x >= temp->GetImageInfo()->GetMaxFrame().x) {
			temp->SetFrameX(0);
			temp->IncreaseFrame({ 0,1 });

			if (temp->GetFrame().y >= temp->GetImageInfo()->GetMaxFrame().y) {
				temp->SetFrameY(0);
			}
		}

		while (currentTime >= _TIMER->GetElapsedTime()) {
			currentTime -= _TIMER->GetElapsedTime();
		}
	}
}

void Animator::Render(void)
{
	mSprite.find(object->GetState())->second->Render();
}
