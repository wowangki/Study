#pragma once

class DX2DApp
{
public:
	ID2D1Factory*			pDirect2dFactory;
	ID2D1HwndRenderTarget*	pRenderTarget;
	ID2D1SolidColorBrush*	pDefaultBrush;

	IDWriteFactory*			pWriteFactory;

public:
	DX2DApp();
	bool CreateFactory(void);
	bool CreateDirect2dResources(void);
	void Release(void);

	void BeginDraw(void);
	void EndDraw(void);
	void OnResize(UINT width, UINT height);

	void ChangeColor(const COLORREF& color, float opacity = 1.0f);
	void ChangeColor(const D2D1_COLOR_F& color);

public:
	//디자인 패턴!
	static DX2DApp* GetInstance() {
		static DX2DApp Instance;
		return &Instance;
	}
};

#define _Device		DX2DApp::GetInstance()
#define _RenderTarget	DX2DApp::GetInstance()->pRenderTarget
#define _Factory		DX2DApp::GetInstance()->pDirect2dFactory
