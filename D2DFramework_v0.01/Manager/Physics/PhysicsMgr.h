#pragma once
#include <vector>
#include <unordered_map>

class GameObject;
class Collider;
class PhysicsMgr
{
private:
	friend class WorldMgr;

private:
	// 일반 오브젝트 (플레이어, 에너미, 크리처 등)
	unordered_map<GameObject*, Collider*> mDynamic;

	// 정적 오브젝트 (맵오브젝트, 아이템)
	unordered_map<GameObject*, Collider*> mStatic;

	typedef unordered_map<GameObject*, Collider*>::iterator mOIter;

	// UI 저장
	vector<Collider*> vUI;

	// TileMap (Grid)
	map<GameObject*, vector<vector<Collider*>>> vMap;
	typedef map <GameObject*, vector<vector<Collider*>>>::iterator mTIter;

private:
	void RegistCollider(Collider* coll);
	void UnRegistCollider(Collider* coll);

public:
	PhysicsMgr();
	~PhysicsMgr();

	void Release(void);
	void Update(const class Camera* cam);
	void Render(void);

	void UIUpdate(void);
	void TerrainUpdate(void);
};

