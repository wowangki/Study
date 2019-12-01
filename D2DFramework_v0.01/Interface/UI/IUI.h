//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== UI INTERFACE ==========================//

//====================== 2019.11.29 ========================//
//================== UI INTERFACE Modify ===================//

#pragma once

class IPointerUpHandler {
public:
	virtual void OnPointUp(void) = 0;
};

class IPointerDownHandler {
public:
	virtual void OnPointDown(void) = 0;
};

class IDragHandler {
public:
	virtual void OnDragPointer(void) = 0;
};