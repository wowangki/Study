#include "stdafx.h"
#include "Sprite.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Manager/World/WorldMgr.h"
#include "../Component/Graphic/Camera/Camera.h"
#include "../Manager/Singleton/Resource/Image/ImageInfo/ImageInfo.h"

Sprite::Sprite(Transform * transform)
	: imageInfo(nullptr), transform(nullptr), frame({ 0,0 }), opacity(1.0f), 
	isReverse(false), isCull(false), type(SINGLE)
{
	this->transform = transform;
	this->transform->GetMyObject()->GetWorld()->RegistSprite(this);
}

Sprite::~Sprite()
{
}

HRESULT Sprite::Init(string nickName, SPRITE_TYPE type, D2D_POINT_2L frame)
{
	imageInfo = _IMAGE->FindImage(nickName);

	if (transform->GetSize().width == 0.0f &&
		transform->GetSize().height == 0.0f) {
		transform->SetSize(imageInfo->GetFrameImgSize());
	}

	this->frame = frame;
	this->type = type;

	return S_OK;
}

void Sprite::Release(void)
{
	this->transform->GetMyObject()->GetWorld()->UnRegistSprite(this);
	imageInfo = nullptr;
}

void Sprite::Update(void)
{
	const Camera* cam = transform->GetMyObject()->GetWorld()->GetCurrentCam();
	D2D_RECT_F cullWindow;
	if (transform->GetMyObject()->GetLayer() == LAYER::UI) {
		cullWindow = MakeRect({ 0,0 }, { WINSIZEX, WINSIZEY });
	}
	else {
		cullWindow = cam->GetCamRect();
	}

	D2D_RECT_F rc = MakeRect(
		{ transform->GetWorldPos().x + cam->GetRevisionPos().x,
		  transform->GetWorldPos().y + cam->GetRevisionPos().y},
		transform->GetSize(), 
		transform->GetPivot());

	isCull = !IsInRect(rc, cullWindow);
}

void Sprite::Render(void)
{
	if (!imageInfo || isCull) return;

	ImageInfo::LPIMAGE_INFO imgInfo = this->imageInfo->GetImageInfo();
	D2D_POINT_2F pos = transform->GetWorldPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();
	const Camera* cam = transform->GetMyObject()->GetWorld()->GetCurrentCam();
	float degree = RadianToDegree(transform->GetWorldAngle());

	if (size.width == 0.0f || size.height == 0.0f) {
		size.width = imgInfo->frameImageSize.width;
		size.height = imgInfo->frameImageSize.height;
	}

	D2D_POINT_2F dxPoint = GetDxPoint(pos, size, pivot);
	Matrix3x2F dxMatrix;

	if (isReverse) dxMatrix = Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint) * Matrix3x2F::Rotation(degree, dxPoint);
	else dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);

	_RenderTarget->SetTransform(dxMatrix);

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation;

	if (transform->GetMyObject()->GetLayer() == LAYER::UI) {
		dxLocation = MakeRect(pos, size, pivot);
	}
	else {
		dxLocation = MakeRect({ pos.x + cam->GetRevisionPos().x,
			pos.y + cam->GetRevisionPos().y }
		, size, pivot);
	}

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		frame.x * imgInfo->frameImageSize.width,
		frame.y * imgInfo->frameImageSize.height,
		(frame.x + 1) * imgInfo->frameImageSize.width,
		(frame.y + 1) * imgInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imgInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	_RenderTarget->SetTransform(Matrix3x2F::Identity());
}

D2D_POINT_2F Sprite::GetDxPoint(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot)
{
	D2D_POINT_2F temp;

	switch (pivot)
	{
	case nFigure::PIVOT_LT:
		temp.x = pos.x + (size.width * 0.5f);
		temp.y = pos.y + (size.height * 0.5f);
		break;
	case nFigure::PIVOT_LC:
		temp.x = pos.x + (size.width * 0.5f);
		temp.y = pos.y;
		break;
	case nFigure::PIVOT_LB:
		temp.x = pos.x + (size.width * 0.5f);
		temp.y = pos.y - (size.height * 0.5f);
		break;
	case nFigure::PIVOT_CT:
		temp.x = pos.x;
		temp.y = pos.y + (size.height * 0.5f);
		break;
	case nFigure::PIVOT_CC:
		temp.x = pos.x;
		temp.y = pos.y;
		break;
	case nFigure::PIVOT_CB:
		temp.x = pos.x;
		temp.y = pos.y - (size.height * 0.5f);
		break;
	case nFigure::PIVOT_RT:
		temp.x = pos.x - (size.width * 0.5f);
		temp.y = pos.y + (size.height * 0.5f);
		break;
	case nFigure::PIVOT_RC:
		temp.x = pos.x - (size.width * 0.5f);
		temp.y = pos.y;
		break;
	case nFigure::PIVOT_RB:
		temp.x = pos.x - (size.width * 0.5f);
		temp.y = pos.y - (size.height * 0.5f);
		break;
	default:
		break;
	}

	return temp;
}

