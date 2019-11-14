#pragma once

class IState {
public:
	virtual ~IState() {};

	virtual void Update(void) = 0;
};