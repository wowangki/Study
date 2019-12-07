#include "stdafx.h"
#include "Sprite.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Manager/Singleton/Resource/Image/ImageInfo/ImageInfo.h"

Sprite::Sprite()
	:imageInfo(nullptr), transform(nullptr), frame({ 0,0 }), opacity(1.0f), isReverse(false), isCull(false)
{
}

Sprite::Sprite(GameObject * object)
	: imageInfo(nullptr), transform(nullptr), frame({ 0,0 }), opacity(1.0f), isReverse(false), isCull(false)
{
	this->object = object;
	transform = object->GetComponent<Transform>();
}


Sprite::~Sprite()
{
}

HRESULT Sprite::Init(string nickName, D2D_POINT_2L frame)
{
	imageInfo = _IMAGE->FindImage(nickName);
	this->frame = frame;

	return S_OK;
}

void Sprite::Release(void)
{
	imageInfo = nullptr;
}

void Sprite::Update(void)
{
	D2D_RECT_F cullWindow;
	if (transform->GetMyObject()->GetLayer() == LAYER::UI) {
		cullWindow = MakeRect({ 0,0 }, { WINSIZEX, WINSIZEY });
	}
	else {
		cullWindow = MakeRect({ _CAMERA->x,_CAMERA->y }, { WINSIZEX, WINSIZEY });
	}

	isCull = !IsInRect(transform->GetRect(), cullWindow);
}

void Sprite::Render(void)
{
	if (!imageInfo || isCull) return;

	ImageInfo::LPIMAGE_INFO imgInfo = this->imageInfo->GetImageInfo();
	D2D_POINT_2F pos = transform->GetWorldPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();
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

	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation;

	if (transform->GetMyObject()->GetLayer() == LAYER::UI) {
		dxLocation = MakeRect(pos, size, pivot);
	}
	else {
		dxLocation = MakeRect({ pos.x + _CAMERA->x, pos.y + _CAMERA->y }
		, size, pivot);
	}

	//���� �̹��� ������
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
