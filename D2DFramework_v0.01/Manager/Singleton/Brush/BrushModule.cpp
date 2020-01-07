#include "stdafx.h"
#include "BrushModule.h"


BrushModule::BrushModule()
{
	CreateBrush("RED", RGB(255, 0, 0));
	CreateBrush("BLUE", RGB(0, 0, 255));
	CreateBrush("GREEN", RGB(0, 255, 0));
	CreateBrush("MAGENTA", RGB(255, 0, 255));
	CreateBrush("CYAN", RGB(0, 255, 255));
	CreateBrush("YELLOW", RGB(255, 255, 0));
	CreateBrush("WHITE", RGB(255, 255, 255));
	CreateBrush("BLACK", RGB(0, 0, 0));
	CreateBrush("GRAY", RGB(125, 125, 125));
	CreateBrush("COLLIDER", RGB(255, 0, 0));
	CreateBrush("TRANSFORM", RGB(0, 255, 0));
	CreateBrush("CAMERA", RGB(255, 255, 255));
	CreateBrush("IMAGE", RGB(0, 0, 255));
}


BrushModule::~BrushModule()
{
	for (auto& p : mBrush)
		SafeRelease(p.second);
}

HRESULT BrushModule::CreateBrush(string nickName, COLORREF color, float opacity)
{
	ID2D1SolidColorBrush* pTemp = nullptr;
	UINT col = (((BYTE)GetBValue(color)) |
		((WORD)((BYTE)GetGValue(color))) << 8 |
		(((DWORD)(BYTE)(GetRValue(color))) << 16));

	D2D1_COLOR_F c = ColorF(col, opacity);

	if (FAILED(_RenderTarget->CreateSolidColorBrush(c, &pTemp)))
		return E_FAIL;

	mBrush.insert(make_pair(nickName, pTemp));

	return S_OK;
}

ID2D1SolidColorBrush * BrushModule::GetBrush(string nickName)
{
	mIter iter = mBrush.find(nickName);
	if (iter == mBrush.end()) return nullptr;

	return iter->second;
}
