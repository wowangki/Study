//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== UI COLLIDER ===========================//

//====================== 2019.11.29 ========================//
//====================== 1Â÷ ¼öÁ¤  =========================//

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
	// POINTER INTERFACE
	IPointerUpHandler* upHandler;
	IPointerDownHandler* downHandler;
	IDragHandler* dragHandler;

private:
	D2D_RECT_F rc;			// RECT_TYPE
	D2D1_ELLIPSE cir;		// CIR_TYPE
	UICOL_TYPE type;		// UI_COLLISION TYPE

public:
	UICollider();
	explicit UICollider(UI* ui, UICOL_TYPE type = UI_RECT);
	virtual ~UICollider();

	virtual HRESULT Init(D2D_POINT_2F pos = { 0.0f,0.0f }, D2D_SIZE_F size = { 0.0f,0.0f }, PIVOT pivot = PIVOT_CC, float angle = 0.0f) override { return S_OK; }
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void IsCollision(void) override;

private:
	void SetHandler(UI* ui);
};

