#include "stdafx.h"
#include "ImageModule.h"


ImageModule::ImageModule()
	:imageInfo(nullptr)
{
}


ImageModule::~ImageModule()
{
}

void ImageModule::Release(void)
{
	SafeRelease(imageInfo->pBitmap);
	SafeRelease(imageInfo->pWicFrameDecoder);
	SafeRelease(imageInfo->pWicDecoder);
	SafeRelease(imageInfo->pWicConverter);
	SafeRelease(imageInfo->pWicFactory);

	SafeDelete(imageInfo);
}

HRESULT ImageModule::CreateImage(string fileName, float width, float height)
{
	if (fileName == "") return E_FAIL;
	this->fileName = StringToWstring(fileName);

	if (imageInfo != nullptr) Release();
	imageInfo = new IMAGE_INFO();

	//WIC를 사용하기 위해 Factory 객체 생성
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imageInfo->pWicFactory));
	Assert(hr == S_OK);

	//이미지를 읽어온다.
	hr = imageInfo->pWicFactory->CreateDecoderFromFilename(
		this->fileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(imageInfo->pWicDecoder));

	//이미지 초기화 실패시 팝업창 오픈
	if (FAILED(hr)) {
		TCHAR errorStr[256];
		_stprintf_s(errorStr, L"이미지 파일이 잘못되었습니다.\nFileName : %s",
			this->fileName.c_str());

		MessageBox(AppDesc._hWnd, errorStr, NULL, MB_OK);
		Release();
		return hr;
	}
	
	//첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = imageInfo->pWicDecoder->GetFrame(0, &imageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//Factory 객체를 사용하여 이미지 변환 객체를 생성
	hr = imageInfo->pWicFactory->CreateFormatConverter(&imageInfo->pWicConverter);
	Assert(hr == S_OK);

	//시스템이 사용 가능한 비트맵 형식으로 변환
	hr = imageInfo->pWicConverter->Initialize(
		imageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//변환된 이미지 형식을 D2D에 사용할 비트맵 생성
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		imageInfo->pWicConverter,
		nullptr,
		&imageInfo->pBitmap
	);

	//이미지가 정상적으로 생성되지 않았을 경우
	if (imageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//이미지 원본 사이즈로 사용하고 싶은 경우
	if (width == 0.0f || height == 0.0f) {
		imageInfo->imageSize = imageInfo->pBitmap->GetSize();
	}
	else {
		imageInfo->imageSize.width = width;
		imageInfo->imageSize.height = height;
	}

	return S_OK;
}

