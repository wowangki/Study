#include "stdafx.h"
#include "FontManager.h"

FontManager::FontManager()
{
	IDWriteTextFormat* temp = nullptr;

	_Device->pWriteFactory->CreateTextFormat(
		L"휴먼굴림체",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		14.0f, L"",
		&temp
	);

	temp->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

	mFont.insert(make_pair("DEFAULT", temp));
}

FontManager::~FontManager()
{
	mIter iter = mFont.begin();
	for (iter; iter != mFont.end(); ++iter)
	{
		SafeRelease(iter->second);
	}

	//	auto ?
	//	컴파일 시간에 이 녀석이 무슨 형식인지 판별한다
	//	컴파일 시간이 길어진다
	/*for (auto& p : mFont) {
		SafeRelease(p.second);
	}*/

	mFont.clear();
}

void FontManager::Create(string nickName, wstring fontName, float fontSize, DWRITE_TEXT_ALIGNMENT type)
{
	IDWriteTextFormat* pTemp = nullptr;

	if (FAILED(_Device->pWriteFactory->CreateTextFormat(
		fontName.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize, L"",
		&pTemp
	))) {
		MessageBox(AppDesc._hWnd, L"폰트를 추가할 수 없습니다!", nullptr, MB_OK);
		return;
	}

	pTemp->SetTextAlignment(type);
	mFont.insert(make_pair(nickName, pTemp));
}

void FontManager::Render(string text, D2D_RECT_F rc, ID2D1SolidColorBrush * brush, string nickName)
{
	if (brush == nullptr) {
		_RenderTarget->DrawTextW(StringToWstring(text).c_str(),
			(UINT32)text.size(),
			mFont[nickName],
			rc,
			_Device->pDefaultBrush);
	}
	else {
		_RenderTarget->DrawTextW(StringToWstring(text).c_str(),
			(UINT32)text.size(),
			mFont[nickName],
			rc,
			brush);
	}
}

void FontManager::Render(wstring text, D2D_RECT_F rc, ID2D1SolidColorBrush * brush, string nickName)
{
	if (brush == nullptr) {
		_RenderTarget->DrawTextW(text.c_str(),
			(UINT32)text.size(),
			mFont[nickName],
			rc,
			_Device->pDefaultBrush);
	}
	else {
		_RenderTarget->DrawTextW(text.c_str(),
			(UINT32)text.size(),
			mFont[nickName],
			rc,
			brush);
	}
}

void FontManager::SetFontSize(string nickName, float fontSize)
{
	mIter iter = mFont.find(nickName);
	if (iter == mFont.end())	return;

	wstring fontNickName = StringToWstring(iter->first);

	SafeRelease(iter->second);

	_Device->pWriteFactory->CreateTextFormat(
		fontNickName.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize, L"",
		&iter->second
	);
}
