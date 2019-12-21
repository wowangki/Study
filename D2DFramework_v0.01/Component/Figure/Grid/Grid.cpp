#include "stdafx.h"
#include "Grid.h"
#include "../GameObject/GameObject.h"
#include "../Component/Figure/Transform/Transform.h"

DECLARE_COMPONENT(Grid);

Grid::Grid(GameObject * object)
	:cellSize({1,1}), maxCell({1,1})
{
	this->object = object;
	this->transform = object->GetComponent<Transform>();
}


Grid::~Grid()
{
}

// 2019.11.27 ==================================================================//
// 그리드 생성 =================================================================//
// ============================================================================//
HRESULT Grid::Init(D2D_SIZE_F cellSize, D2D_POINT_2U maxCell, PIVOT pivot)
{
	D2D_POINT_2F pos = transform->GetWorldPos();

	this->cellSize = cellSize;
	this->maxCell = maxCell;

	for (UINT y = 0; y < maxCell.y; y++)
	{
		vector<Transform*> vTemp;
		D2D_POINT_2F tPos;
		for (UINT x = 0; x < maxCell.x; x++)
		{
			Transform* temp = new Transform(object);
			switch (pivot)
			{
			case nFigure::PIVOT_LT:
				tPos = { pos.x + (x * cellSize.width),
						 pos.y + (y * cellSize.height) };
				break;
			case nFigure::PIVOT_LC:
				tPos = { pos.x + (x * cellSize.width),
						 pos.y + ((y - maxCell.y * 0.5f) * cellSize.height) };
				break;
			case nFigure::PIVOT_LB:
				tPos = { pos.x + (x * cellSize.width),
						 pos.y + ((y - maxCell.y) * cellSize.height) };
				break;
			case nFigure::PIVOT_CT:
				tPos = { pos.x + ((x - maxCell.x * 0.5f) * cellSize.width),
						 pos.y + (y * cellSize.height) };
				break;
			case nFigure::PIVOT_CC:default:
				tPos = { pos.x + ((x - maxCell.x * 0.5f) * cellSize.width),
						 pos.y + (((y - maxCell.y * 0.5f) - maxCell.y * 0.5f) * cellSize.height) };
				break;
			case nFigure::PIVOT_CB:
				tPos = { pos.x + ((x - maxCell.x * 0.5f) * cellSize.width),
						 pos.y + ((y - maxCell.y) * cellSize.height) };
				break;
			case nFigure::PIVOT_RT:
				tPos = { pos.x + ((x - maxCell.x) * cellSize.width),
						 pos.y + (y * cellSize.height) };
				break;
			case nFigure::PIVOT_RC:
				tPos = { pos.x + ((x - maxCell.x) * cellSize.width),
						 pos.y + ((y - maxCell.y * 0.5f) * cellSize.height) };
				break;
			case nFigure::PIVOT_RB:
				tPos = { pos.x + ((x - maxCell.x) * cellSize.width),
						 pos.y + ((y - maxCell.y) * cellSize.height) };
				break;
			}

			temp->Init(
				tPos, 
				cellSize,
				pivot, 
				0.0f, 
				transform);

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