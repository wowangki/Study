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
	imageInfo->imageSize = imageInfo->pBitmap->GetSize();

	//프레임 이미지 계산
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
