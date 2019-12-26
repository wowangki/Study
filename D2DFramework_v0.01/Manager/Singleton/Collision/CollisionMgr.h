#pragma once
#include "../SingletonBase.h"
#include <list>

class Collider;
class CollisionMgr : public SingletonBase<CollisionMgr>
{
private:
	list<Collider*> lCollList;
	typedef list<Collider*>::iterator lCollIter;

public:
	CollisionMgr();
	~CollisionMgr();

	void Release(void);
	void Update(void);

	void CollisionUpdate(void);


	void RegistCollider(Collider* coll);
	void UnRegistCollider(Collider* coll);

	
};

