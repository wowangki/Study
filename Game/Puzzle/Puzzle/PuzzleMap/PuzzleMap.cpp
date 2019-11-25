#include "stdafx.h"
#include "PuzzleMap.h"
#include "../Component/Transform/Transform.h"
#include "../Component/Grid/GridMap.h"
#include "../Piece/Piece.h"

PuzzleMap::PuzzleMap()
{
}

PuzzleMap::PuzzleMap(D2D_POINT_2F startPos, D2D_SIZE_F gridSize, D2D_POINT_2U maxGrid)
{
	AddComponent<Transform>()->SetPosChain(startPos);
	AddComponent<GridMap>()->SetGridSize(gridSize)->SetMaxGrid(maxGrid)->SetStartIndex(startPos);
	pieceImgKey[0] = "..";
	pieceImgKey[1] = "..";
	pieceImgKey[2] = "..";
	pieceImgKey[3] = "..";
}


PuzzleMap::~PuzzleMap()
{
}

void PuzzleMap::Init(void)
{
	for (UINT i = 0; i < vComponent.size(); i++)
	{
		vComponent[i]->Init();
	}

	for (UINT y = 0; y < GetComponent<GridMap>()->GetVGrid().size(); y++)
	{
		for (UINT x = 0; x < GetComponent<GridMap>()->GetVGrid()[y].size(); x++)
		{
			GameObject* temp = new Piece(pieceImgKey[RandomInt(0, 3)], { 0,0 }, { 0,0 });
			GetComponent<GridMap>()->SetObject(temp, { x,y });
		}
	}
}

void PuzzleMap::Release(void)
{
	for (UINT i = 0; i < vComponent.size(); i++)
	{
		SafeRelease(vComponent[i]);
	}

	vComponent.clear();

	vector<Component*> temp;
	temp.swap(vComponent);
}

void PuzzleMap::Update(void)
{
	for (UINT i = 0; i < vComponent.size(); i++)
	{
		vComponent[i]->Update();
	}
}

void PuzzleMap::Render(void)
{
	for (UINT i = 0; i < vComponent.size(); i++)
	{
		vComponent[i]->Render();
	}
}
