#pragma once

namespace nCollision {

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
