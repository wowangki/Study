#pragma once

class ColliderBase;
//class ITrigger {
//
//public:
//	virtual void OnTriggerEnter(GameObject* other) = 0;
//	virtual void OnTriggerStay(GameObject* other) = 0;
//	virtual void OnTriggerExit(GameObject* other) = 0;
//};

class ICollision {

public:
	virtual void OnCollisionEnter(ColliderBase* other) = 0;
	virtual void OnCollisionStay(ColliderBase* other) = 0;
	virtual void OnCollisionExit(ColliderBase* other) = 0;
};
