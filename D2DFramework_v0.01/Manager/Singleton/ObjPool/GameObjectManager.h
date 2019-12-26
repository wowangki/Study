#pragma once
#include "../SingletonBase.h"
#include <vector>

class GameObject;
class GameObjectManager : public SingletonBase<GameObjectManager>
{	
private:
	vector<GameObject*> vObjList;

public:
	GameObjectManager();
	~GameObjectManager();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	inline vector<GameObject*> GetVObjeList(void) const { return vObjList; }

	inline void RegistObjList(GameObject* object) { vObjList.push_back(object); }
	inline void UnRegistObjList(GameObject* object) { 

		for (UINT i = 0; i < vObjList.size(); i++)
		{
			if (vObjList[i] == object) {
				vObjList.erase(vObjList.begin() + i);
				return;
			}
		}
	}
};

