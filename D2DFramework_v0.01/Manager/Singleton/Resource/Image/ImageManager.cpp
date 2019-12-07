#include "stdafx.h"
#include "ImageManager.h"
#include "ImageInfo/ImageInfo.h"

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	mIter iter = mImage.begin();
	
	for (iter; iter != mImage.end(); ++iter) {
		SafeDeleteClass(iter->second);
	}
}

ImageInfo * ImageManager::CreateImage(string nickName, string fileName, D2D_POINT_2L maxFrame)
{
	ImageInfo* img = FindImage(nickName);
	if (img != nullptr) return img;

	img = new ImageInfo;
	img->CreateImage(fileName, maxFrame);

	mImage.insert(make_pair(nickName, img));

	return img;
}

ImageInfo * ImageManager::FindImage(string nickName)
{
	if (mImage.empty()) return nullptr;
	mIter iter = mImage.begin();

	for (iter; iter != mImage.end(); ++iter) {
		if (iter->first == nickName)
			return iter->second;
	}

	return nullptr;
}
