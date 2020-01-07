#pragma once

namespace nCollision {
	// Rect To Rect Interfere
	bool IsInRect(D2D_RECT_F from, D2D_RECT_F to);
	bool IsInRect(D2D_RECT_F* from, D2D_RECT_F* to);
	// Rect To Point Interfere
	bool IsInRectPoint(D2D_RECT_F from, D2D_POINT_2F to);
	bool IsInRectPoint(D2D_RECT_F* from, D2D_POINT_2F to);
	// Cir To Point Interfere
	bool IsInCirPoint(D2D1_ELLIPSE cir, D2D_POINT_2F point);
	bool IsInCirPoint(D2D1_ELLIPSE* cir, D2D_POINT_2F point);
	// Rect To Cir Interfere
	bool IsRectInCircle(D2D_RECT_F rect, D2D1_ELLIPSE cir);
	bool IsRectInCircle(D2D_RECT_F* rect, D2D1_ELLIPSE* cir);
	// Cir To Cir Interfere
	bool IsInCircle(D2D1_ELLIPSE from, D2D1_ELLIPSE to);
	bool IsInCircle(D2D1_ELLIPSE* from, D2D1_ELLIPSE* to);

	float GetDistance(D2D_POINT_2F from, D2D_POINT_2F to);
	float GetAngle(D2D_POINT_2F from, D2D_POINT_2F to);


	// Rect To Rect RevisionSize Getting
	D2D_POINT_2F GetRevisionSize(D2D_RECT_F from, D2D_RECT_F to);
	D2D_POINT_2F GetRevisionSize(D2D_RECT_F* from, D2D_RECT_F* to);
	// Rect To Cir RevisionSize Getting
	D2D_POINT_2F GetRevisionSize(D2D_RECT_F rect, D2D1_ELLIPSE cir);
	D2D_POINT_2F GetRevisionSize(D2D_RECT_F* rect, D2D1_ELLIPSE* cir);
	// Cir To Cir RevisionSize Getting
	D2D_POINT_2F GetRevisionSize(D2D1_ELLIPSE from, D2D1_ELLIPSE to);
	D2D_POINT_2F GetRevisionSize(D2D1_ELLIPSE* from, D2D1_ELLIPSE* to);
}