//====================== 2019.11.24 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Navigator =============================//

#pragma once
#include "../Component.h"
#include <vector>
#define OFFSETX 2
#define OFFSETY 2

class GameObject;
class Tile;
class Navigator : public Component
{
private:
	GameObject* myObject;

	vector<vector<Tile*>> vMap;
	D2D_POINT_2L start;
	D2D_POINT_2L end;
	D2D_POINT_2L current;

private:
	GameObject* target;

public:
	Navigator();
	explicit Navigator(GameObject* myObject);
	virtual ~Navigator();

	// Component을(를) 통해 상속됨
	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void SetCurrentMap(vector<vector<Tile*>> vMap) { this->vMap = vMap; }
	void FindCurrentIndex(void);


};

