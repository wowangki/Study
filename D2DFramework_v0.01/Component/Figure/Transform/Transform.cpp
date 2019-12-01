#include "stdafx.h"
#include "Transform.h"
#include "../GameObject/GameObject.h"

Transform::Transform()
	:worldPos({ 0,0 }), localPos({ 0,0 }), size({ 0,0 }), pivot(PIVOT_LT), worldAngle(0.0f),
	localAngle(0.0f), parent(this)
{
}

Transform::Transform(GameObject * object)
	: worldPos({ 0,0 }), localPos({ 0,0 }), size({ 0,0 }), pivot(PIVOT_LT), worldAngle(0.0f),
	localAngle(0.0f), parent(this)
{
	this->object = object;
}

Transform::~Transform()
{
}
// 2019.11.27 ==================================================================//
// �ʱ�ȭ (��� ��ǥ �ʿ��) ====================================================//
// ============================================================================//
HRESULT Transform::Init(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle, Transform * parent)
{
	while (true) {
		if (angle >= 0.0f && angle < 2 * PI) break;

		if (angle > 0) {
			angle -= 2 * PI;
		}
		else {
			angle += 2 * PI;
		}
	}
	
	if (!parent) {
		this->worldPos = this->localPos = pos;
		this->size = size;
		this->pivot = pivot;
		this->worldAngle = this->localAngle = angle;
		this->parent = this;
	}
	else {
		this->parent = parent;
		parent->AddChild(this);
		this->localPos = pos;
		this->worldPos.x = parent->worldPos.x + localPos.x;
		this->worldPos.y = parent->worldPos.y + localPos.y;
		this->size = size;
		this->pivot = pivot;
		this->localAngle = angle;
		this->worldAngle = parent->worldAngle + localAngle;
	}

	rc = MakeRect(worldPos, this->size, this->pivot);

	return S_OK;
}

// 2019.11.27 ==================================================================//
// �ʱ�ȭ (��� ��ǥ ���ʿ� ��) =================================================//
// ============================================================================//
HRESULT Transform::Init(Transform * parent)
{
	this->parent = parent;
	parent->AddChild(this);
	this->worldPos.x = parent->worldPos.x;
	this->worldPos.y = parent->worldPos.y;
	this->size = parent->size;
	this->pivot = parent->pivot;
	this->worldAngle = parent->worldAngle;

	rc = MakeRect(worldPos, size, pivot);

	return S_OK;
}

// 2019.11.27 ==================================================================//
// �޸� ���� =================================================================//
// ============================================================================//
void Transform::Release(void)
{
	if (children.empty()) return;

	for (lIter iter = children.begin(); iter != children.end(); ++iter) {
		SafeRelease(*iter);
	}

	children.clear();
	list<Transform*> temp;
	temp.swap(children);
}

// 2019.11.27 ==================================================================//
// ������Ʈ ====================================================================//
// ============================================================================//
void Transform::Update(void)
{
	if (parent == this) {
		worldPos = localPos;
		worldAngle = localAngle;
	}
	else {
		worldPos.x = parent->worldPos.x + localPos.x;
		worldPos.y = parent->worldPos.y + localPos.y;
		worldAngle = parent->worldAngle + localAngle;
	}

	while (true) {
		if (worldAngle >= 0.0f && worldAngle < 2 * PI) break;

		if (worldAngle > 0) {
			worldAngle -= 2 * PI;
		}
		else{
			worldAngle += 2 * PI;
		}
	}

	rc = MakeRect(worldPos, size, pivot);

	if (children.empty()) return;
	for (UINT i = 0; i < children.size(); i++)
	{
		(children.front() + i)->Update();
	}
}

// 2019.11.27 ==================================================================//
// ������ (����Ʈ ����) =======================================================//
// ============================================================================//
void Transform::Render(void)
{
	if(object->GetMode() == OBJECT_MODE::TOOLSET)
		_RenderTarget->DrawRectangle(rc, _Device->pDefaultBrush);
}

// 2019.11.27 ==================================================================//
// ������ǥ(������ǥ) ���� ======================================================//
// ============================================================================//
void Transform::SetWorldPos(D2D_POINT_2F worldPos)
{
	this->worldPos = worldPos;
}

// 2019.11.27 ==================================================================//
// ������ǥ(�����ǥ) ���� ======================================================//
// ============================================================================//
void Transform::SetLocalPos(D2D_POINT_2F localPos)
{
	this->localPos = localPos;
	Update();
}

// 2019.11.27 ==================================================================//
// ũ�� ���� ===================================================================//
// ============================================================================//
void Transform::SetSize(D2D_SIZE_F size)
{
	this->size = size;
	rc = MakeRect(worldPos, size, pivot);
}

// 2019.11.27 ==================================================================//
// �Ǻ� ���� ===================================================================//
// ============================================================================//
void Transform::SetPivot(PIVOT pivot)
{
	this->pivot = pivot;
	rc = MakeRect(worldPos, size, pivot);
}

// 2019.11.27 ==================================================================//
// ���尢��(���밢��) ���� ======================================================//
// ============================================================================//
void Transform::SetWorldAngle(float degree)
{
	if (degree >= 360.0f) degree -= 360.0f;
	this->worldAngle = DegreeToRadian(degree);
}

