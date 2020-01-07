#include "stdafx.h"
#include "Transform.h"
#include "../GameObject/GameObject.h"

DECLARE_COMPONENT(Transform);

Transform::Transform(GameObject * object)
	: worldPos({ 0,0 }), localPos({ 0,0 }), size({ 0,0 }), pivot(PIVOT_LT), worldAngle(0.0f),
	localAngle(0.0f), parent(nullptr)
{
	this->object = object;
}

Transform::~Transform()
{
}

// 2019.11.27 ==================================================================//
// 초기화 (상대 좌표 필요시) ====================================================//
// ============================================================================//
HRESULT Transform::Init(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle, Transform * parent)
{
	DegreeToRadian(RevisionDegree(angle));

	if (!parent) {
		this->worldPos = this->localPos = pos;
		this->size = size;
		this->pivot = pivot;
		this->worldAngle = this->localAngle = angle;
	}
	else {
		this->localPos = pos;
		this->worldPos.x = parent->worldPos.x + localPos.x;
		this->worldPos.y = parent->worldPos.y + localPos.y;
		this->size = size;
		this->pivot = pivot;
		this->localAngle = angle;
		this->worldAngle = parent->worldAngle + localAngle;
		AddParent(parent);
	}

	rc = MakeRect(worldPos, this->size, this->pivot);

	return S_OK;
}

// 2019.11.27 ==================================================================//
// 초기화 (상대 좌표 미필요 시) =================================================//
// ============================================================================//
HRESULT Transform::Init(Transform * parent)
{
	if (!parent) return S_OK;

	this->worldPos.x = parent->worldPos.x;
	this->worldPos.y = parent->worldPos.y;
	this->size = parent->size;
	this->pivot = parent->pivot;
	this->worldAngle = parent->worldAngle;
	AddParent(parent);
	rc = MakeRect(worldPos, size, pivot);
	return S_OK;
}

// 2019.11.27 ==================================================================//
// 메모리 해제 =================================================================//
// ============================================================================//
void Transform::Release(void)
{
	if (children.empty()) return;

	for (lIter iter = children.begin(); iter != children.end(); ++iter) {
		SafeRelease(*iter);
	}

	if (!parent) {
		children.clear();
		list<Transform*> temp;
		temp.swap(children);
	}
}

// 2019.11.27 ==================================================================//
// 업데이트 ====================================================================//
// ============================================================================//
void Transform::Update(void)
{
	if (!parent) {
		worldPos = localPos;
		worldAngle = localAngle;
	}
	else {
		worldPos.x = parent->worldPos.x + localPos.x;
		worldPos.y = parent->worldPos.y + localPos.y;
		worldAngle = DegreeToRadian(RevisionRadian(parent->worldAngle + localAngle));
	}

	rc = MakeRect(worldPos, size, pivot);

	if (children.empty()) return;

	lIter iter = children.begin();

	for (iter; iter != children.end(); ++iter) {
		(*iter)->Update();
	}
}

// 2019.11.27 ==================================================================//
// 렌더링 (에디트 모드용) =======================================================//
// ============================================================================//
void Transform::Render(void)
{
	_RenderTarget->DrawRectangle(rc, _Device->pDefaultBrush);
}

// 2019.11.27 ==================================================================//
// 월드좌표(절대좌표) 설정 ======================================================//
// ============================================================================//
void Transform::SetWorldPos(D2D_POINT_2F worldPos)
{
	this->worldPos = worldPos;
	if (parent) {
		localPos.x += this->worldPos.x - localPos.x;
		localPos.y += this->worldPos.y - localPos.y;
	}
}

// 2019.11.27 ==================================================================//
// 로컬좌표(상대좌표) 설정 ======================================================//
// ============================================================================//
void Transform::SetLocalPos(D2D_POINT_2F localPos)
{
	this->localPos = localPos;
	Update();
}

// 2019.11.27 ==================================================================//
// 크기 설정 ===================================================================//
// ============================================================================//
void Transform::SetSize(D2D_SIZE_F size)
{
	this->size = size;
}

// 2019.11.27 ==================================================================//
// 피봇 설정 ===================================================================//
// ============================================================================//
void Transform::SetPivot(PIVOT pivot)
{
	this->pivot = pivot;
}

// 2019.11.27 ==================================================================//
// 월드각도(절대각도) 설정 ======================================================//
// ============================================================================//
void Transform::SetWorldAngle(float degree)
{
	this->worldAngle = DegreeToRadian(RevisionDegree(degree));
	this->localAngle = RevisionRadian(worldAngle - localAngle);
}

// 2019.11.27 ==================================================================//
// 로컬각도(상대각도) 설정 ======================================================//
// ============================================================================//
void Transform::SetLocalAngle(float degree)
{
	localAngle = RevisionDegree(degree);
	Update();
}

