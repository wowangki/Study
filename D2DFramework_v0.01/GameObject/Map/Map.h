#pragma once
#include <vector>

class Tile;
class Map
{
private:
	vector<vector<Tile*>> vMap;

private:
	D2D_POINT_2L startIndex;
	D2D_SIZE_F grid;
	D2D_SIZE_U maxSize;

public:
	Map();
	explicit Map(D2D_SIZE_F grid, D2D_SIZE_U maxSize);
	~Map();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	vector<vector<Tile*>> GetMap(void) { return vMap; }
};

