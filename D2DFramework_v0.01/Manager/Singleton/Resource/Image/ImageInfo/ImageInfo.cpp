#include "stdafx.h"
#include "ImageInfo.h"


ImageInfo::ImageInfo()
	:imageInfo(nullptr)
{
}


ImageInfo::~ImageInfo()
{
}

HRESULT ImageInfo::CreateImage(string fileName, D2D_POINT_2L maxFrame)
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
	imageInfo->imageSize = imageInfo->pBitmap->GetSize();

	//������ �̹��� ���
	imageInfo->maxFrameX = maxFrame.x;
	imageInfo->maxFrameY = maxFrame.y;

	imageInfo->frameImageSize.width = imageInfo->imageSize.width / maxFrame.x;
	imageInfo->frameImageSize.height = imageInfo->imageSize.height / maxFrame.y;

	return S_OK;
}

void ImageInfo::Release(void)
{
	SafeRelease(imageInfo->pBitmap);
	SafeRelease(imageInfo->pWicFrameDecoder);
	SafeRelease(imageInfo->pWicDecoder);
	SafeRelease(imageInfo->pWicConverter);
	SafeRelease(imageInfo->pWicFactory);

	SafeDelete(imageInfo);
}