// 2019.11.27 ==================================================================//
// 렉트 설정 ===================================================================//
// ============================================================================//
void Transform::SetRect(D2D_RECT_F rect)
{
	worldPos.x = (rect.right + rect.left) * 0.5f;
	worldPos.y = (rect.bottom + rect.top) * 0.5f;

	if (parent) {
		localPos.x += worldPos.x - localPos.x;
		localPos.y += worldPos.y - localPos.y;
	}

	size.width = (rect.right - rect.left) * 0.5f;
	size.height = (rect.bottom - rect.top) * 0.5f;

	Update();
}

// 2019.11.27 ==================================================================//
// 부모(Root / Master) 설정 ====================================================//
// ============================================================================//
void Transform::AddParent(Transform * parent)
{
	parent->AddChild(this);
}

void Transform::RemoveParent(void)
{
	parent->RemoveChild(this);
}

// 2019.11.27 ==================================================================//
// 자식(Leaf / Slave) 추가 ====================================================//
// ============================================================================//
void Transform::AddChild(Transform * child)
{
	lIter iter = children.begin();

	for (iter; iter != children.end(); ++iter) {
		if (child == (*iter)) return;
	}

	if (child->parent != this) child->parent = this;
	child->localPos.x = child->worldPos.x - worldPos.x;
	child->localPos.y = child->worldPos.y - worldPos.y;
	children.push_back(child);
	Update();
}

// 2019.11.27 ==================================================================//
// 자식(Leaf / Slave) 제거 ====================================================//
// ============================================================================//
void Transform::RemoveChild(Transform * child)
{
	if (children.empty()) return;

	lIter iter = children.begin();

	for (iter; iter != children.end(); ++iter) {
		if (child == (*iter)) {
			children.erase(iter);
			child->parent = nullptr;
			child->Update();
			return;
		}
	}
}

// 2019.11.27 ==================================================================//
// 월드 좌표(절대 좌표) 체인 설정 ================================================//
// ============================================================================//
Transform * Transform::SetWorldPosChain(D2D_POINT_2F worldPos)
{
	SetWorldPos(worldPos);
	return this;
}

// 2019.11.27 ==================================================================//
// 로컬 좌표(상대 좌표) 체인 설정 ================================================//
// ============================================================================//
Transform * Transform::SetLocalPosChain(D2D_POINT_2F localPos)
{
	SetLocalPos(localPos);
	return this;
}

// 2019.11.27 ==================================================================//
// 크기 체인 설정 ===============================================================//
// ============================================================================//
Transform * Transform::SetSizeChain(D2D_SIZE_F size)
{
	SetSize(size);
	return this;
}

// 2019.11.27 ==================================================================//
// 피봇 체인 설정 ===============================================================//
// ============================================================================//

Transform * Transform::SetPivotChain(PIVOT pivot)
{
	SetPivot(pivot);
	return this;
}

// 2019.11.27 ==================================================================//
// 월드 각도(절대 각도) 체인 설정 ================================================//
// ============================================================================//
Transform * Transform::SetWorldAngleChain(float degree)
{
	SetWorldAngle(degree);
	return this;
}

// 2019.11.27 ==================================================================//
// 로컬 각도(상대 각도) 체인 설정 ================================================//
// ============================================================================//
Transform * Transform::SetLocalAngleChain(float degree)
{
	SetLocalAngle(degree);
	return this;
}

// 2019.11.27 ==================================================================//
// 렉트 체인 설정 ===============================================================//
// ============================================================================//
Transform * Transform::SetRectChain(D2D_RECT_F rect)
{
	SetRect(rect);
	return this;
}

// 2019.11.27 ==================================================================//
// 부모 (Root / Master) 체인 설정 ===============================================//
// ============================================================================//
Transform * Transform::AddParentChain(Transform * parent)
{
	AddParent(parent);
	return this;
}

Transform * Transform::RemoveParentChain(void)
{
	RemoveParent();
	return nullptr;
}

// 2019.11.27 ==================================================================//
// 자식 (Leaf / Slave) 체인 추가 ===============================================//
// ============================================================================//
Transform * Transform::AddChildChain(Transform * child)
{
	AddChild(child);
	return this;
}

// 2019.11.27 ==================================================================//
// 자식 (Leaf / Slave) 체인 제거 ===============================================//
// ============================================================================//
Transform * Transform::RemoveChildChain(Transform * child)
{
	RemoveChild(child);
	return this;
}

// 2019.11.27 ==================================================================//
// 이동 ========================================================================//
// ============================================================================//
void Transform::Translate(const D2D_POINT_2F power)
{
	localPos.x += power.x;
	localPos.y += power.y;

	Update();
}

// 2019.11.27 ==================================================================//
// 회전 ========================================================================//
// ============================================================================//
void Transform::Ratate(const float degree)
{
	localAngle = RevisionRadian(localAngle += DegreeToRadian(degree));
	
	Update();
}
