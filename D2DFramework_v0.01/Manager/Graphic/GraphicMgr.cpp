#include "stdafx.h"
#include "GraphicMgr.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Graphic/Image/Image.h"
#include "../Component/Graphic/Image/Sprite.h"
#include "../Component/Graphic/Animator/Animator.h"
#include "../Component/Graphic/Camera/Camera.h"

GraphicMgr::GraphicMgr()
{
}

GraphicMgr::~GraphicMgr()
{
}

void GraphicMgr::Release(void)
{
	lImage.clear();
	lSprite.clear();
	lAnimator.clear();
	lCamera.clear();
}

void GraphicMgr::Render(void)
{
	for (lSIter iter = lSprite.begin(); iter != lSprite.end(); ++iter) {
		if (!(*iter)->GetTransform()->GetMyObject()->GetActive()) return;
		(*iter)->Render();
	}

	for (lAIter iter = lAnimator.begin(); iter != lAnimator.end(); ++iter) {
		if (!(*iter)->GetMyObject()->GetActive()) return;
		(*iter)->Render();
	}

	for (lIIter iter = lImage.begin(); iter != lImage.end(); ++iter) {
		if (!(*iter)->GetMyObject()->GetActive()) return;
		(*iter)->Render();
	}
}

void GraphicMgr::RegistImage(Image * img)
{
	lImage.push_back(img);
}

void GraphicMgr::UnRegistImage(Image * img)
{
	lImage.remove(img);
}

void GraphicMgr::RegistSprite(Sprite * sprite)
{
	lSprite.push_back(sprite);
}

void GraphicMgr::UnRegistSprite(Sprite * sprite)
{
	lSprite.remove(sprite);
}

void GraphicMgr::RegistAnimator(Animator * anim)
{
	lAnimator.push_back(anim);
}

void GraphicMgr::UnRegistAnimator(Animator * anim)
{
	lAnimator.remove(anim);
}

void GraphicMgr::RegistCam(Camera * cam)
{
	lCamera.push_back(cam);
}

void GraphicMgr::UnRegistCam(Camera * cam)
{
	lCamera.remove(cam);
}

void GraphicMgr::SetCurrentCam(GameObject * object)
{
	lCIter iter = lCamera.begin();
	
	currentCam = nullptr;
	for (iter; iter != lCamera.end(); ++iter) {
		if ((*iter)->GetMyObject() == object) {
			currentCam = (*iter);
		}
	}
}

void GraphicMgr::TestRenderBox(D2D_RECT_F rc, string brushName)
{
	D2D_RECT_F temp = rc;

	temp.left = temp.left + currentCam->GetRevisionPos().x;
	temp.right = temp.right + currentCam->GetRevisionPos().x;
	temp.top = temp.top + currentCam->GetRevisionPos().y;
	temp.bottom = temp.bottom + currentCam->GetRevisionPos().y;

	_RenderTarget->DrawRectangle(temp, _BRUSH->GetBrush(brushName));
}
