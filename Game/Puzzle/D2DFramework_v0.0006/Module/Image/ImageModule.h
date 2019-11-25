#pragma once
#include "../Component/Component.h"

class GameObject;
class Transform;
class ImageModule
{
public:
	ImageModule();
	~ImageModule();

	typedef struct IMAGE_INFO {
		IMAGE_INFO()
			:
			pWicFactory(nullptr),
			pWicConverter(nullptr),
			pWicDecoder(nullptr),
			pWicFrameDecoder(nullptr),
			pBitmap(nullptr),
			imageSize(D2D1_SIZE_F()),
			bufferSize(1.0f),
			frameImageSize(D2D1_SIZE_F()),
			maxFrameX(0), maxFrameY(0)
		{};

		IWICImagingFactory*		pWicFactory;
		IWICFormatConverter*	pWicConverter;
		IWICBitmapDecoder*		pWicDecoder;
		IWICBitmapFrameDecode*	pWicFrameDecoder;
		ID2D1Bitmap*			pBitmap;

		D2D1_SIZE_F				imageSize;
		float					bufferSize;

		D2D1_SIZE_F				frameImageSize;
		int						maxFrameX;
		int						maxFrameY;
	}*LPIMAGE_INFO;

private:
	LPIMAGE_INFO imageInfo;
	wstring fileName;

// Release
public:
	void Release(void);

// Create
public:
	HRESULT CreateImage(string fileName, float width = 0.0f, float height = 0.0f);
	HRESULT CreateFrameImage(string fileName, int maxFrameX, int maxFrameY, float width = 0.0f, float height = 0.0f);

//Render
public:
	void Render(float opacity = 1.0f);
	void Render(float x, float y, float opacity = 1.0f);
	void Render(float x, float y, float scaleX, float scaleY, float opacity = 1.0f);
	
	void CropRender(float x, float y, float startX, float startY, float endX, float endY, float opacity = 1.0f);
	void CropRender(float x, float y, float startX, float startY, float endX, float endY, float scaleX, float scaleY, float opacity = 1.0f);

	void FrameRender(float x, float y, int cfX, int cfY, float opacity = 1.0f);
	void FrameRender(float x, float y, int cfX, int cfY, float scaleX, float scaleY, float opacity = 1.0f);
	void FrameRender(float x, float y, int cfX, int cfY, float degree, bool isReverse, float scaleX = 0.0f, float scaleY = 0.0f, float opacity = 1.0f);

	void EffectFrameRender(POINTF pos, int cfX, int cfY, float opacity = 1.0f);

	void UiFrameRender(float x, float y, int cfX, int cfY, float scaleX, float scaleY, float opacity = 1.0f);

//Render by Transform 2019.11.21 ==============================================//
public:
	void Render(Transform* transform, float opacity = 1.0f);
	void FrameRender(Transform* transform, D2D_POINT_2L frame, bool isReverse, float opacity = 1.0f);
	void EffectFrameRender(Transform* transform, D2D_POINT_2L frame, float opacity = 1.0f);
	void UIFrameRender(Transform* transform, D2D_POINT_2L frame, float opacity = 1.0f);

private:
	D2D_POINT_2F GetDxPoint(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot);

//=============================================================================//

// Getter & Setter
public:
	inline float GetWidth() { return imageInfo->imageSize.width; }
	inline float GetHeight() { return imageInfo->imageSize.height; }

	inline float GetFrameWidth() { return imageInfo->frameImageSize.width; }
	inline float GetFrameHeight() { return imageInfo->frameImageSize.height; }

	inline int GetMaxFrameX() { return imageInfo->maxFrameX; }
	inline int GetMaxFrameY() { return imageInfo->maxFrameY; }

	inline D2D_RECT_F GetRect(float x, float y) {
		return RectF(x, y,
			x + imageInfo->imageSize.width,
			y + imageInfo->imageSize.height);
	}
	
};

