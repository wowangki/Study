#include "stdafx.h"
#include "MainEntry.h"
#include "../GameObject/TestObject/TestObject.h"
#include "../Component/Physics/Collider/RectCollider/RectCollider.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"

MainEntry::MainEntry()
{
}


MainEntry::~MainEntry()
{
	_BRUSH->ReleaseSingleton();
	_FONT->ReleaseSingleton();
	_KEYCODE->ReleaseSingleton();
}

HRESULT MainEntry::Init(void)
{
	t1 = new TestObject({ WINSIZEX * 0.5f, WINSIZEY * 0.5f - 200.0f }, { 50,50 }, PIVOT_CC);
	t2 = new TestObject({ WINSIZEX * 0.5f, WINSIZEY * 0.5f }, { 50,50 }, PIVOT_CC);;

	t1->Init();
	t2->Init();
	((TestObject*)t1)->SetIsControll(true);

	return S_OK;
}

void MainEntry::Release(void)
{
	t1->Release();
	t2->Release();
}

void MainEntry::Update(void)
{
	t1->Update();
	t2->Update();

	t1->GetComponent<RidgidBody>()->IsCollision(t2->GetComponent<RectCollider>());
}

void MainEntry::Render(void)
{
	D2D_SIZE_F temp = GetOverlapSize(t1->GetComponent<Transform>()->GetRect(),
									t2->GetComponent<Transform>()->GetRect());

	WCHAR tString[256];
	static TCHAR tTextString[] = L"WIDTH : %.2f\nHIGHT : %.2f\n";

	_stprintf(tString, tTextString, temp.width, temp.height);
	_FONT->Render(tString, RectF(200.0f, 0.0f, 400.0f, 100.0f));

	t1->Render();
	t2->Render();
}
