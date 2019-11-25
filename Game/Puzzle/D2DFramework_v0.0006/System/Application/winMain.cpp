#include "stdafx.h"
#include "../MainEntry/MainEntry.h"

MainEntry* MainClass;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef _DEBUG
	// 종료할 때 덤프메모리를 체크하는 전처리기
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	MainClass 에 테스트용으로 int* pInt 를 동적할당하고 지우지 않았다
	//	이 상태에서 F5 (로컬 디버그) 으로 실행하게되면 '출력' 탭에
	/*
		Detected memory leaks!
		Dumping objects ->
		(.. 현재 프로젝트 파일) : {232} normal block at 0x007D3C58, 4byte long.
		이라는 문자열이 나온다.

		위 문자열을 더블클릭하면 메모리릭이 발생한 코드를 가리킨다.
		허나 위치가 나타나지 않는 경우도 있는데 중괄호 {232} 내부의 번호를 이용해 찾을 수 있다

		밑의 _CrtSetBreakAlloc() 안에 232 라는 번호를 넣고 로컬 디버그를 실행하면
		해당 메모리릭이 발생한 코드에서 디버깅이 중지된다
	*/
	//_CrtSetBreakAlloc();
#endif

	MainClass = new MainEntry;

	if (FAILED(MainClass->CreateDevice(hInstance, nCmdShow))) return FALSE;
	if (FAILED(MainClass->Init())) return FALSE;

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			_TIMER->UpdateTime();
			MainClass->Update();

			_Device->BeginDraw();
			MainClass->Render();
			_TIMER->RenderTime();
			_Device->EndDraw();
		}
	}

	SafeDeleteClass(MainClass);
	_Device->Release();

	_CrtDumpMemoryLeaks();

	return (int)msg.wParam;
}