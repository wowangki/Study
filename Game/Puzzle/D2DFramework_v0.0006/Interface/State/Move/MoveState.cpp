#include "stdafx.h"
#include "MoveState.h"
#include "../GameObject/GameObject.h"
#include "../Component/Transform/Transform.h"

MoveState::MoveState()
{
}

MoveState::MoveState(float speed)
	:speed(speed)
{
}


MoveState::~MoveState()
{
}

void MoveState::Update(GameObject * object)
{
	Transform* transform = object->GetComponent<Transform>();
	
}
