//====================== 2019.12.07 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Image Info ============================//

#pragma once
class ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();

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

public:
	HRESULT CreateImage(string fileName, D2D_POINT_2L maxFrame = { 1,1 });
	void Release(void);

	inline LPIMAGE_INFO GetImageInfo(void) const { return imageInfo; }
	inline D2D_SIZE_F GetImgSize(void) const { return imageInfo->imageSize; }
	inline D2D_SIZE_F GetFrameImgSize(void) const { return imageInfo->frameImageSize; }
	inline D2D_POINT_2L GetMaxFrame(void) const { return { imageInfo->maxFrameX, imageInfo->maxFrameY }; }
};

