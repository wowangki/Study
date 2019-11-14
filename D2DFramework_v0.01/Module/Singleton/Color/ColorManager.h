#pragma once
#include "../SingletonBase.h"
#include <map>

class ColorManager : public SingletonBase<ColorManager>
{	
public:
	enum BRUSH_COLOR {
		BLACK,
		GRAY,
		WHITE,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		MAGENTA,
		CYAN,
		CUSTOM
	};

private:
	typedef map<BRUSH_COLOR, pair<string, ID2D1SolidColorBrush*>> _mBrush;
	typedef _mBrush::iterator mIter;
	_mBrush mBrush;


public:
	ColorManager();
	~ColorManager();

	HRESULT CreateBrush(string nickName, COLORREF color, BRUSH_COLOR type = CUSTOM, float opacity = 1.0f);
	ID2D1SolidColorBrush* GetBrush(BRUSH_COLOR type, string nickName = "DEFAULT");
};

