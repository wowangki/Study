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
	// �Ϲ� ������Ʈ (�÷��̾�, ���ʹ�, ũ��ó ��)
	unordered_map<GameObject*, Collider*> mDynamic;

	// ���� ������Ʈ (�ʿ�����Ʈ, ������)
	unordered_map<GameObject*, Collider*> mStatic;

	typedef unordered_map<GameObject*, Collider*>::iterator mOIter;

	// UI ����
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

