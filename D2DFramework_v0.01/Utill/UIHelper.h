#pragma once

class IPointerUpHandler {

public:
	virtual void OnPointerUp() = 0;
};

class IPointerDownHandler {

public:
	virtual void OnPointerDown() = 0;
};