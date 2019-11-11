#include "stdafx.h"
#include "EffectModule.h"
#include "Effect.h"

EffectModule::EffectModule()
{
}

EffectModule::~EffectModule()
{
	for (UINT i = 0; i < vPlayIndex.size(); ++i)
		SafeDelete(vPlayIndex[i]);

	for (auto& p : mEffect)
		SafeDelete(p.second);
}

void EffectModule::CreateEffect(string nickName, int frameSpeed)
{
	for (auto& p : mEffect)
		if (p.first == nickName) return;

	Effect* pTemp = new Effect(nickName, frameSpeed);

	mEffect.insert(make_pair(nickName, pTemp));
}

void EffectModule::Update(void)
{
	for (UINT i = 0; i < vPlayIndex.size(); ++i)
		vPlayIndex[i]->Update();
}

void EffectModule::Render(void)
{
	for (UINT i = 0; i < vPlayIndex.size(); ++i)
		vPlayIndex[i]->Render();
}

void EffectModule::Play(string nickName, float x, float y)
{
	if (mEffect.find(nickName) == mEffect.end()) return;

	for (UINT i = 0; i < vPlayIndex.size(); ++i) {
		if (vPlayIndex[i]->GetisActive()) continue;
		if (vPlayIndex[i]->GetName() != nickName) continue;

		vPlayIndex[i]->Start(x, y);
		return;
	}

	Effect* pTemp = new Effect(*mEffect[nickName]);
	pTemp->Start(x, y);
	vPlayIndex.push_back(pTemp);
}
