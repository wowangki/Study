#include "stdafx.h"
#include "cApplication.h"

App_Desc AppDesc;
POINT AppMouse;

LRESULT cApplication::WndProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (message)
	{
	case WM_MOUSEMOVE:
		AppMouse.x = GET_X_LPARAM(lParam);
		AppMouse.y = GET_Y_LPARAM(lParam);
		break;

	case WM_CLOSE: case WM_QUIT:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

cApplication::cApplication()
{
	AppDesc = {
		nullptr, nullptr,
		800, 600
	};
}


cApplication::~cApplication()
{
	UnregisterClass(ApplicationName, AppDesc._hInstance);
}

HRESULT cApplication::CreateDevice(HINSTANCE hInstance,
	int nCmdShow)
{
	AppDesc._hInstance = hInstance;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof WNDCLASSEX;

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = ApplicationName;
	wcex.lpszClassName = ApplicationName;
	wcex.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

	RegisterClassExW(&wcex);

	if (!_Device->CreateFactory()) return E_FAIL;

	//DPI
	//Dots Per Inch
	//1��ġ�� �ȼ��� � ������ Ȯ��
	FLOAT dpiX, dpiY;
	_Factory->GetDesktopDpi(&dpiX, &dpiY);

	AppDesc._hWnd = CreateWindow(
		ApplicationName,
		ApplicationName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		static_cast<UINT>(ceil(AppDesc.width * dpiX / 96.f)),
		static_cast<UINT>(ceil(AppDesc.height * dpiY / 96.f)),
		nullptr, nullptr, hInstance, this);

	if (!AppDesc._hWnd) return E_FAIL;
	if (!_Device->CreateDirect2dResources()) return E_FAIL;

	ShowWindow(AppDesc._hWnd, nCmdShow);
	UpdateWindow(AppDesc._hWnd);

	return S_OK;
}
