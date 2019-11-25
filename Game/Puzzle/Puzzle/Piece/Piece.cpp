#include "stdafx.h"
#include "Piece.h"
#include "../Component/Transform/Transform.h"
#include "../Component/Collider/CircleCollider/CircleCollider.h"
#include "../Component/Animation/Animation.h"
#include "../Module/Image/ImageModule.h"

Piece::Piece()
{
}

Piece::Piece(string imgKey, D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot)
{
	AddComponent<Transform>()->SetPosChain(pos)->SetSizeChain(size)->SetPivotChain(pivot)->SetAngleR(0.0f);
	GetComponent<Transform>()->SetRect(MakeRect(pos, size, pivot));
	
	//AddComponent<CircleCollider>()->SetTransformChain(GetComponent<Transform>());
	img = _IMAGE->FindImage(imgKey);
}


Piece::~Piece()
{
}

void Piece::Init(void)
{
	isActive = true;
	mode = OBJECT_MODE::INGAME;
	layer = LAYER::DEFAULT;
}

void Piece::Release(void)
{
	for (UINT i = 0; i < vComponent.size(); i++)
	{
		SafeRelease(vComponent[i]);
	}

	vComponent.clear();
	vector<Component*> temp;
	temp.swap(vComponent);
}

void Piece::Update(void)
{
	for (UINT i = 0; i < vComponent.size(); i++)
	{
		vComponent[i]->Update();
	}
}

void Piece::Render(void)
{
	_RenderTarget->DrawRectangle(GetComponent<Transform>()->GetRect(), _Device->pDefaultBrush);

	//img->Render(GetComponent<Transform>());
}

void Piece::OnCollisionEnter(Collider * coll)
{
}

void Piece::OnCollisionStay(Collider * coll)
{
}

void Piece::OnCollisionEnd(Collider * coll)
{
}
