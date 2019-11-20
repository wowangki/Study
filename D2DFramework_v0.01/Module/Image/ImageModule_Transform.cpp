#include "stdafx.h"
#include "ImageModule.h"
#include "../Component/Transform/Transform.h"


void ImageModule::Render(Transform * transform, float opacity)
{
	D2D_POINT_2F pos = transform->GetPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();

	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = MakeRect(
		{ pos.x + _CAMERA->x, pos.y + _CAMERA->y },
		size,
		pivot);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(0.0f, 0.0f,
		imageInfo->imageSize.width,
		imageInfo->imageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(Transform * transform, D2D_POINT_2L frame, bool isReverse, float opacity)
{
	D2D_POINT_2F pos = transform->GetPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();
	float degree = RadianToDegree(transform->GetAngle());

	if (imageInfo == nullptr) return;
	if (size.width == 0.0f || size.height == 0.0f) {
		size.width = imageInfo->frameImageSize.width;
		size.height = imageInfo->frameImageSize.height;
	}

	D2D_POINT_2F dxPoint = GetDxPoint(pos, size, pivot);
	Matrix3x2F dxMatrix;

	if (isReverse) dxMatrix = Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint) * Matrix3x2F::Rotation(degree, dxPoint);
	else dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);

	_RenderTarget->SetTransform(dxMatrix);

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = MakeRect(
		{ pos.x + _CAMERA->x, pos.y + _CAMERA->y },
		size,
		pivot);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		frame.x * imageInfo->frameImageSize.width,
		frame.y * imageInfo->frameImageSize.height,
		(frame.x + 1) * imageInfo->frameImageSize.width,
		(frame.y + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	_RenderTarget->SetTransform(Matrix3x2F::Identity());
}

void ImageModule::EffectFrameRender(Transform * transform, D2D_POINT_2L frame, float opacity)
{
	D2D_POINT_2F pos = transform->GetPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();

	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = MakeRect(pos, size, pivot);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		frame.x * imageInfo->frameImageSize.width,
		frame.y * imageInfo->frameImageSize.height,
		(frame.x + 1) * imageInfo->frameImageSize.width,
		(frame.y + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::UIFrameRender(Transform * transform, D2D_POINT_2L frame, float opacity)
{
	D2D_POINT_2F pos = transform->GetPos();
	D2D_SIZE_F size = transform->GetSize();
	PIVOT pivot = transform->GetPivot();

	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = MakeRect(pos, size, pivot);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		frame.x * imageInfo->frameImageSize.width,
		frame.y * imageInfo->frameImageSize.height,
		(frame.x + 1) * imageInfo->frameImageSize.width,
		(frame.y + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}


D2D_POINT_2F ImageModule::GetDxPoint(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot)
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
