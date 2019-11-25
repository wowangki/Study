#pragma once
#include "../GameObject/GameObject.h"

class PuzzleMap : public GameObject
{
private:
	string pieceImgKey[4];

public:
	PuzzleMap();
	explicit PuzzleMap(D2D_POINT_2F startPos, D2D_SIZE_F gridSize, D2D_POINT_2U maxGrid);
	~PuzzleMap();

	// GameObject을(를) 통해 상속됨
	virtual void Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
};

