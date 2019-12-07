#include "stdafx.h"
#include "Navigator.h"
#include "../Component/Figure/Transform/Transform.h"

Navigator::Navigator()
{
}

Navigator::Navigator(GameObject * myObject)
	:myObject(myObject), start({-OFFSETX, -OFFSETY}), end({OFFSETX, OFFSETY}), target(nullptr)
{

}


Navigator::~Navigator()
{
}

HRESULT Navigator::Init(void)
{
	FindCurrentIndex();


	return S_OK;
}

void Navigator::Release(void)
{
	myObject = nullptr;

	vMap.clear();
	vector<vector<Tile*>> temp;
	vMap.swap(temp);
}

void Navigator::Update(void)
{
}

void Navigator::Render(void)
{
	
}

void Navigator::FindCurrentIndex(void)
{
	UINT y = 0;
	UINT x = 0;
	
}
