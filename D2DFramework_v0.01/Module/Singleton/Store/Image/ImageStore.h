#pragma once
#include "../Module/Singleton/SingletonBase.h"
#include <map>
#include "../Module/Image/ImageModule.h"

class ImageStore : public SingletonBase<ImageStore>
{
private:
	map<string, ImageModule*> mImage;
	typedef map<string, ImageModule*>::iterator mIter;

public:
	ImageStore();
	~ImageStore();

	ImageModule* CreateImage(string nickName, string fileName, float width = 0.0f, float height = 0.0f);
	ImageModule* CreateFrameImage(string nickName, string fileName, int maxFrameX, int maxFrameY, float width = 0.0f, float height = 0.0f);
	ImageModule* FindImage(string nickName);
};

