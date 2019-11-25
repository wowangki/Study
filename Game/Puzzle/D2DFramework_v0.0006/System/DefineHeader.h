#pragma once

//SAFE DELETE, RELEASE
#define SafeRelease(p) { if(p) {(p)->Release(); (p) = nullptr; }}
#define SafeDelete(p) { if(p) delete (p); (p) = nullptr; }
#define SafeDeleteClass(p) { if(p) { (p)->Release(); delete (p); } (p) = nullptr; }
#define SafeDeleteArray(p) { if(p) delete[] (p); (p) = nullptr; }

//MOUSE POINT (LPARAM)
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

#define ArrSize(p) { sizeof(p) / sizeof(*p) }
#define PathImage(p) { std::string("../Image/").append(p) }
#define PathSound(p) { std::string("../Sound/").append(p) }

#ifndef Assert
#if defined(DEBUG) || defined(_DEBUG)
#define Assert(b) do { if (!(b)) {OutputDebugStringA("Assert : " #b "\n");}} while (0)
#else
#define Assert(b)
#endif	// DEBUG || _DEBUG
#endif

/*
	crtdbg.h ?
	마이크로소프트에서 지원하는 CRT 라이브러리
	이전에 할당한 메모리를 내가 깜빡하고 해제하지 못하였을 경우 발생하는 문제
	(메모리 누수량이 많아질 경우 메모리 고갈로 인한 응용 프로그램 충돌 등등.. )
	를 방지하고자 '메모리 누수 탐지 기능' 을 사용한다 (덤프 메모리)

	헤더를 추가하고 <crtdbg.h>
	밑의 전처리기는 문제 코드, 파일 위치, 코드 라인 을 표시할 수 있도록 정의
*/
#include <crtdbg.h>
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif