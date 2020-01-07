#pragma once
#include "../Component/Component.h"

#define MAXZOOM 3.0f
#define MINZOOM 0.5f

class Transform;
class Camera : public Component
{
private:
	DEFINE_COMPONENT(Camera, Component, false);

private:
	GameObject* target;
	Transform* transform;

	float scale;

public:
	explicit Camera(GameObject* object);
	virtual ~Camera();

	// Component을(를) 통해 상속됨
	HRESULT Init(D2D_SIZE_F size = { WINSIZEX, WINSIZEY }, D2D_POINT_2F offset = { 0.0f,0.0f });
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override {}

	void ZoomIn(void);
	void ZoomOut(void);

	D2D_POINT_2F GetRevisionPos(void) const;
	D2D_RECT_F GetCamRect(void) const;
	inline float GetScale(void) const { return scale; }

	GameObject* GetTarget(void) const { return target; }
	void SetTarget(GameObject* target) { this->target = target; }
	void UnRegistTarget(void) { target = nullptr; }
	void SetScale(float scale);

	void TestControll(void);
};

