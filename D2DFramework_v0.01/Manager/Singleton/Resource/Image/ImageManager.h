#pragma once
#include "../Manager/Singleton/SingletonBase.h"
#include <map>

class ImageInfo;
class ImageManager : public SingletonBase<ImageManager>
{
private:
	map<string, ImageInfo*> mImage;
	typedef map<string, ImageInfo*>::iterator mIter;

public:
	ImageManager();
	~ImageManager();

	ImageInfo* CreateImage(string nickName, string fileName, D2D_POINT_2L maxFrame = { 1,1 });
	ImageInfo* FindImage(string nickName);
};

