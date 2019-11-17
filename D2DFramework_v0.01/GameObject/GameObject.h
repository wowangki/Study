#pragma once

enum class OBJECT_MODE { DEFAULT, INGAME, TOOLSET };
enum class LAYER { DEFAULT, PLAYER, ENEMY, UI, MAPOBJECT };

class Transform;
class Collider;
class GameObject
{
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
	GameObject();
	~GameObject();
	
	inline virtual GameObject* Clone(void) = 0;
	inline Transform* GetTransform(void) { return transform; }
	inline Collider* GetCollider(void) { return collider; }
};

