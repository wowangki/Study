#include "stdafx.h"
#include "Image.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Manager/World/WorldMgr.h"
#include "../Component/Graphic/Camera/Camera.h"
#include "../Manager/Singleton/Resource/Image/ImageInfo/ImageInfo.h"
#include "../GameObject/GameObject.h"

DECLARE_COMPONENT(Image);

Image::Image(GameObject * object)
	:imageInfo(nullptr),opacity(1.0f),isCull(false)
{
	this->object = object;
	transform = object->GetComponent<Transform>();
	this->object->GetWorld()->RegistImage(this);
}


Image::~Image()
{
	
}

HRESULT Image::Init(string nickName)
{
	imageInfo = _IMAGE->FindImage(nickName);

	if (transform->GetSize().width == 0.0f &&
		transform->GetSize().height == 0.0f) {
		transform->SetSize(imageInfo->GetImgSize());
	}

	return S_OK;
}

void Image::Release(void)
{
	this->object->GetWorld()->UnRegistImage(this);
	imageInfo = nullptr;
}

void Image::Update(void)
{
	const Camera* cam = object->GetWorld()->GetCurrentCam();
	D2D_RECT_F cullWindow;
	
	if (object->GetLayer() == LAYER::UI) {
		cullWindow = MakeRect({ 0,0 }, { WINSIZEX, WINSIZEY });
	}
	else {
		cullWindow = cam->GetCamRect();
	}

	D2D_RECT_F rc = MakeRect(
		{ transform->GetWorldPos().x + cam->GetRevisionPos().x,
		  transform->GetWorldPos().y + cam->GetRevisionPos().y },
		transform->GetSize(),
		transform->GetPivot());

	isCull = !IsInRect(rc, cullWindow);
}

void Image::Render(void)
{
	if (!imageInfo || isCull) return;

	ImageInfo::LPIMAGE_INFO imgInfo = imageInfo->GetImageInfo();
	D2D_POINT_2F pos = transform->GetWorldPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();
	const Camera* cam = object->GetWorld()->GetCurrentCam();
	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation;

	if (object->GetLayer() == LAYER::UI) {
		dxLocation = MakeRect(pos, size, pivot); 
	}
	else {
		dxLocation = MakeRect({ pos.x + cam->GetRevisionPos().x,
			pos.y + cam->GetRevisionPos().y }
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