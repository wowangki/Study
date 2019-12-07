//====================== 2019.12.03 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Collision Manager =====================//

#pragma once
#include <map>
#include <list>

class GameObject;
class Collider;
class CollisionManager
{
private:
	map<int, Collider*> mCollider;
	typedef map<int, Collider*>::iterator mIter;

public:
	CollisionManager();
	~CollisionManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	void AddCollider(Collider* col);
	void RemoveCollider(GameObject* object);
	Collider* FindCollider(GameObject* object);
	
};
