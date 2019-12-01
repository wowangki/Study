#include "stdafx.h"
#include "Animate.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Module/Image/ImageModule.h"

Animate::Animate()
{
}

Animate::Animate(string imgKey, Transform * myTransform)
	:transform(myTransform)
{
	this->imgKey = imgKey;

	image = _IMAGE->FindImage(imgKey);
	isReverse = false;
	opacity = 1.0f;
	currentFrame = { 0,0 };
	currentTime = 0.0f;
	frameTime = 1.0f;
	isCull = false;
	isPlay = false;
}

Animate::~Animate()
{
}

HRESULT Animate::Init(void)
{
	return S_OK;
}

void Animate::Release(void)
{
	SafeRelease(transform);
	image = nullptr;
}

void Animate::Update(void)
{
	isCull = IsCulling();

	if (isPlay) {
		currentTime += _TIMER->GetElapsedTime();

		if (currentTime >= frameTime) {
			if (!(currentFrame.x >= image->GetMaxFrameX())) {
				currentFrame.x = 0;
				currentTime -= frameTime;

				while (currentTime > _TIMER->GetElapsedTime()) {
					currentTime -= _TIMER->GetElapsedTime();
				}
				
			}
			else {
				currentFrame.x++;
			}
		}
	}
}

void Animate::Render(void)
{
	if (isCull) return;
	image->FrameRender(transform, currentFrame, isReverse, opacity);
}

bool Animate::IsCulling(void)
{
	return (!IsInRect(image->GetRect(transform->GetWorldPos().x, transform->GetWorldPos().y),
		MakeRect({ _CAMERA->x, _CAMERA->y }, { WINSIZEX, WINSIZEY })));
}