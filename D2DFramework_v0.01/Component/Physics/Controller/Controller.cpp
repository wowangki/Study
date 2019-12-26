#include "stdafx.h"
#include "Controller.h"


Controller::Controller()
{
	SetControllKey();
}


Controller::~Controller()
{
}

HRESULT Controller::Init(void)
{
	return S_OK;
}

void Controller::Release(void)
{
	map<CONTROL_KEY, int> temp;
	temp.swap(mControll);

	mControll.clear();
}

void Controller::Update(void)
{
	if (mControll.empty()) return;

	mIter iter = mControll.begin();
	for (iter; iter != mControll.end(); ++iter) {

	}
}

void Controller::SetControllKey(void)
{
	mControll.insert(make_pair(LEFT, VK_LEFT));
	mControll.insert(make_pair(RIGHT, VK_RIGHT));
	mControll.insert(make_pair(UP, VK_UP));
	mControll.insert(make_pair(DOWN, VK_DOWN));
	mControll.insert(make_pair(ATTACK, VK_CONTROL));
	mControll.insert(make_pair(JUMP, VK_SPACE));
}
