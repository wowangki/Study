#include "stdafx.h"
#include "ColorManager.h"


ColorManager::ColorManager()
{
	//Basic Color Create

	CreateBrush("BLACK", RGB(0, 0, 0), BLACK);
	CreateBrush("GRAY", RGB(125, 125, 125), GRAY);
	CreateBrush("WHITE", RGB(255, 255, 255), WHITE);
	CreateBrush("RED", RGB(255, 0, 0), RED);
	CreateBrush("GREEN", RGB(0, 255, 0), GREEN);
	CreateBrush("BLUE", RGB(0, 0, 255), BLUE);
	CreateBrush("YELLOW", RGB(255, 255, 0), YELLOW);
	CreateBrush("MAGENTA", RGB(255, 0, 255), MAGENTA);
	CreateBrush("CYAN", RGB(0, 255, 255), CYAN);
}


ColorManager::~ColorManager()
{
	for (auto& p : mBrush)
		SafeRelease(p.second.second);
}

HRESULT ColorManager::CreateBrush(string nickName, COLORREF color, BRUSH_COLOR type, float opacity)
{
	ID2D1SolidColorBrush* pTemp = nullptr;
	UINT col = (((BYTE)GetBValue(color)) |
		((WORD)((BYTE)GetGValue(color))) << 8 |
		(((DWORD)(BYTE)(GetRValue(color))) << 16));

	D2D1_COLOR_F c = ColorF(col, opacity);

	if (FAILED(_RenderTarget->CreateSolidColorBrush(c, &pTemp)))
		return E_FAIL;

	mBrush.insert(make_pair(type, make_pair(nickName, pTemp)));

	return S_OK;
}

ID2D1SolidColorBrush * ColorManager::GetBrush(BRUSH_COLOR type, string nickName)
{
	mIter iter = mBrush.find(type);
	if (iter == mBrush.end()) return nullptr;

	if (iter->first != CUSTOM) {
		return iter->second.second;
	}
	else {
		if (iter->second.first == nickName)
			return iter->second.second;
		else return nullptr;
	}
}