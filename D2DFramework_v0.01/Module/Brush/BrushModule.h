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
	
	//Enum으로만 찾아도 충분할듯하고 네임스페이스에 생성한거면 
	//namespace nBrushColor {
	//	enum Enum {
	//		BLACK,
	//		GRAY,
	//		WHITE,
	//		RED,
	//		GREEN,
	//		BLUE,
	//		YELLOW,
	//		MAGENTA,
	//		CYAN,
	//		CUSTOM
	//	};
	//}
	//이런식으로 하는것도 나중에 사용하기 편함 defaultBrushColor
	
	ID2D1SolidColorBrush* GetBrush(nBrushColor::BRUSH_COLOR type, string nickName = "DEFAULT");
};

