#pragma once

class ComponentBase
{
public:
	virtual ~ComponentBase() { delete this; }

	virtual void Update(void) = 0;
};

