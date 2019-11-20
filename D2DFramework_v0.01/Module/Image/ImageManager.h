#pragma once
#include "../SingletonBase.h"
#include <map>

class ImageModule;
class ImageManager : public SingletonBase<ImageManager>
{
private:
	map<string, ImageModule*> mImage;
	typedef map<string, ImageModule*>::iterator mIter;

public:
	ImageManager();
	~ImageManager();

	ImageModule* CreateImage(string nickName, string fileName, float width = 0.0f, float height = 0.0f);
	ImageModule* CreateFrameImage(string nickName, string fileName, int maxFrameX, int maxFrameY, float width = 0.0f, float height = 0.0f);
	ImageModule* FindImage(string nickName);
};

