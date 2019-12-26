#include "stdafx.h"
#include "CollisionMgr.h"
#include "../Component/Physics/Collider/Collider.h"
#include "../Component/Physics/RidgidBody/RidgidBody.h"
#include "../GameObject/GameObject.h"

CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}

void CollisionMgr::Release(void)
{
	lCollList.clear();

	list<Collider*> lTemp;

	lTemp.swap(lCollList);
}

void CollisionMgr::Update(void)
{
	CollisionUpdate();
}

void CollisionMgr::CollisionUpdate(void)
{
	lCollIter sourIter = lCollList.begin();
	lCollIter sourIterEnd = --lCollList.end();
	
	lCollIter destIter = ++lCollList.begin();
	lCollIter destIterEnd = lCollList.end();

	for (sourIter; sourIter != sourIterEnd; ++sourIter)
	{
		for (destIter; destIter != destIterEnd; ++destIter) {
			(*sourIter)->IsCollision((*destIter));
		}
	}


}

void CollisionMgr::RegistCollider(Collider * coll)
{
	lCollList.push_back(coll);
}

void CollisionMgr::UnRegistCollider(Collider * coll)
{
	if (lCollList.empty()) return;

	lCollList.remove(coll);
}
