#include "stdafx.h"
#include "ImageStore.h"


ImageStore::ImageStore()
{
}


ImageStore::~ImageStore()
{
	mIter iter = mImage.begin();
	
	for (iter; iter != mImage.end(); ++iter) {
		iter->second->Release();
		SafeDelete(iter->second);
	}
}

ImageModule * ImageStore::CreateImage(string nickName, string fileName, float width, float height)
{
	ImageModule* img = FindImage(nickName);
	if (img != nullptr) return img;

	img = new ImageModule;
	img->CreateImage(fileName, width, height);

	mImage.insert(make_pair(nickName, img));

	return img;
}

ImageModule * ImageStore::CreateFrameImage(string nickName, string fileName, int maxFrameX, int maxFrameY, float width, float height)
{
	ImageModule* img = FindImage(nickName);
	if (img != nullptr) return img;

	img = new ImageModule;
	img->CreateFrameImage(fileName, maxFrameX, maxFrameY, width, height);

	mImage.insert(make_pair(nickName, img));

	return img;
}

ImageModule * ImageStore::FindImage(string nickName)
{
	if (mImage.empty()) return nullptr;
	mIter iter = mImage.begin();

	for (iter; iter != mImage.end(); ++iter) {
		if (iter->first == nickName)
			return iter->second;
	}

	return nullptr;
}
