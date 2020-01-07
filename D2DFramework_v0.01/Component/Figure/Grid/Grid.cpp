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
	this->cellSize = cellSize;
	this->maxCell = maxCell;

	for (UINT y = 0; y < maxCell.y; y++)
	{
		vector<Transform*> vTemp;
		for (UINT x = 0; x < maxCell.x; x++)
		{
			Transform* temp = new Transform(object);
			
			temp->Init(
				SetGridPosition({ x,y }),
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

D2D_POINT_2F Grid::SetGridPosition(D2D_POINT_2U index)
{
	D2D_POINT_2F temp;
	D2D_POINT_2F pos = transform->GetWorldPos();

	switch (transform->GetPivot())
	{
	case nFigure::PIVOT_LT:
		temp = { pos.x + (index.x * cellSize.width),
				 pos.y + (index.y * cellSize.height) };
		break;
	case nFigure::PIVOT_LC:
		temp = { pos.x + (index.x * cellSize.width),
				 pos.y + ((index.y - maxCell.y * 0.5f) * cellSize.height) };
		break;
	case nFigure::PIVOT_LB:
		temp = { pos.x + (index.x * cellSize.width),
				 pos.y + ((index.y - maxCell.y) * cellSize.height) };
		break;
	case nFigure::PIVOT_CT:
		temp = { pos.x + ((index.x - maxCell.x * 0.5f) * cellSize.width),
				 pos.y + (index.y * cellSize.height) };
		break;
	case nFigure::PIVOT_CC:default:
		temp = { pos.x + ((index.x - maxCell.x * 0.5f) * cellSize.width),
				 pos.y + (((index.y - maxCell.y * 0.5f) - maxCell.y * 0.5f) * cellSize.height) };
		break;
	case nFigure::PIVOT_CB:
		temp = { pos.x + ((index.x - maxCell.x * 0.5f) * cellSize.width),
				 pos.y + ((index.y - maxCell.y) * cellSize.height) };
		break;
	case nFigure::PIVOT_RT:
		temp = { pos.x + ((index.x - maxCell.x) * cellSize.width),
				 pos.y + (index.y * cellSize.height) };
		break;
	case nFigure::PIVOT_RC:
		temp = { pos.x + ((index.x - maxCell.x) * cellSize.width),
				 pos.y + ((index.y - maxCell.y * 0.5f) * cellSize.height) };
		break;
	case nFigure::PIVOT_RB:
		temp = { pos.x + ((index.x - maxCell.x) * cellSize.width),
				 pos.y + ((index.y - maxCell.y) * cellSize.height) };
		break;
	}

	return temp;
}

void Grid::ChangeCellSize(D2D_SIZE_F cellSize)
{
	this->cellSize = cellSize;

	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid[y].size(); x++)
		{	
			vGrid[y][x]->SetWorldPos(SetGridPosition({ y,x }));
			vGrid[y][x]->SetSize(this->cellSize);
		}
	}

	Update();
}

void Grid::IncreseMaxCell(void)
{
	maxCell.x++;
	maxCell.y++;

	for (UINT y = 0; y < maxCell.y; y++)
	{
		if (y != maxCell.y - 1) {
			Transform* temp = new Transform(object);
			temp->Init(SetGridPosition({maxCell.x -1, y}), cellSize,
				transform->GetPivot(), 0.0f, transform);

			vGrid[y].push_back(temp);
		}
		else {

			vector<Transform*> vTemp;
			for (UINT x = 0; x < maxCell.x; x++)
			{
				Transform* temp = new Transform(object);
				temp->Init(SetGridPosition({ x, y }), cellSize,
					transform->GetPivot(), 0.0f, transform);
				vTemp.push_back(temp);
			}
			vGrid.push_back(vTemp);
			vTemp.clear();
		}
	}
}

void Grid::DecreaseMaxCell(void)
{
	if (vGrid.empty()) return;

	maxCell.x--;
	maxCell.y--;

	for (UINT y = 0; y < vGrid.size(); y++)
	{
		vGrid[y].pop_back();
	}
	vGrid.pop_back();
}

void Grid::AttachObject(GameObject * object, D2D_POINT_2U index)
{
	vGrid[index.y][index.x]->AddChild(object->GetComponent<Transform>());
	vGrid[index.y][index.x]->SetLocalPos({ 0,0 });
}

void Grid::DetachObject(GameObject * object)
{
	for (UINT y = 0; y < vGrid.size(); y++)
	{
		for (UINT x = 0; x < vGrid[y].size(); x++)
		{
			vGrid[y][x]->RemoveChild(object->GetComponent<Transform>());
		}
	}
}
