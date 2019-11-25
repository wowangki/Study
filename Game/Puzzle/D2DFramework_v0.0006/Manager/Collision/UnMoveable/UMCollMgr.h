//====================== 2019.11.25 ========================//
//================== MADE BY KIM WANKI =====================//
//=============== UnMoveable Collision Mgr =================//

#pragma once
#include "../Component/Component.h"
#include <vector>

class GameObject;
class Tile;
class MapObject;
class Map;
class UMCollMgr final : public Component
{
private:
	GameObject* myObject;

private:
	vector<vector<Tile*>> vMap;
	//vector<MapObject*> vMObject;

private:
	D2D_POINT_2L myIndex;
	D2D_POINT_2L sOffsetIndex;
	D2D_POINT_2L eOffsetIndex;

public:
	UMCollMgr();
	explicit UMCollMgr(GameObject* myObject);
	explicit UMCollMgr(GameObject* myObject, Map* myMap);
	~UMCollMgr();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void ChkMapCollision(void);
	//void ChkMObjectCollision(void);
};

