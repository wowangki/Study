//====================== 2019.11.27 ========================//
//================== MADE BY KIM WANKI =====================//
//======================= Grid =============================//

#pragma once
#include "../Component/Component.h"
#include <vector>

class Transform;
class Grid final : public Component
{
private:
	vector<vector<Transform*>> vGrid;

private:
	Transform* transform;

	D2D_SIZE_F cellSize;
	D2D_POINT_2U maxCell;

private:
	DEFINE_COMPONENT(Grid, Component, false);

public:
	explicit Grid(GameObject* object);
	~Grid();

	// Component을(를) 통해 상속됨
	virtual HRESULT Init(D2D_SIZE_F cellSize, D2D_POINT_2U maxCell, PIVOT pivot = PIVOT_CC);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	inline D2D_SIZE_F GetCellSize(void) const { return cellSize; }
	inline D2D_POINT_2U GetMaxCell(void) const { return maxCell; }

	D2D_POINT_2F SetGridPosition(D2D_POINT_2U index);
	void ChangeCellSize(D2D_SIZE_F cellSize);
	
	// UI 용
	void IncreseMaxCell(void);
	void DecreaseMaxCell(void);

	void AttachObject(GameObject* object, D2D_POINT_2U index);
	void DetachObject(GameObject* object);
};