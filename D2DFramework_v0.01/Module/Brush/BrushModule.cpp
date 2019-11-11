#include "stdafx.h"
#include "BrushModule.h"


BrushModule::BrushModule()
{
	//Basic Color Create

	CreateBrush("BLACK", RGB(0, 0, 0), nBrushColor::BLACK);
	CreateBrush("GRAY", RGB(125, 125, 125), nBrushColor::GRAY);
	CreateBrush("WHITE", RGB(255, 255, 255), nBrushColor::WHITE);
	CreateBrush("RED", RGB(255, 0, 0), nBrushColor::RED);
	CreateBrush("GREEN", RGB(0, 255, 0), nBrushColor::GREEN);
	CreateBrush("BLUE", RGB(0, 0, 255), nBrushColor::BLUE);
	CreateBrush("YELLOW", RGB(255, 255, 0), nBrushColor::YELLOW);
	CreateBrush("MAGENTA", RGB(255, 0, 255), nBrushColor::MAGENTA);
	CreateBrush("CYAN", RGB(0, 255, 255), nBrushColor::CYAN);
}


BrushModule::~BrushModule()
{
	for (auto& p : mBrush)
		SafeRelease(p.second.second);
}

HRESULT BrushModule::CreateBrush(string nickName, COLORREF color, nBrushColor::BRUSH_COLOR type, float opacity)
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

ID2D1SolidColorBrush * BrushModule::GetBrush(nBrushColor::BRUSH_COLOR type, string nickName)
{
	mIter iter = mBrush.find(type);
	if (iter == mBrush.end()) return nullptr;

	if (iter->first != nBrushColor::CUSTOM) {
		return iter->second.second;
	}
	else {
		if (iter->second.first == nickName)
			return iter->second.second;
	}
}