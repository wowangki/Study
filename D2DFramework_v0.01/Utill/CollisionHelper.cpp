//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COLLISION HELPER ======================//


#include "stdafx.h"
#include "CollisionHelper.h"

namespace nCollision {
	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to)
	{
		if ((from.left <= to.right && from.right >= to.left) &&
			(from.top <= to.bottom && from.bottom >= to.top))
			return true;

		return false;
	}

	bool IsInRectPoint(D2D_RECT_F from, D2D_POINT_2F to)
	{
		if ((from.left <= to.x && from.right >= to.x) &&
			from.top <= to.y && from.bottom >= to.y)
			return true;

		return false;
	}

	bool IsInCirPoint(D2D1_ELLIPSE cir, D2D_POINT_2F point)
	{
		float dx = cir.point.x - point.x;
		float dy = cir.point.y - point.y;

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
			if (IsInCirPoint(cir, { rect.left, rect.top } ))return true;
			if (IsInCirPoint(cir, { rect.left, rect.bottom } )) return true;
			if (IsInCirPoint(cir, { rect.right, rect.top } )) return true;
			if (IsInCirPoint(cir, { rect.right, rect.bottom } )) return true;
		}

		return false;
	}

	bool IsInCircle(D2D1_ELLIPSE from, D2D1_ELLIPSE to)
	{
		float angle = GetAngle(from.point, to.point);

		float fromCos = from.radiusX * cos(angle);
		float fromSin = from.radiusY * sin(angle);

		float toCos = to.radiusX * cos(angle);
		float toSin = to.radiusY * sin(angle);

		float result = sqrtf(pow(fromCos + toCos, 2) + pow(fromSin + toSin, 2));
		
		if (GetDistance(from.point, to.point) <= result) return true;

		return false;
	}

	float GetDistance(D2D_POINT_2F from, D2D_POINT_2F to) {
		float temp;

		temp = sqrtf((pow(from.x - to.x, 2)) + (pow(from.y - to.y, 2)));

		return temp;
	}

	float GetAngle(D2D_POINT_2F from, D2D_POINT_2F to)
	{
		float x = to.x - from.x;
		float y = to.y - from.y;

		float angle = atan2(y, x) * (180.0f / PI);
		if (angle < 0.0f) angle += 360.0f;

		return DegreeToRadian(angle);
	}

//====================== 2019.12.01 ========================//
//================== MADE BY KIM WANKI =====================//
//============= OVERLAPSIZE (Rect to Rect) =================//
	D2D_SIZE_F GetOverlapSize(D2D_RECT_F from, D2D_RECT_F to)
	{
		D2D_SIZE_F temp = { 0.0 };
		if (!IsInRect(from, to)) return temp;
		
		D2D_POINT_2F tPos1;
		tPos1.x = (from.right + from.left) * 0.5f;
		tPos1.y = (from.top + from.bottom) * 0.5f;
		D2D_POINT_2F tPos2;
		tPos2.x = (to.right + to.left) * 0.5f;
		tPos2.y = (to.top + to.bottom) * 0.5f;

		float angle = GetAngle(tPos1, tPos2);

		temp.width = (max(from.left, to.left) - min(from.right, to.right)) * cos(angle);
		temp.height = (max(from.top, to.top) - min(from.bottom, to.bottom)) * sin(angle);

		return temp;
	}

//====================== 2019.12.01 ========================//
//================== MADE BY KIM WANKI =====================//
//============ OVERLAPSIZE (Rect to Circle) ================//
	D2D_SIZE_F GetOverlapSize(D2D_RECT_F rect, D2D1_ELLIPSE cir)
	{
		D2D_SIZE_F temp = { 0.0 };
		if (!IsRectInCircle(rect, cir)) return temp;


		return temp;
	}

//====================== 2019.12.01 ========================//
//================== MADE BY KIM WANKI =====================//
//=========== OVERLAPSIZE (Circle to Circle) ===============//
	D2D_SIZE_F GetOverlapSize(D2D1_ELLIPSE from, D2D1_ELLIPSE to)
	{
		D2D_SIZE_F temp = { 0.0 };
		if (!IsInCircle(from, to)) return temp;

		float angle = GetAngle(from.point, to.point);
		
		float fromCos = from.radiusX * cos(angle);
		float fromSin = from.radiusY * sin(angle);
		
		float toCos = to.radiusX * cos(angle);
		float toSin = to.radiusY * sin(angle);

		temp.width = ((from.point.x - to.point.x)) + (fromCos + toCos);
		temp.height = ((from.point.y - to.point.y)) + (fromSin + toSin);

		return temp;
	}

}
