#include "stdafx.h"
#include "GridMap.h"
#include "../GameObject/GameObject.h"
#include "../Component/Transform/Transform.h"

GridMap::GridMap()
{
}

GridMap::GridMap(GameObject * myObject)
	:myObject(myObject)
{
	startIndex = { 0,0 };
	gridSize = { 0,0 };
	maxGrid = { 0,0 };
}

GridMap::GridMap(D2D_SIZE_F gridSize, D2D_POINT_2U maxGrid)
{
	startIndex.x = ((WINSIZEX * 0.5f) / (gridSize.width)) - (maxGrid.x * 0.5f) + 1;
	startIndex.y = ((WINSIZEY * 0.5f) / (gridSize.height)) - (maxGrid.y * 0.5f) + 1;
}


GridMap::~GridMap()
{
}

HRESULT GridMap::Init(void)
{
	for (int y = 0; y < maxGrid.y; y++) 
	{
		vector<GameObject*> vTemp;
		for (int x = 0; x < maxGrid.x; x++)
		{
			vTemp.push_back(nullptr);
		}
		vGrid.push_back(vTemp);
		vTemp.clear();
	}

	return S_OK;
}

void GridMap::Release(void)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid.size(); x++)
		{
			vGrid[y][x]->Release();
		}
	}
}

void GridMap::Update(void)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid.size(); x++)
		{
			vGrid[y][x]->Update();
		}
	}
}

void GridMap::Render(void)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid.size(); x++)
		{
			vGrid[y][x]->Render();
		}
	}
}

void GridMap::SetObject(GameObject * object, D2D_POINT_2U grid)
{
	D2D_POINT_2F pos;
	pos.x = gridSize.width * grid.x;
	pos.y = gridSize.height * grid.y;

	object->GetComponent<Transform>()->SetPos(pos);
	object->GetComponent<Transform>()->SetSize(gridSize);

	vGrid[grid.y][grid.x] = object;
}
