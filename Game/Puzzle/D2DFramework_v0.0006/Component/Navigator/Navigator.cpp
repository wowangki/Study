#include "stdafx.h"
#include "Navigator.h"
#include "../GameObject/Map/Tile/Tile.h"
#include "../Component/Transform/Transform.h"

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
	for (int y = start.y; y <= end.y; y++) {
		for (int x = start.x; y <= end.x; x++) {
			vMap[current.y + y][current.x + x]->Render();
		}
	}
}

void Navigator::FindCurrentIndex(void)
{
	UINT y = 0;
	UINT x = 0;
	
	while (true) {
		if (vMap[y][x]->GetComponent<Transform>()->GetRect().left <= myObject->GetComponent<Transform>()->GetPos().x &&
			vMap[y][x]->GetComponent<Transform>()->GetRect().right >= myObject->GetComponent<Transform>()->GetPos().x) {
			current.x = x;
			break;
		}
		x++;
	}

	while (true) {
		if (vMap[y][x]->GetComponent<Transform>()->GetRect().top <= myObject->GetComponent<Transform>()->GetPos().y &&
			vMap[y][x]->GetComponent<Transform>()->GetRect().bottom >= myObject->GetComponent<Transform>()->GetPos().y) {
			current.y = y;
			break;
		}
		y++;
	}
}
