// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ Ư�� ���� ������ ��� �ִ�
// ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <string>
#include <memory>
#include <time.h>
using namespace std;

// Direct2D Header File
#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include <d2d1helper.h>

using namespace D2D1;

// �ȵ� �� �ּ�ó��
#pragma comment(lib, "WindowsCodecs.lib")
#include <wincodec.h>

// PNG incoder
#pragma comment(lib, "dwrite.lib")
#include <dwrite.h>

//D2D1 Application Header
#include "Application/DX2DApp.h"

struct App_Desc {
	HINSTANCE _hInstance;
	HWND _hWnd;
	float width;
	float height;
};

//extern
//���α׷� ��ü�� �������� ����
//stack�� ����
//���� ��������� ��
extern App_Desc AppDesc;
extern POINT	AppMouse;

//WINDOW NAME
#define ApplicationName TEXT("Direct2D Build")
//WIN SIZE
#define WINSIZEX AppDesc.width
#define WINSIZEY AppDesc.height

//============================== SYSTEM BASIC =========================== //

//============================== Define Header ========================== //
#include "DefineHeader.h"
#include "../Utill/Utillity.h"
using namespace nString;
using namespace nRadian;
using namespace nFigure;

#include "../Utill/CollisionHelper.h"
using namespace nCollision;

#include "../Utill/SingletonHeader.h"