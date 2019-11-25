#pragma once
#include "../SingletonBase.h"
#include <map>

class FontManager : public SingletonBase<FontManager>
{
private:
	typedef map<string, IDWriteTextFormat*> _mFont;
	typedef _mFont::iterator mIter;

	_mFont mFont;

public:
	FontManager();
	~FontManager();

	void Create(string nickName, wstring fontName, float fontSize,
		DWRITE_TEXT_ALIGNMENT type = DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	void Render(string text, D2D_RECT_F rc, ID2D1SolidColorBrush* brush = nullptr, string nickName = "DEFAULT");
	void Render(wstring text, D2D_RECT_F rc, ID2D1SolidColorBrush* brush = nullptr, string nickName = "DEFAULT");

	void SetFontSize(string nickName, float fontSize);
};

