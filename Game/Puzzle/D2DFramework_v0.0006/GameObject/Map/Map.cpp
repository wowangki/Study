#include "stdafx.h"
#include "Map.h"
#include "../Map/Tile/Tile.h"
#include "../Component/Transform/Transform.h"

Map::Map()
{
}

Map::Map(D2D_SIZE_F grid, D2D_SIZE_U maxSize)
	:grid(grid), maxSize(maxSize)
{
	startIndex.x = ((WINSIZEX * 0.5f) / (grid.width)) - (maxSize.width * 0.5f) + 1;
	startIndex.y = ((WINSIZEY * 0.5f) / (grid.height)) - (maxSize.height * 0.5f) + 1;
}

Map::~Map()
{
}

HRESULT Map::Init(void)
{
	for (int y = 0; y < maxSize.height; y++)
	{
		vector<Tile*> vTemp;
		for (int x = 0; x < maxSize.width; x++)
		{
			Tile* temp = new Tile({ (startIndex.x + x) * grid.width, (startIndex.y + y) * grid.height}, 
				{ grid.width , grid.height }, PIVOT_CC);

			vTemp.push_back(temp);
		}
		vMap.push_back(vTemp);
		vTemp.clear();
	}
	return S_OK;
}

void Map::Release(void)
{
}

void Map::Update(void)
{
}

void Map::Render(void)
{
	for (UINT y = 0; y < vMap.size(); y++)
	{
		for (UINT x = 0; x < vMap[y].size(); x++)
		{
			vMap[y][x]->Render();
		}
	}
}
