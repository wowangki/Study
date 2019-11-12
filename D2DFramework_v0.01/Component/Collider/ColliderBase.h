#pragma once
#include "../ComponentBase.h"
#include "CollisionHelper.h"


//ColliderBase �� �̹� ComponentBase���� ������ Update�Լ��� ������ ���� ���⼭ ������ ���ص� �ҷ��� �� ����!!
//��ư� �� �ʿ���� ���� ��Ʈ�� ��� �浹�� �ϸ� ������ ���� �׷��Ŷ� ��������
//ITrigger�� �������̽��ε� ��Ӱ���� �ؾߵǴ°� ������?
class Transform;
class ColliderBase : public ComponentBase //, public ITrigger ��⿡ �ؼ� �����ؼ� ���߻��(�������̽��� ����ؼ� ���, ���߻������, �������̽��� ���������Լ��� ���� �߻�Ŭ����)
{
protected:
	Transform* transform;		// Transform

	ITrigger* Itrigger;			// TriggerInterface
	bool isColl;				// isCollision
	bool isTrigger;				// isTrigger
	

public:
	virtual void Update(void) = 0;

	inline bool GetIsColl(void) { return isColl; }
	inline bool GetIsTrigger(void) { return isTrigger; }

	void SetIsColl(bool isColl) { this->isColl = isColl; }
	void SetIsTrigger(bool isTrigger) { this->isTrigger = isTrigger; }
};

