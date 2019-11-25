#include "stdafx.h"
#include "UMCollMgr.h"
#include "../Component/Transform/Transform.h"
#include "../Component/Collider/Collider.h"
#include "../GameObject/Map/Tile/Tile.h"
#include "../GameObject/Map/Map.h"

UMCollMgr::UMCollMgr()
{
}

UMCollMgr::UMCollMgr(GameObject * myObject)
{
	this->myObject = myObject;
}

UMCollMgr::UMCollMgr(GameObject * myObject, Map * myMap)
{
	this->myObject = myObject;
}


UMCollMgr::~UMCollMgr()
{
}

HRESULT UMCollMgr::Init(void)
{
	return S_OK;
}

void UMCollMgr::Release(void)
{
}

void UMCollMgr::Update(void)
{
	ChkMapCollision();
}

void UMCollMgr::Render(void)
{
	for (UINT y = sOffsetIndex.y; y < eOffsetIndex.y; y++)
	{
		for (UINT x = sOffsetIndex.x; x < eOffsetIndex.x; x++) {
			_RenderTarget->DrawRectangle(vMap[myIndex.y + y][myIndex.x + x]->GetComponent<Transform>()->GetRect(),
				_Device->pDefaultBrush);
		}
	}
}

void UMCollMgr::ChkMapCollision(void)
{
	for (UINT y = sOffsetIndex.y; y < eOffsetIndex.y; y++)
	{
		for (UINT x = sOffsetIndex.x; x < eOffsetIndex.x; x++) {
			myObject->GetComponent<Collider>()->IsCollision(
				vMap[myIndex.y + y][myIndex.x + x]->GetComponent<Collider>());
		}
	}

}
