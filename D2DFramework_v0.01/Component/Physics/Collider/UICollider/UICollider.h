//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== UI COLLIDER ===========================//

//====================== 2019.11.29 ========================//
//====================== 1�� ����  =========================//

#pragma once
#include "../Collider.h"


// UICOLLISION TYPE
enum UICOL_TYPE {
	UI_RECT,
	UI_CIR
};

class IPointerUpHandler;
class IPointerDownHandler;
class IDragHandler;
class UI;
class UICollider final : public Collider
{
private:
	DEFINE_COMPONENT(UICollider, Collider, false);

private:
	// POINTER INTERFACE
	IPointerUpHandler* upHandler;
	IPointerDownHandler* downHandler;
	IDragHandler* dragHandler;

private:
	UICOL_TYPE type;		// UI_COLLISION TYPE

private:

public:
	explicit UICollider(UI* ui, UICOL_TYPE type = UI_RECT);
	virtual ~UICollider();

	//virtual HRESULT Init(void) override;
	//virtual HRESULT Init(D2D_POINT_2F pos, D2D_SIZE_F size, float angle = 0.0f) override;
	virtual void Release(void) override;
	virtual void Update(void) override;

	virtual void IsCollision(void) override;

private:
	void SetHandler(UI* ui);
	//virtual void IsCollision(Collider * other) override;
};