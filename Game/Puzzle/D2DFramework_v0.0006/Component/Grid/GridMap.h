#pragma once
#include <vector>
#include "../Component.h"

class GameObject;
class GridMap : public Component
{
private:
	vector<vector<GameObject*>> vGrid;

private:
	GameObject* myObject;
	D2D_POINT_2U startIndex;
	D2D_SIZE_F gridSize;
	D2D_POINT_2U maxGrid;


public:
	GridMap();
	explicit GridMap(GameObject* myObject);
	explicit GridMap(D2D_SIZE_F gridSize, D2D_POINT_2U maxGrid);
	~GridMap();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	vector<vector<GameObject*>> GetVGrid(void) { return vGrid; }
	void SetObject(GameObject* object, D2D_POINT_2U grid);

	//Chainning Set
	GridMap* SetGridSize(D2D_SIZE_F size) { 
		this->gridSize = size; return this; 
	}

	GridMap* SetMaxGrid(D2D_POINT_2U grid) { 
		this->maxGrid = grid; return this; 
	}

	GridMap* SetStartIndex(D2D_POINT_2F pos = { WINSIZEX * 0.5f, WINSIZEY * 0.5f }) {
		startIndex.x = ((pos.x) / (gridSize.width)) - (maxGrid.x * 0.5f) + 1;
		startIndex.y = ((pos.y) / (gridSize.height)) - (maxGrid.y * 0.5f) + 1;
		return this;
	}


};

