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
	int index;

public:
	Animation();
	virtual ~Animation();

	virtual HRESULT Init(void);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	void AddAnimation(Animate* animate) {
		vAnimation.emplace_back(animate);
	}

	void SetIndex(int index) { this->index = index; }

};

