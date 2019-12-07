#include "stdafx.h"
#include "CollisionManager.h"
#include "../GameObject/GameObject.h"
#include "../Component/Physics/Collider/Collider.h"


CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

HRESULT CollisionManager::Init(void)
{

	return S_OK;
}

void CollisionManager::Release(void)
{
}

void CollisionManager::Update(void)
{
}

void CollisionManager::Render(void)
{
}

void CollisionManager::AddCollider(Collider * col)
{
	Collider* temp = FindCollider(col->GetMyObject());
	if (temp) return;

	mCollider.insert(make_pair(col->GetMyObject()->GetID(), col));
}

void CollisionManager::RemoveCollider(GameObject* object)
{
	Collider* temp = FindCollider(object);
	if (!temp) return;

	mCollider.erase(object->GetID());
}

Collider * CollisionManager::FindCollider(GameObject* object)
{
	if (mCollider.empty()) return nullptr;
	mIter iter = mCollider.begin();

	for (iter; iter != mCollider.end(); ++iter) {
		if (iter->first == object->GetID()) {
			return iter->second;
		}
	}

	return nullptr;
}
