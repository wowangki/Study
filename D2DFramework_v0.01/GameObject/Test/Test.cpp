#include "stdafx.h"
#include "Test.h"
#include "../Module/Transform/Transform.h"
#include "../Module/Collider/RectCollider/RectCollider.h"

Test::Test()
{
}

Test::Test(D2D_POINT_2F pos, D2D_SIZE_F size, bool isControl, CollisionMediator* mediator)
{
	transform = new Transform(pos, size);
	collider = new RectCollider(this, transform, PIVOT_CC, false, mediator);

	this->isControl = isControl;
}

Test::~Test()
{
}

void Test::Init(void)
{
		
}

void Test::Release(void)
{
}

void Test::Update(void)
{
	if (!isControl) return;

	if (_KEY->StayKeyDown(VK_UP)) {
		transform->SetPos(transform->GetPos().x, transform->GetPos().y - 1.0f);
	}
	else if (_KEY->StayKeyDown(VK_DOWN)) {
		transform->SetPos(transform->GetPos().x, transform->GetPos().y + 1.0f);
	}
	else if (_KEY->StayKeyDown(VK_LEFT)) {
		transform->SetPos(transform->GetPos().x - 1.0f, transform->GetPos().y);
	}
	else if (_KEY->StayKeyDown(VK_RIGHT)) {
		transform->SetPos(transform->GetPos().x + 1.0f, transform->GetPos().y);
	}
}

void Test::Render(void)
{
	collider->Render();
}

void Test::OnCollisionEnter(ColliderBase * other)
{
}

void Test::OnCollisionStay(ColliderBase * other)
{
}
