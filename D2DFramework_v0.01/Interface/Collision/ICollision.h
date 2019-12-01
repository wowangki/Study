//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== COLLISION INTERFACE ===================//

#pragma once

class Collider;
class ICollision {

public:
	virtual void OnCollisionEnter(Collider* coll) = 0;	// Collision Start
	virtual void OnCollisionStay(Collider* coll) = 0;		// Collision Stay
	virtual void OnCollisionEnd(Collider* coll) = 0;		// Collisino End
};

class ITrigger {

public:
	virtual void OnTriggerEnter(Collider* coll) = 0;	// Trigger Start
	virtual void OnTriggerStay(Collider* coll) = 0;		// Trigger Stay
	virtual void OnTriggerEnd(Collider* coll) = 0;		// Trigger End
};