HRESULT ImageModule::CreateFrameImage(string fileName, int maxFrameX, int maxFrameY, float width, float height)
{
	if (fileName == "") return E_FAIL;
	this->fileName = StringToWstring(fileName);

	if (imageInfo != nullptr) Release();
	imageInfo = new IMAGE_INFO();

	//WIC를 사용하기 위해 Factory 객체 생성
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imageInfo->pWicFactory));
	Assert(hr == S_OK);
	
	//이미지를 읽어온다.
	hr = imageInfo->pWicFactory->CreateDecoderFromFilename(
		this->fileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(imageInfo->pWicDecoder));

	//이미지 초기화가 실패하면 팝업창 띄우기
	if (FAILED(hr)) {
		TCHAR errorStr[256];
		_stprintf_s(errorStr, L"이미지 파일이 잘못되었습니다.\nFileName : %s",
			this->fileName.c_str());

		MessageBox(AppDesc._hWnd, errorStr, NULL, MB_OK);
		Release();
		return hr;
	}

	//첫 번째 프레임을 사용할 수 있는 객체 구성
	hr = imageInfo->pWicDecoder->GetFrame(0, &imageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//Factory 객체를 사용하여 이미지 변환 객체를 생성
	hr = imageInfo->pWicFactory->CreateFormatConverter(&imageInfo->pWicConverter);
	Assert(hr == S_OK);

	//시스템이 사용 가능한 비트맵 형식으로 변환
	hr = imageInfo->pWicConverter->Initialize(
		imageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//변환된 이미지 형식을 D2D에 사용할 비트맵 생성
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		imageInfo->pWicConverter,
		nullptr,
		&imageInfo->pBitmap
	);

	//이미지가 정상적으로 생성되지 않았을 경우
	if (imageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//이미지 원본 사이즈로 사용하고 싶은 경우
	if (width == 0.0f || height == 0.0f) {
		imageInfo->imageSize = imageInfo->pBitmap->GetSize();
	}
	else {
		imageInfo->imageSize.width = width;
		imageInfo->imageSize.height = height;
	}

	//프레임 이미지 계산
	imageInfo->maxFrameX = maxFrameX;
	imageInfo->maxFrameY = maxFrameY;
	imageInfo->frameImageSize.width = imageInfo->imageSize.width / maxFrameX;
	imageInfo->frameImageSize.height = imageInfo->imageSize.height / maxFrameY;

	return S_OK;
}

void ImageModule::Render(float opacity)
{
	if (imageInfo->pBitmap == nullptr) return;

	D2D1_RECT_F dxLocation = RectF(
		_CAMERA->x,
		_CAMERA->y,
		_CAMERA->x + imageInfo->imageSize.width,
		_CAMERA->y + imageInfo->imageSize.height
	);

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

void ImageModule::Render(float x, float y, float opacity)
{
	if (imageInfo == nullptr) return;
	
	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAMERA->x,
		y + _CAMERA->y,
		x + _CAMERA->x + imageInfo->imageSize.width,
		y + _CAMERA->y + imageInfo->imageSize.height
	);

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

void ImageModule::Render(float x, float y, float scaleX, float scaleY, float opacity)
{
	if (imageInfo == nullptr) return;
	
	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAMERA->x,
		y + _CAMERA->y,
		x + scaleX + _CAMERA->x,
		y + scaleY + _CAMERA->y
	);

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

void ImageModule::CropRender(float x, float y, float startX, float startY, float endX, float endY, float opacity)
{
	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + imageInfo->imageSize.width,
		y + imageInfo->imageSize.height
	);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(startX, startY,
		endX,
		endY
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::CropRender(float x, float y, float startX, float startY, float endX, float endY, float scaleX, float scaleY, float opacity)
{
	if (imageInfo == nullptr) return;
	
	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + scaleX,
		y + scaleY
	);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(startX, startY,
		endX,
		endY);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(float x, float y, int cfX, int cfY, float opacity)
{
	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + imageInfo->frameImageSize.width,
		y + imageInfo->frameImageSize.height
	);

	D2D1_RECT_F dxSize = RectF(
		cfX * imageInfo->frameImageSize.width,
		cfY * imageInfo->frameImageSize.height,
		(cfX + 1) * imageInfo->frameImageSize.width,
		(cfY + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(float x, float y, int cfX, int cfY, float scaleX, float scaleY, float opacity)
{
	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x + _CAMERA->x,
		y + _CAMERA->y,
		x + scaleX + _CAMERA->x,
		y + scaleY + _CAMERA->y
	);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		cfX * imageInfo->frameImageSize.width,
		cfY * imageInfo->frameImageSize.height,
		(cfX + 1) * imageInfo->frameImageSize.width,
		(cfY + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::FrameRender(float x, float y, int cfX, int cfY, float degree, bool isReverse, float scaleX, float scaleY, float opacity)
{
	if (imageInfo == nullptr) return;
	if (scaleX == 0.0f || scaleY == 0.0f) {
		scaleX = imageInfo->frameImageSize.width;
		scaleY = imageInfo->frameImageSize.height;
	}

	D2D_POINT_2F dxPoint = { x + scaleX / 2.0f, y + scaleY / 2.0f };
	Matrix3x2F dxMatrix;

	if (isReverse) dxMatrix = Matrix3x2F::Scale(-1.0f, 1.0f, dxPoint) * Matrix3x2F::Rotation(degree, dxPoint);
	else dxMatrix = Matrix3x2F::Rotation(degree, dxPoint);

	_RenderTarget->SetTransform(dxMatrix);

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + scaleX,
		y + scaleY
	);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		cfX * imageInfo->frameImageSize.width,
		cfY * imageInfo->frameImageSize.height,
		(cfX + 1) * imageInfo->frameImageSize.width,
		(cfY + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);

	_RenderTarget->SetTransform(Matrix3x2F::Identity());
}

void ImageModule::EffectFrameRender(POINTF pos, int cfX, int cfY, float opacity)
{
	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		pos.x,
		pos.y,
		pos.x + imageInfo->frameImageSize.width,
		pos.y + imageInfo->frameImageSize.height
	);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		cfX * imageInfo->frameImageSize.width,
		cfY * imageInfo->frameImageSize.height,
		(cfX + 1) * imageInfo->frameImageSize.width,
		(cfY + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}

void ImageModule::UiFrameRender(float x, float y, int cfX, int cfY, float scaleX, float scaleY, float opacity)
{
	if (imageInfo == nullptr) return;

	//뿌려줄 이미지 위치
	D2D1_RECT_F dxLocation = RectF(
		x,
		y,
		x + scaleX,
		y + scaleY
	);

	//실제 이미지 사이즈
	D2D1_RECT_F dxSize = RectF(
		cfX * imageInfo->frameImageSize.width,
		cfY * imageInfo->frameImageSize.height,
		(cfX + 1) * imageInfo->frameImageSize.width,
		(cfY + 1) * imageInfo->frameImageSize.height
	);

	_RenderTarget->DrawBitmap(imageInfo->pBitmap,
		dxLocation,
		opacity,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		dxSize);
}
