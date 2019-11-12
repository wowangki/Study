#pragma once
#include "stdafx.h"

//클래스는 네임스페이스로 바꿔서 정적함수로 만들던가
//내부를 static함수로 만들어서 사용하면 번거롭지 않음
class CollisionHelper {
public:
	bool isInRect(D2D_RECT_F from, D2D_RECT_F to)
	{
		if ((from.left <= to.right && from.right >= to.left) &&
			(from.top <= to.bottom && from.bottom >= to.top))
			return true;

		return false;
	}

	bool isInRectPoint(D2D_RECT_F from, POINT to)
	{
		if ((from.left <= to.x && from.right >= to.x) &&
			from.top <= to.y && from.bottom >= to.y)
			return true;

		return false;
	}

	bool isInCirPoint(float x, float y, D2D1_ELLIPSE cir)
	{
		float dx = cir.point.x - x;
		float dy = cir.point.y - y;

		//pow = dx * dx
		//sqrt, +f(float)
		float p = sqrtf(pow(dx, 2) + pow(dy, 2));

		return (p < cir.radiusX) ? true : false;
	}

	bool IsRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE cir)
	{
		if ((rect.left <= cir.point.x && rect.right >= cir.point.x) ||
			(rect.top <= cir.point.y && rect.bottom >= cir.point.y))
		{
			D2D_RECT_F temp =
			{
				rect.left - cir.radiusX,
				rect.top - cir.radiusX,
				rect.right + cir.radiusX,
				rect.bottom + cir.radiusX
			};

			if ((temp.left <= cir.point.x && temp.right >= cir.point.x) &&
				(temp.top <= cir.point.y && temp.bottom >= cir.point.y))
				return true;
		}
		else {
			if (isInCirPoint(rect.left, rect.top, cir))return true;
			if (isInCirPoint(rect.left, rect.bottom, cir)) return true;
			if (isInCirPoint(rect.right, rect.top, cir)) return true;
			if (isInCirPoint(rect.right, rect.bottom, cir)) return true;
		}

		return false;
	}
};


//이런 인터페이스는 인터페이스 헤더파일을 만들어서 한번에 불러오면 좋음 
class ColliderBase;
class ITrigger {

public:
	virtual void OnTriggerEnter(ColliderBase* other) = 0;
	virtual void OnTriggerStay(ColliderBase* other) = 0;
	virtual void OnTriggerExit(ColliderBase* other) = 0;
};

class ColliderBase;
class ICollision {

public:
	virtual void OnCollisionEnter(ColliderBase* other) = 0;
	virtual void OnCollisionStay(ColliderBase* other) = 0;
	virtual void OnCollisionExit(ColliderBase* other) = 0;
};