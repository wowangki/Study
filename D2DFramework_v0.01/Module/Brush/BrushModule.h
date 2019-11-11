#pragma once
#include "../SingletonBase.h"
#include <map>

namespace nBrushColor {
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
}

class BrushModule : public SingletonBase<BrushModule>
{	
private:
	typedef map<nBrushColor::BRUSH_COLOR, pair<string, ID2D1SolidColorBrush*>> _mBrush;
	typedef _mBrush::iterator mIter;
	_mBrush mBrush;

public:
	BrushModule();
	~BrushModule();

	HRESULT CreateBrush(string nickName, COLORREF color, nBrushColor::BRUSH_COLOR type = nBrushColor::CUSTOM, float opacity = 1.0f);
	ID2D1SolidColorBrush* GetBrush(nBrushColor::BRUSH_COLOR type, string nickName = "DEFAULT");
};

