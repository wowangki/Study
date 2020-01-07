#pragma once
#include <vector>

enum class WORLD_MODE { DEFAULT, INGAME, TOOLSET };

class GameObject;
class Collider;
class Image;
class Sprite;
class Animator;
class Camera;
class WorldMgr
{
private:
	typedef vector<GameObject*> ObjList;
	typedef ObjList::iterator vIter;
	ObjList objList;

private:
	class PhysicsMgr* physics;
	class GraphicMgr* graphic;

public:
	WorldMgr();
	~WorldMgr();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	GameObject* FindObject(string name) const;
	GameObject* FindObjectWithTag(string tag) const;
	vector<GameObject*> FindObjects(string name) const;
	vector<GameObject*> FindObjectsWithTag(string tag) const;

	inline vector<GameObject*> GetOtherObj(void) const { return objList; }

	void RegistObjList(GameObject* obj);
	void UnRegistObjList(GameObject* obj);
	void RegistPhysics(Collider* coll);
	void UnRegistPhysics(Collider* coll);
	void RegistImage(Image* image);
	void UnRegistImage(Image* image);
	void RegistSprite(Sprite* sprite);
	void UnRegistSprite(Sprite* sprite);
	void RegistAnimator(Animator* anim);
	void UnRegistAnimator(Animator* anim);
	void RegistCamera(Camera* cam);
	void UnRegistCamera(Camera* cam);
	const Camera* GetCurrentCam(void) const;
	void SetCurrentCam(GameObject* object);

};

