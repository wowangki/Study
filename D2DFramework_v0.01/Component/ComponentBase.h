#pragma once

class ComponentBase
{
public:
	virtual ~ComponentBase()
	{
		//난 이거 안될거 같은데.. delete 키워드로 들어온 소멸자에서 자기자신 소멸시키면 오류날듯
		delete this; 
	}

	virtual void Update(void) = 0;
};

