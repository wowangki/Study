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
	D2D_SIZE_F gridSize;
	D2D_POINT_2U length;

public:
	Grid();
	explicit Grid(GameObject* object);
	~Grid();

	// Component을(를) 통해 상속됨
	virtual HRESULT Init(D2D_POINT_2F pos, D2D_SIZE_F gridSize, D2D_POINT_2U length, PIVOT pivot = PIVOT_CC);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetGridTransform(GameObject* object, D2D_POINT_2U index);
};

