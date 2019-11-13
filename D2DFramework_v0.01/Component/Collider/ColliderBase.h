#pragma once
#include "../ComponentBase.h"
#include "CollisionHelper.h"


//ColliderBase 는 이미 ComponentBase에서 선언한 Update함수를 가지고 있음 여기서 선언을 안해도 불러올 수 있음!!
//어렵게 할 필요없이 원과 렉트로 모든 충돌을 하면 좋을듯 나도 그럴거라 ㅎㅎㅎㅎ
//ITrigger는 인터페이스인데 상속관계로 해야되는거 같은데?
class Transform;
class ColliderBase : public ComponentBase //, public ITrigger 요기에 해서 선언해서 이중상속(인터페이스는 상속해서 사용, 다중상속으로, 인터페이스는 순수가상함수를 가진 추상클래스)
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

