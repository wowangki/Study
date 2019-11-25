//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== CAPSULE FIGURE ========================//

#pragma once
struct CapsuleF
{
	D2D_RECT_F rc;
	D2D1_ELLIPSE cir[2];
};

inline CapsuleF Capsule(D2D_RECT_F rc, D2D1_ELLIPSE* cir) {
	CapsuleF capsule;

	capsule.rc = rc;
	capsule.cir[0] = cir[0];
	capsule.cir[1] = cir[1];

	return capsule;
}

