#include "stdafx.h"
#include "Image.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Manager/Singleton/Resource/Image/ImageInfo/ImageInfo.h"
#include "../GameObject/GameObject.h"

Image::Image()
	:imageInfo(nullptr),transform(nullptr),opacity(1.0f),isCull(false)
{
}

Image::Image(GameObject * object)
	:imageInfo(nullptr),opacity(1.0f),isCull(false)
{
	this->object = object;
	transform = object->GetComponent<Transform>();
}


Image::~Image()
{
	
}

HRESULT Image::Init(string nickName)
{
	imageInfo = _IMAGE->FindImage(nickName);
	return S_OK;
}

void Image::Release(void)
{
	imageInfo = nullptr;
}

void Image::Update(void)
{
	D2D_RECT_F cullWindow;
	if (object->GetLayer() == LAYER::UI) {
		cullWindow = MakeRect({ 0,0 }, { WINSIZEX, WINSIZEY });
	}
	else {
		cullWindow = MakeRect({ _CAMERA->x,_CAMERA->y }, { WINSIZEX, WINSIZEY });
	}

	isCull = !IsInRect(transform->GetRect(), cullWindow);
}

void Image::Render(void)
{
	if (!imageInfo || isCull) return;

	ImageInfo::LPIMAGE_INFO imgInfo = imageInfo->GetImageInfo();
	D2D_POINT_2F pos = transform->GetWorldPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();
	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation;

	if (object->GetLayer() == LAYER::UI) {
		dxLocation = MakeRect(pos, size, pivot);
	}
	else {
		dxLocation = MakeRect({ pos.x + _CAMERA->x, pos.y + _CAMERA->y }
			, size, pivot);
	}

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		imgInfo->imageSize.width,
		imgInfo->imageSize.height
	);

	_RenderTarget->DrawBitmap(imgInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}