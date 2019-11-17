#pragma once
#include <map>
#include <queue>

class Collider;
class GameObject;
class ColliderManager
{
private:
	friend Collider;

private:
	map<Collider*, GameObject*> mColl;
	typedef map<Collider*, GameObject*>::iterator mIter;
	
public:
	ColliderManager();
	~ColliderManager();

	void Init(void);
	void Release(void);
	void Update(void);
	void Render(void);
};

