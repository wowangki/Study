#pragma once
#include "../Utill/ICollision.h"
enum OBJECT_MODE{
	DEFAULT,
	INGAME,
	MAP_PLACEMENT
};

class Transform;
class GameObject : public ICollision
{
#pragma region Transform
	// Transform Class
	//protected:
	//	D2D_POINT_2F pos;
	//	D2D_SIZE_F size;
	//	float angle;

protected:
	Transform* transform;
#pragma endregion

#pragma region Collider
// Collider or Collision Class
//protected:
//	D2D_RECT_F rc;
//	PIVOT pivot;
//	bool onTrigger;

protected:
	ColliderBase* collider;
#pragma endregion

#pragma region ETC
//// ImageModule Class
//protected:
//	string imgKey;
//	ImageModule* img;
//	float opacity;
//	bool isCull;
//
//// Animation Class
//protected:
//	D2D_POINT_2U frame;
//	float frameRate;
//	float elapsedTime;
//
//// Unique parameter
//protected:
//	string name;
//	bool isActive;
//	OBJECT_MODE mode;
#pragma endregion

public:
	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

	virtual void SelectObject(void) = 0;
	virtual void SetObject(void) = 0;
};

