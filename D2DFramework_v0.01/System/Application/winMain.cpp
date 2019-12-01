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
	// ������ �� �����޸𸮸� üũ�ϴ� ��ó����
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//	MainClass �� �׽�Ʈ������ int* pInt �� �����Ҵ��ϰ� ������ �ʾҴ�
	//	�� ���¿��� F5 (���� �����) ���� �����ϰԵǸ� '���' �ǿ�
	/*
		Detected memory leaks!
		Dumping objects ->
		(.. ���� ������Ʈ ����) : {232} normal block at 0x007D3C58, 4byte long.
		�̶�� ���ڿ��� ���´�.

		�� ���ڿ��� ����Ŭ���ϸ� �޸𸮸��� �߻��� �ڵ带 ����Ų��.
		�㳪 ��ġ�� ��Ÿ���� �ʴ� ��쵵 �ִµ� �߰�ȣ {232} ������ ��ȣ�� �̿��� ã�� �� �ִ�

		���� _CrtSetBreakAlloc() �ȿ� 232 ��� ��ȣ�� �ְ� ���� ����׸� �����ϸ�
		�ش� �޸𸮸��� �߻��� �ڵ忡�� ������� �����ȴ�
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