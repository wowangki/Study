#include "stdafx.h"
#include "Actor.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/Graphic/Animator/Animator.h"

Actor::Actor()
{
	isAlive = true;
	layer = LAYER::DEFAULT;
	AddComponent(new Transform(this));
	AddComponent(new Animator(this));
}


Actor::~Actor()
{
}