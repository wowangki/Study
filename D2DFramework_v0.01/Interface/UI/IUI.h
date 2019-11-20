//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== UI INTERFACE ==========================//

#pragma once

class Collider;
class IPointerUpHandler {
public:
	virtual void OnPointUp(Collider* col) = 0;
};

class IPointerDownHandler {
public:
	virtual void OnPointDown(Collider* col) = 0;
};

class IDragHandler {
public:
	virtual void OnDragPointer(Collider* col) = 0;
};