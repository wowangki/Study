//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Animation ==============================//

#pragma once
#include "../Component/Component.h"
#include <vector>

class Animate;
class Animation : public Component
{
private:
	vector<Animate*> vAnimation;

	int vAnimateIndex;		//추후 자료형 변환해서 index

public:
	Animation();
	~Animation();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void AddAnimation(Animate* animate) {
		vAnimation.emplace_back(animate);
	}

};

