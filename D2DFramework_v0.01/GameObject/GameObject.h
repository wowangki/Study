//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== GAME OBJECT ===========================//

#pragma once
#include <vector>

enum class OBJECT_MODE { DEFAULT, INGAME, TOOLSET };
enum class LAYER { DEFAULT, PLAYER, ENEMY, UI, MAPOBJECT };

class Component;
class Transform;
class Collider;
class GameObject
{
protected:
	vector<Component*> vComponent;

protected:
	//Unique
	string name;		// OBJECT NAME
	string tag;			// OBJECT TAG
	LAYER layer;		// LAYER
	OBJECT_MODE mode;	// OBJECT PROCESS MODE
	bool isActive;		// ACTIVATION STATE

	// Transform
	//D2D_POINT_2F pos;	// POSITION
	//D2D_SIZE_F size;	// SIZE
	//float angle;		// ANGLE of Radian
	Transform* transform;

	// FIGURE (RECT & Collision)
	//D2D_RECT_F rc;	// RECT of FIND COLLISION
	//PIVOT pivot;		// PIVOT
	Collider* collider;

	// Image
	string imgKey;		// IMGKEY
	ImageModule* img;	// IMG
	D2D_POINT_2L frame;	// FRAME
	float frameTime;	// FRAMETIME
	float elapsedTime;	// ELAPSEDTIME
	bool isCull;

	// Sound
	SoundModule* sound; // SOUND

public:

	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

	inline virtual GameObject* Clone(void) = 0;
	//inline Transform* GetTransform(void) { return transform; }
	//inline Collider* GetCollider(void) { return collider; }
	
	template<typename T>
	T* AddComponent(void) { 
		if (FAILED(vComponent.emplace_back(new T(this)))) {
			TCHAR errorStr[256];
			_stprintf_s(errorStr, L"초기화에 실패 했습니다. \nClassName: %s", typeid(*this).name());
			MessageBox(AppDesc._hWnd, errorStr, NULL, MB_OK);
			return E_FAIL;
		}

		return vComponent[vComponent.size() - 1];
	}
};

