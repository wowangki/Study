#pragma once

namespace nCollision {
	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to);
	bool IsInRectPoint(D2D_RECT_F from, D2D_POINT_2F to);
	bool IsInCirPoint(D2D_POINT_2F point, D2D1_ELLIPSE cir);
	bool IsRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE cir);
	bool IsInCircle(D2D1_ELLIPSE from, D2D1_ELLIPSE to);
	float GetDistance(D2D_POINT_2F from, D2D_POINT_2F to);
	float GetAngle(D2D_POINT_2F from, D2D_POINT_2F to);
}