// 2019.11.27 ==================================================================//
// ���ð���(��밢��) ���� ======================================================//
// ============================================================================//
void Transform::SetLocalAngle(float degree)
{
	if (degree >= 360.0f) degree -= 360.0f;
	float temp = this->localAngle;
	this->localAngle = DegreeToRadian(degree);

	worldAngle += localAngle - temp;

	while (true) {
		if (worldAngle >= 0.0f && worldAngle < 2 * PI) break;

		if (worldAngle > 0) {
			worldAngle -= 2 * PI;
		}
		else {
			worldAngle += 2 * PI;
		}
	}
}

// 2019.11.27 ==================================================================//
// ��Ʈ ���� ===================================================================//
// ============================================================================//
void Transform::SetRect(D2D_RECT_F rect)
{
	rc = rect;
	Update();
}

// 2019.11.27 ==================================================================//
// �θ�(Root / Master) ���� ====================================================//
// ============================================================================//
void Transform::SetParent(Transform * parent)
{
	if (this->parent != this) {
		this->parent->RemoveChild(this);
	}

	this->parent = parent;
	Update();
}

// 2019.11.27 ==================================================================//
// �ڽ�(Leaf / Slave) �߰� ====================================================//
// ============================================================================//
void Transform::AddChild(Transform * child)
{
	lIter iter = children.begin();

	for (iter; iter != children.end(); ++iter) {
		if (*iter == child) return;
	}
	child->SetParent(this);
	children.push_back(child);

	Update();
}

// 2019.11.27 ==================================================================//
// �ڽ�(Leaf / Slave) ���� ====================================================//
// ============================================================================//
void Transform::RemoveChild(Transform * child)
{
	if (children.empty()) return;

	children.remove(child);
	Update();
}

// 2019.11.27 ==================================================================//
// ���� ��ǥ(���� ��ǥ) ü�� ���� ================================================//
// ============================================================================//
Transform * Transform::SetWorldPosChain(D2D_POINT_2F worldPos)
{
	SetWorldPos(worldPos);
	return this;
}

// 2019.11.27 ==================================================================//
// ���� ��ǥ(��� ��ǥ) ü�� ���� ================================================//
// ============================================================================//
Transform * Transform::SetLocalPosChain(D2D_POINT_2F localPos)
{
	SetLocalPos(localPos);
	return this;
}

// 2019.11.27 ==================================================================//
// ũ�� ü�� ���� ===============================================================//
// ============================================================================//
Transform * Transform::SetSizeChain(D2D_SIZE_F size)
{
	SetSize(size);
	return this;
}

// 2019.11.27 ==================================================================//
// �Ǻ� ü�� ���� ===============================================================//
// ============================================================================//

Transform * Transform::SetPivotChain(PIVOT pivot)
{
	SetPivot(pivot);
	return this;
}

// 2019.11.27 ==================================================================//
// ���� ����(���� ����) ü�� ���� ================================================//
// ============================================================================//
Transform * Transform::SetWorldAngleChain(float degree)
{
	SetWorldAngle(degree);
	return this;
}

// 2019.11.27 ==================================================================//
// ���� ����(��� ����) ü�� ���� ================================================//
// ============================================================================//
Transform * Transform::SetLocalAngleChain(float degree)
{
	SetLocalAngle(degree);
	return this;
}

// 2019.11.27 ==================================================================//
// ��Ʈ ü�� ���� ===============================================================//
// ============================================================================//
Transform * Transform::SetRectChain(D2D_RECT_F rect)
{
	SetRect(rect);
	return this;
}

// 2019.11.27 ==================================================================//
// �θ� (Root / Master) ü�� ���� ===============================================//
// ============================================================================//
Transform * Transform::SetParentChain(Transform * parent)
{
	SetParent(parent);
	return this;
}

// 2019.11.27 ==================================================================//
// �ڽ� (Leaf / Slave) ü�� �߰� ===============================================//
// ============================================================================//
Transform * Transform::AddChildChain(Transform * child)
{
	AddChild(child);
	return this;
}

// 2019.11.27 ==================================================================//
// �ڽ� (Leaf / Slave) ü�� ���� ===============================================//
// ============================================================================//
Transform * Transform::RemoveChildChain(Transform * child)
{
	RemoveChild(child);
	return this;
}

// 2019.11.27 ==================================================================//
// �̵� ========================================================================//
// ============================================================================//
void Transform::Translate(const D2D_POINT_2F power)
{
	worldPos.x += power.x;
	worldPos.y += power.y;

	if (parent == this) {
		localPos = worldPos;
	}
	else {
		localPos.x += power.x;
		localPos.y += power.y;
	}

	Update();
}

// 2019.11.27 ==================================================================//
// ȸ�� ========================================================================//
// ============================================================================//
void Transform::Ratate(const float degree)
{
	localAngle += DegreeToRadian(degree);
	
	if (parent == this) {
		worldAngle = localAngle;
	}
	else {
		worldAngle = parent->worldAngle + localAngle;
	}

	while (true) {
		if (worldAngle >= 0.0f && worldAngle < 2 * PI) break;

		if (worldAngle > 0) {
			worldAngle -= 2 * PI;
		}
		else {
			worldAngle += 2 * PI;
		}
	}
}
