#include "stdafx.h"
#include "Grid.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"

Grid::Grid()
{
}

Grid::Grid(GameObject * object)
{
	this->object = object;
}


Grid::~Grid()
{
}

// 2019.11.27 ==================================================================//
// 그리드 생성 =================================================================//
// ============================================================================//
HRESULT Grid::Init(D2D_POINT_2F pos, D2D_SIZE_F gridSize, D2D_POINT_2U length, PIVOT pivot)
{
	this->gridSize = gridSize;
	this->length = length;

	for (UINT y = 0; y < length.y; y++)
	{
		vector<Transform*> vTemp;
		D2D_POINT_2F tPos;
		for (UINT x = 0; x < length.x; x++)
		{
			Transform* temp = new Transform(object);
			switch (pivot)
			{
			case nFigure::PIVOT_LT:
				tPos = { pos.x + (x * gridSize.width), 
						 pos.y + (y * gridSize.height) };
				break;
			case nFigure::PIVOT_LC:
				tPos = { pos.x + (x * gridSize.width), 
						 pos.y + ((y - length.y * 0.5f) * gridSize.height) };
				break;
			case nFigure::PIVOT_LB:
				tPos = { pos.x + (x * gridSize.width),
						 pos.y + ((y - length.y) * gridSize.height) };
				break;
			case nFigure::PIVOT_CT:
				tPos = { pos.x + ((x - length.x * 0.5f) * gridSize.width),
						 pos.y + (y * gridSize.height) };
				break;
			case nFigure::PIVOT_CC:default:
				tPos = { pos.x + ((x - length.x * 0.5f) * gridSize.width), 
						 pos.y + (((y - length.y * 0.5f) - length.y * 0.5f) * gridSize.height) };
				break;
			case nFigure::PIVOT_CB:
				tPos = { pos.x + ((x - length.x * 0.5f) * gridSize.width),
						 pos.y + ((y - length.y) * gridSize.height) };
				break;
			case nFigure::PIVOT_RT:
				tPos = { pos.x + ((x - length.x) * gridSize.width), 
						 pos.y + (y * gridSize.height) };
				break;
			case nFigure::PIVOT_RC:
				tPos = { pos.x + ((x - length.x) * gridSize.width),
						 pos.y + ((y - length.y * 0.5f) * gridSize.height) };
				break;
			case nFigure::PIVOT_RB:
				tPos = { pos.x + ((x - length.x) * gridSize.width),
						 pos.y + ((y - length.y) * gridSize.height) };
				break;
			}

			temp->Init(
				tPos, 
				gridSize, 
				pivot, 
				0.0f, 
				object->GetComponent<Transform>());

			vTemp.push_back(temp);
		}
		vGrid.push_back(vTemp);
		vTemp.clear();
	}

	return S_OK;
}

// 2019.11.27 ==================================================================//
// 메모리 해제 ==================================================================//
// ============================================================================//
void Grid::Release(void)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid[y].size(); x++)
		{
			SafeRelease(vGrid[y][x]);
		}
	}

	vGrid.clear();
	vector<vector<Transform*>> vTemp;
	vTemp.swap(vGrid);
}

// 2019.11.27 ==================================================================//
// 업데이트 ====================================================================//
// ============================================================================//
void Grid::Update(void)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid[y].size(); x++)
		{
			vGrid[y][x]->Update();
		}
	}
}

// 2019.11.27 ==================================================================//
// 렌더링 (에디트 용) ===========================================================//
// ============================================================================//
void Grid::Render(void)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid[y].size(); x++)
		{
			vGrid[y][x]->Render();
		}
	}
}

// 2019.11.27 ==================================================================//
// 그리드 종속 =================================================================//
// ============================================================================//
void Grid::SetGridTransform(GameObject * object, D2D_POINT_2U index)
{
	vGrid[index.y][index.x]->AddChild(object->GetComponent<Transform>());
	object->GetComponent<Transform>()->SetLocalPos({ 0,0 });
}