#pragma once
#include "../SingletonBase.h"
#include <map>

class BrushModule : public SingletonBase<BrushModule>
{
private:
	typedef map<string, ID2D1SolidColorBrush*> _mBrush;
	typedef _mBrush::iterator mIter;
	_mBrush mBrush;

public:
	BrushModule();
	~BrushModule();

	HRESULT CreateBrush(string nickName, COLORREF color, float opacity = 1.0f);
	ID2D1SolidColorBrush* GetBrush(string nickName);
};

