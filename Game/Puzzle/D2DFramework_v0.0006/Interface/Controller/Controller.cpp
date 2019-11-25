#include "stdafx.h"
#include "Controller.h"


Controller::Controller()
{
}


Controller::~Controller()
{
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

