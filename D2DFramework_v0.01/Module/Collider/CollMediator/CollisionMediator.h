#pragma once
#include <map>

class ColliderBase;
class Transform;
class CollisionMediator
{
private:
	map<Transform*, ColliderBase*> mCollider;
	typedef map<Transform*, ColliderBase*>::iterator mIter;

public:
	CollisionMediator();
	~CollisionMediator();

	void Update(void);

	void AddCollider(ColliderBase* col);
	void RemoveCollider(ColliderBase * col);
};

