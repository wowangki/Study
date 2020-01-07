#include "stdafx.h"
#include "PhysicsMgr.h"
#include "../GameObject/GameObject.h"
#include "../Component/Graphic/Camera/Camera.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Physics/Collider/Collider.h"
#include "../Component/Figure/Grid/Grid.h"

PhysicsMgr::PhysicsMgr()
{
}

PhysicsMgr::~PhysicsMgr()
{
}

void PhysicsMgr::Release(void)
{

}

void PhysicsMgr::Update(const Camera * cam)
{

}

void PhysicsMgr::Render(void)
{
}

void PhysicsMgr::RegistCollider(Collider * coll)
{
	GameObject* temp = coll->GetMyObject();

	switch (temp->GetLayer())
	{
		case LAYER::PLAYER: case LAYER::ENEMY:default: {
			mDynamic.insert(make_pair(temp, coll));
		}
		break;
		case LAYER::MAPOBJECT: case LAYER::ITEM: {
			mStatic.insert(make_pair(temp, coll));
		}
		break;
		case LAYER::MAP: {
			
		}
		break;
		case LAYER::UI: {
			vUI.push_back(coll);
		}
		break;
	}
}

void PhysicsMgr::UnRegistCollider(Collider * coll)
{
	GameObject* temp = coll->GetMyObject();

	switch (temp->GetLayer())
	{
		case LAYER::PLAYER: case LAYER::ENEMY:default: {
			mDynamic.erase(temp);
		}
		break;
		case LAYER::MAPOBJECT: case LAYER::ITEM: {
			mStatic.erase(temp);
		}
		break;
		case LAYER::MAP: {
			if (vMap.find(temp) == vMap.end()) return;
			mTIter iter = vMap.find(temp);

			for (UINT y = 0; y < iter->second.size(); y++)
			{
				for (UINT x = 0; x < iter->second[y].size(); x++) {
					if (iter->second[y][x] == coll) {
						iter->second[y][x] = nullptr;
					}
				}
			}


		}
		break;
		case LAYER::UI: {
			for (UINT i = 0; i < vUI.size(); i++)
			{
				if (vUI[i] == coll) {
					vUI.erase(vUI.begin() + i);
				}
			}
		}
		break;
	}
}

void PhysicsMgr::UIUpdate(void)
{
}

void PhysicsMgr::TerrainUpdate(void)
{
}
