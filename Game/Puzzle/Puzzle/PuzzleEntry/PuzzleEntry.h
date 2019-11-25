#pragma once
#include "../System/Application/cApplication.h"

class PuzzleMap;
class PuzzleEntry : public cApplication
{
private:
	PuzzleMap* puzzleMap;

public:
	PuzzleEntry();
	~PuzzleEntry();

	virtual HRESULT Init(void) override;
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

};

