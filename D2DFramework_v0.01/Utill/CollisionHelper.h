#pragma once

namespace nCollision {
	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to);
	bool IsInRectPoint(D2D_RECT_F from, D2D_POINT_2F to);
	bool IsInCirPoint(D2D1_ELLIPSE cir, D2D_POINT_2F point);
	bool IsRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE cir);
	bool IsInCircle(D2D1_ELLIPSE from, D2D1_ELLIPSE to);
	float GetDistance(D2D_POINT_2F from, D2D_POINT_2F to);
	float GetAngle(D2D_POINT_2F from, D2D_POINT_2F to);

	D2D_POINT_2F GetOverlapSize(D2D_RECT_F from, D2D_RECT_F to);
	D2D_POINT_2F GetOverlapSize(D2D_RECT_F rect, D2D1_ELLIPSE cir);
	D2D_POINT_2F GetOverlapSize(D2D1_ELLIPSE from, D2D1_ELLIPSE to);
}

//RoundedRect Collision