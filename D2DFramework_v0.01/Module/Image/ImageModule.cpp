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

	//WIC�� ����ϱ� ���� Factory ��ü ����
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imageInfo->pWicFactory));
	Assert(hr == S_OK);

	//�̹����� �о�´�.
	hr = imageInfo->pWicFactory->CreateDecoderFromFilename(
		this->fileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(imageInfo->pWicDecoder));

	//�̹��� �ʱ�ȭ ���н� �˾�â ����
	if (FAILED(hr)) {
		TCHAR errorStr[256];
		_stprintf_s(errorStr, L"�̹��� ������ �߸��Ǿ����ϴ�.\nFileName : %s",
			this->fileName.c_str());

		MessageBox(AppDesc._hWnd, errorStr, NULL, MB_OK);
		Release();
		return hr;
	}
	
	//ù ��° �������� ����� �� �ִ� ��ü ����
	hr = imageInfo->pWicDecoder->GetFrame(0, &imageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//Factory ��ü�� ����Ͽ� �̹��� ��ȯ ��ü�� ����
	hr = imageInfo->pWicFactory->CreateFormatConverter(&imageInfo->pWicConverter);
	Assert(hr == S_OK);

	//�ý����� ��� ������ ��Ʈ�� �������� ��ȯ
	hr = imageInfo->pWicConverter->Initialize(
		imageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//��ȯ�� �̹��� ������ D2D�� ����� ��Ʈ�� ����
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		imageInfo->pWicConverter,
		nullptr,
		&imageInfo->pBitmap
	);

	//�̹����� ���������� �������� �ʾ��� ���
	if (imageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//�̹��� ���� ������� ����ϰ� ���� ���
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

	//WIC�� ����ϱ� ���� Factory ��ü ����
	CoInitialize(nullptr);
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imageInfo->pWicFactory));
	Assert(hr == S_OK);
	
	//�̹����� �о�´�.
	hr = imageInfo->pWicFactory->CreateDecoderFromFilename(
		this->fileName.c_str(),
		nullptr,
		GENERIC_READ,
		WICDecodeMetadataCacheOnDemand,
		&(imageInfo->pWicDecoder));

	//�̹��� �ʱ�ȭ�� �����ϸ� �˾�â ����
	if (FAILED(hr)) {
		TCHAR errorStr[256];
		_stprintf_s(errorStr, L"�̹��� ������ �߸��Ǿ����ϴ�.\nFileName : %s",
			this->fileName.c_str());

		MessageBox(AppDesc._hWnd, errorStr, NULL, MB_OK);
		Release();
		return hr;
	}

	//ù ��° �������� ����� �� �ִ� ��ü ����
	hr = imageInfo->pWicDecoder->GetFrame(0, &imageInfo->pWicFrameDecoder);
	Assert(hr == S_OK);

	//Factory ��ü�� ����Ͽ� �̹��� ��ȯ ��ü�� ����
	hr = imageInfo->pWicFactory->CreateFormatConverter(&imageInfo->pWicConverter);
	Assert(hr == S_OK);

	//�ý����� ��� ������ ��Ʈ�� �������� ��ȯ
	hr = imageInfo->pWicConverter->Initialize(
		imageInfo->pWicFrameDecoder,
		GUID_WICPixelFormat32bppPRGBA,
		WICBitmapDitherTypeNone,
		nullptr,
		0.0f,
		WICBitmapPaletteTypeCustom
	);

	//��ȯ�� �̹��� ������ D2D�� ����� ��Ʈ�� ����
	hr = _RenderTarget->CreateBitmapFromWicBitmap(
		imageInfo->pWicConverter,
		nullptr,
		&imageInfo->pBitmap
	);

	//�̹����� ���������� �������� �ʾ��� ���
	if (imageInfo->pBitmap == nullptr) {
		Release();
		return E_FAIL;
	}

	//�̹��� ���� ������� ����ϰ� ���� ���
	if (width == 0.0f || height == 0.0f) {
		imageInfo->imageSize = imageInfo->pBitmap->GetSize();
	}
	else {
		imageInfo->imageSize.width = width;
		imageInfo->imageSize.height = height;
	}

	//������ �̹��� ���
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
	
	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAMERA->x,
		y + _CAMERA->y,
		x + _CAMERA->x + imageInfo->imageSize.width,
		y + _CAMERA->y + imageInfo->imageSize.height
	);

	//���� �̹��� ������
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
	
	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAMERA->x,
		y + _CAMERA->y,
		x + scaleX + _CAMERA->x,
		y + scaleY + _CAMERA->y
	);

	//���� �̹��� ������
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

	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + imageInfo->imageSize.width,
		y + imageInfo->imageSize.height
	);

	//���� �̹��� ������
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
	
	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + scaleX,
		y + scaleY
	);

	//���� �̹��� ������
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

	//�ѷ��� �̹��� ��ġ
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

	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x + _CAMERA->x,
		y + _CAMERA->y,
		x + scaleX + _CAMERA->x,
		y + scaleY + _CAMERA->y
	);

	//���� �̹��� ������
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

	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(x, y,
		x + scaleX,
		y + scaleY
	);

	//���� �̹��� ������
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

	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		pos.x,
		pos.y,
		pos.x + imageInfo->frameImageSize.width,
		pos.y + imageInfo->frameImageSize.height
	);

	//���� �̹��� ������
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

	//�ѷ��� �̹��� ��ġ
	D2D1_RECT_F dxLocation = RectF(
		x,
		y,
		x + scaleX,
		y + scaleY
	);

	//���� �̹��� ������
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
