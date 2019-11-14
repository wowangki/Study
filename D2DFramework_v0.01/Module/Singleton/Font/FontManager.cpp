#include "stdafx.h"
#include "FontManager.h"

FontManager::FontManager()
{
	Create("DEFAULT", L"�޸ձ���ü", 10.0f, DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
}

FontManager::~FontManager()
{
	mIter iter = mFont.begin();
	for (iter; iter != mFont.end(); ++iter)
	{
		SafeRelease(iter->second);
	}

	//	auto ?
	//	������ �ð��� �� �༮�� ���� �������� �Ǻ��Ѵ�
	//	������ �ð��� �������
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
		MessageBox(AppDesc._hWnd, L"��Ʈ�� �߰��� �� �����ϴ�!", nullptr, MB_OK);
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
