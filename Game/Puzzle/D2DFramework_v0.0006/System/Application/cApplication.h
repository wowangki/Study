#pragma once
class cApplication
{
public:
	HRESULT CreateDevice(HINSTANCE, int);

public:
	cApplication();
	virtual ~cApplication();

	virtual HRESULT Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

