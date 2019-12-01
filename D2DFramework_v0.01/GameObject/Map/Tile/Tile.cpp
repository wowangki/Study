#include "stdafx.h"
#include "Tile.h"
#include "../Component/Figure/Transform/Transform.h"
#include "../Component/"
Tile::Tile()
{

}

Tile::Tile(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot, float angle)
{
	AddComponent<Transform>()->SetPosChain(pos)->SetSizeChain(size)->SetPivotChain(pivot)->SetAngleR(angle);
	GetComponent<Transform>()->SetRect(MakeRect(pos, size, pivot));
}


Tile::~Tile()
{
}

void Tile::Render(void)
{
	_RenderTarget->DrawRectangle(GetComponent<Transform>()->GetRect(), _Device->pDefaultBrush);

	//for (UINT i = 0; i < vComponent.size(); i++) {
	//	vComponent[i]->Render();
	//}
}
