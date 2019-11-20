//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== UI COLLIDER ===========================//

#pragma once
#include "../Collider.h"

class IPointerUpHandler;
class IPointerDownHandler;
class IDragHandler;
class UI;
class UICollider : public Collider
{
private:
	// UICOLLISION TYPE
	enum UICOL_TYPE {
		UI_RECT,
		UI_CIR
	};

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
	explicit UICollider(UI* myUI, UICOL_TYPE type = UI_RECT);
	~UICollider();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	virtual void IsCollision(Collider * col) override {};
	virtual void IsCollision(void) override;

	void SetHandler(UI* myUI);
};

