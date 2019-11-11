#pragma once
#include "../SingletonBase.h"
#include <map>	
#include <vector>

class Effect;
class EffectModule : public SingletonBase<EffectModule>
{
private:
	map<string, Effect*> mEffect;
	vector<Effect*> vPlayIndex;

public:
	EffectModule();
	~EffectModule();

	void CreateEffect(string nickName, int frameSpeed);
	void Update(void);
	void Render(void);

	void Play(string nickName, float x, float y);
};