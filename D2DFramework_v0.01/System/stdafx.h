// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 특정 포함 파일이 들어 있는
// 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
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

// 안될 시 주석처리
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
//프로그램 전체에 전역으로 선언
//stack에 쌓임
//마구 사용하지말 것
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