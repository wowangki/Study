#include "stdafx.h"
#include "WorldMgr.h"
#include "../Manager/Physics/PhysicsMgr.h"
#include "../Manager/Graphic/GraphicMgr.h"
#include "../GameObject/GameObject.h"


WorldMgr::WorldMgr()
{
	physics = new PhysicsMgr;
	graphic = new GraphicMgr;
}

WorldMgr::~WorldMgr()
{
}

HRESULT WorldMgr::Init(void)
{
	for (UINT i = 0; i < objList.size(); i++)
	{
		objList[i]->Init();
	}

	return S_OK;
}

void WorldMgr::Release(void)
{
	for (UINT i = 0; i < objList.size(); i++)
	{
		SafeRelease(objList[i]);
	}

	objList.clear();

	ObjList temp;
	temp.swap(objList);

	SafeRelease(physics);
	SafeRelease(graphic);
}

void WorldMgr::Update(void)
{

	for (UINT i = 0; i < objList.size(); i++)
	{
		objList[i]->Update();
	}
}

void WorldMgr::Render(void)
{
	graphic->Render();
}

GameObject * WorldMgr::FindObject(string name) const
{
	for (UINT i = 0; i < objList.size(); i++)
	{
		if (objList[i]->GetName() == name) {
			return objList[i];
		}
	}

	return nullptr;
}

GameObject * WorldMgr::FindObjectWithTag(string tag) const
{
	for (UINT i = 0; i < objList.size(); i++)
	{
		if (objList[i]->GetTag() == tag) {
			return objList[i];
		}
	}

	return nullptr;
}

vector<GameObject*> WorldMgr::FindObjects(string name) const
{
	ObjList vTemp;

	for (UINT i = 0; i < objList.size(); i++)
	{
		if (objList[i]->GetName() == name) {
			vTemp.push_back(objList[i]);
		}
	}

	return vTemp;
}

vector<GameObject*> WorldMgr::FindObjectsWithTag(string tag) const
{
	ObjList vTemp;

	for (UINT i = 0; i < objList.size(); i++)
	{
		if (objList[i]->GetTag() == tag) {
			vTemp.push_back(objList[i]);
		}
	}

	return vTemp;
}

void WorldMgr::RegistObjList(GameObject * obj)
{
	for (UINT i = 0; i < objList.size(); i++)
	{
		if (objList[i] == obj) return;
	}

	objList.push_back(obj);
}

void WorldMgr::UnRegistObjList(GameObject * obj)
{
	vIter iter = objList.begin();

	for (iter; iter != objList.end(); ++iter) {
		if ((*iter) == obj) {
			objList.erase(iter);
			return;
		}
	}
}

void WorldMgr::RegistPhysics(Collider * coll)
{
	if (physics) physics->RegistCollider(coll);
}

void WorldMgr::UnRegistPhysics(Collider * coll)
{
	if (physics) physics->UnRegistCollider(coll);
}

void WorldMgr::RegistImage(Image * image)
{
	if (graphic) graphic->RegistImage(image);
}

void WorldMgr::UnRegistImage(Image * image)
{
	if (graphic) graphic->UnRegistImage(image);
}

void WorldMgr::RegistSprite(Sprite * sprite)
{
	if (graphic) graphic->RegistSprite(sprite);
}

void WorldMgr::UnRegistSprite(Sprite * sprite)
{
	if (graphic) graphic->UnRegistSprite(sprite);
}

void WorldMgr::RegistAnimator(Animator * anim)
{
	if (graphic) graphic->RegistAnimator(anim);
}

void WorldMgr::UnRegistAnimator(Animator * anim)
{
	if (graphic) graphic->UnRegistAnimator(anim);
}

void WorldMgr::RegistCamera(Camera * cam)
{
	if (graphic) graphic->RegistCam(cam);
}

void WorldMgr::UnRegistCamera(Camera * cam)
{
	if (graphic) graphic->UnRegistCam(cam);
}

const Camera * WorldMgr::GetCurrentCam(void) const
{
	if (graphic) return graphic->GetCurrentCam();
}

void WorldMgr::SetCurrentCam(GameObject * object)
{
	if (graphic) graphic->SetCurrentCam(object);
}
