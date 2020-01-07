//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== TRANSFORM  ============================//

//====================== 2019.11.27 ========================//
//====================== 1차 수정  ==========================//

#pragma once
#include "../Component/Component.h"
#include <list>

class Transform final : public Component
{
private:
	D2D_POINT_2F worldPos;	// WorldPosition
	D2D_POINT_2F localPos;	// LocalPosition
	D2D_SIZE_F size;		// Size
	PIVOT pivot;			// Pivot

	float worldAngle;		// WorldAngle;
	float localAngle;		// localAngle;
	D2D_RECT_F rc;			// RECT

	Transform* parent;		//Parent (if isolate Transform parent = this)
	list<Transform*> children; // Children
	typedef list<Transform*>::iterator lIter;

private:
	DEFINE_COMPONENT(Transform, Component, false);

public:
	explicit Transform(GameObject* object);
	virtual ~Transform();

	HRESULT Init(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot = PIVOT_LT, float angle = 0.0f, Transform* parent = nullptr);
	HRESULT Init(Transform* parent);

	// Component을(를) 통해 상속됨
	virtual void Release(void)	override;
	virtual void Update(void)	override;
	virtual void Render(void)	override;

	inline D2D_POINT_2F GetWorldPos(void)		const { return worldPos; }
	inline D2D_POINT_2F GetLocalPos(void)		const { return localPos; }
	inline D2D_SIZE_F GetSize(void)				const { return size; }
	inline PIVOT GetPivot(void)					const { return pivot; }
	inline float GetWorldAngle(void)			const { return worldAngle; }
	inline float GetLocalAngle(void)			const { return localAngle; }
	inline D2D_RECT_F GetRect(void)				const { return rc; }
	inline Transform* GetParent(void)			const { return parent; }
	inline Transform* GetChild(Transform* child)const { 	
		for (UINT i = 0; i < children.size(); i++)
		{
			if ((children.front() + i) == child) {
				return children.front() + i;
			}
		}
		return nullptr;
	}

	// Normal Set
	void SetWorldPos(D2D_POINT_2F worldPos);
	void SetLocalPos(D2D_POINT_2F localPos);
	void SetSize(D2D_SIZE_F size);
	void SetPivot(PIVOT pivot);
	void SetWorldAngle(float degree);
	void SetLocalAngle(float degree);
	void SetRect(D2D_RECT_F rect);
	void AddParent(Transform* parent);
	void RemoveParent(void);
	void AddChild(Transform* child);
	void RemoveChild(Transform* child);

	// Chainning Set
	Transform* SetWorldPosChain(D2D_POINT_2F worldPos);
	Transform* SetLocalPosChain(D2D_POINT_2F localPos);
	Transform* SetSizeChain(D2D_SIZE_F size);
	Transform* SetPivotChain(PIVOT pivot);
	Transform* SetWorldAngleChain(float degree);
	Transform* SetLocalAngleChain(float degree);
	Transform* SetRectChain(D2D_RECT_F rect);
	Transform* AddParentChain(Transform* parent);
	Transform* RemoveParentChain(void);
	Transform* AddChildChain(Transform* child);
	Transform* RemoveChildChain(Transform* child);

	// Translate
	void Translate(const D2D_POINT_2F power);
	void Ratate(const float degree);
	
};