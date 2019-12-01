//============================== 19.11.24 ===============================//
//========================= MADE BY KIM WANKI============================//
//========================= Controller ==================================//
#pragma once
#include "../Component/Component.h"
#include <map>

enum CONTROL_KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	ATTACK,
	JUMP
};

class Controller : public Component
{
protected:
	map<CONTROL_KEY, int> mControll;
	typedef map<CONTROL_KEY, int>::iterator mIter;


public:
	Controller();
	~Controller();

	virtual void SetControllKey(void);

	inline int GetKey(CONTROL_KEY key) {
		if (mControll.empty()) return NULL;

		mIter iter = mControll.begin();
		for (iter; iter != mControll.end(); ++iter) {
			if (iter->first == key)
				return iter->second;
		}

		return NULL;
	}
};

