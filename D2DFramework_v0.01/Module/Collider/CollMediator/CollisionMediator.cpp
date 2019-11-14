#include "stdafx.h"
#include "CollisionMediator.h"
#include "../RectCollider/RectCollider.h"

CollisionMediator::CollisionMediator()
{
}


CollisionMediator::~CollisionMediator()
{
}

void CollisionMediator::Update(void)
{
	mIter iter = mCollider.begin();

	for (iter; iter != mCollider.end(); ++iter) {
		iter->second->Update(nullptr);
	}
}

void CollisionMediator::AddCollider(ColliderBase * col)
{
	mIter iter = mCollider.begin();

	for (iter; iter != mCollider.end(); ++iter) {
		if (iter->first == col->GetTransform())
			return;
	}

	mCollider.insert(make_pair(col->GetTransform(), col));
}

void CollisionMediator::RemoveCollider(ColliderBase * col)
{
	if (mCollider.empty()) return;

	mIter iter = mCollider.begin();

	for (iter; iter != mCollider.end(); ++iter) {
		if (iter->first == col->GetTransform()) {
			mCollider.erase(iter);
		}
	}
}
