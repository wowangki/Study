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
	����ũ�μ���Ʈ���� �����ϴ� CRT ���̺귯��
	������ �Ҵ��� �޸𸮸� ���� �����ϰ� �������� ���Ͽ��� ��� �߻��ϴ� ����
	(�޸� �������� ������ ��� �޸� ���� ���� ���� ���α׷� �浹 ���.. )
	�� �����ϰ��� '�޸� ���� Ž�� ���' �� ����Ѵ� (���� �޸�)

	����� �߰��ϰ� <crtdbg.h>
	���� ��ó����� ���� �ڵ�, ���� ��ġ, �ڵ� ���� �� ǥ���� �� �ֵ��� ����
*/
#include <crtdbg.h>
#ifdef _DEBUG
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif