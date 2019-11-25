#include "stdafx.h"
#include "Transform.h"


Transform::Transform()
	:pos({0,0}), size({0,0}), angle(0.0f)
{
}

Transform::Transform(GameObject * myObject)
	: myObject(myObject)
{
}

Transform::Transform(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle)
	:pos(pos), size(size), pivot(pivot), angle(angle)
{
	rc = MakeRect(pos, size, pivot);
}


Transform::~Transform()
{
}
