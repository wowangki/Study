#include "stdafx.h"
#include "Animation.h"
#include "Animate/Animate.h"

Animation::Animation()
	:index(0)
{
}


Animation::~Animation()
{
}

HRESULT Animation::Init(void)
{
	return S_OK;
}

void Animation::Release(void)
{
	for (UINT i = 0; i < vAnimation.size(); i++) {
		vAnimation[i]->Release();
	}
	vAnimation.clear();

	vector<Animate*> vTemp;
	vTemp.swap(vAnimation);
}

void Animation::Update(void)
{
	vAnimation[index]->Update();
}

void Animation::Render(void)
{
	vAnimation[index]->Render();
}
