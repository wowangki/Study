#include "stdafx.h"
#include "Effect.h"


Effect::Effect(string effectNickName, int _effectSpeed)
	:img(nullptr), pos(POINTF()),
	isActive(false),
	frameX(0), frameY(0),
	effectSpeed(_effectSpeed),
	currentFrame(POINT()),
	frameTime(0)
{
	img = _IMAGE->FindImage(effectNickName);
	if (img == nullptr) {
		string errStr = "이펙트 이미지를 찾을 수 없습니다.\n 이펙트 닉네임 : " + effectNickName;
		MessageBoxA(AppDesc._hWnd, errStr.c_str(), NULL, MB_OK);
		PostQuitMessage(0);
	}

	imgName = effectNickName;
	frameX = img->GetMaxFrameX();
	frameY = img->GetMaxFrameY();
}

Effect::~Effect()
{
}

void Effect::Start(float x, float y)
{
	pos = { x,y };
	isActive = true;
	currentFrame = { 0,0 };
	frameTime = 0;
}

void Effect::Reset()
{
	isActive = false;
	pos = { 0.0f, 0.0f };
	currentFrame = { 0,0 };
	frameTime = 0;
}

void Effect::Update()
{
	if (!isActive) return;

	if (frameTime % effectSpeed == 0)
	{
		currentFrame.x++;
		frameTime = 0;

		if (currentFrame.x > frameX) {
			currentFrame.x = 0;
			currentFrame.y++;

			if (currentFrame.y > frameY) {
				Reset();
				return;
			}
		}
	}
	
	frameTime++;
}

void Effect::Render()
{
	if (!isActive) return;

	img->EffectFrameRender(pos, currentFrame.x, currentFrame.y);
}
