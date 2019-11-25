//====================== 2019.11.24 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Tile =================================//

#pragma once
#include "../GameObject/GameObject.h"

enum TILE_TYPE {
	DEFAULT,
	TILE_WATER,
	TILE_OBSTACLE
};

class Tile : public GameObject
{
private:
	TILE_TYPE type;

public:
	Tile();
	explicit Tile(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_LT, float angle = 0.0f);
	~Tile();

	virtual void Init(void) override {}
	virtual void Release(void) override {}
	virtual void Update(void) override {}
	virtual void Render(void) override;
};

