#include "stdafx.h"
#include "ImageManager.h"
#include "ImageModule.h"

ImageManager::ImageManager()
{
}


ImageManager::~ImageManager()
{
	mIter iter = mImage.begin();
	
	for (iter; iter != mImage.end(); ++iter) {
		iter->second->Release();
		SafeDelete(iter->second);
	}
}

ImageModule * ImageManager::CreateImage(string nickName, string fileName, float width, float height)
{
	ImageModule* img = FindImage(nickName);
	if (img != nullptr) return img;

	img = new ImageModule;
	img->CreateImage(fileName, width, height);

	mImage.insert(make_pair(nickName, img));

	return img;
}

ImageModule * ImageManager::CreateFrameImage(string nickName, string fileName, int maxFrameX, int maxFrameY, float width, float height)
{
	ImageModule* img = FindImage(nickName);
	if (img != nullptr) return img;

	img = new ImageModule;
	img->CreateFrameImage(fileName, maxFrameX, maxFrameY, width, height);

	mImage.insert(make_pair(nickName, img));

	return img;
}

ImageModule * ImageManager::FindImage(string nickName)
{
	if (mImage.empty()) return nullptr;
	mIter iter = mImage.begin();

	for (iter; iter != mImage.end(); ++iter) {
		if (iter->first == nickName)
			return iter->second;
	}

	return nullptr;
}
