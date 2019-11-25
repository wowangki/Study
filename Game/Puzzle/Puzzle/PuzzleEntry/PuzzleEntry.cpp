#include "stdafx.h"
#include "PuzzleEntry.h"
#include "../PuzzleMap/PuzzleMap.h"


PuzzleEntry::PuzzleEntry()
{
}


PuzzleEntry::~PuzzleEntry()
{
}

HRESULT PuzzleEntry::Init(void)
{
	puzzleMap = new PuzzleMap({ WINSIZEX * 0.5f, WINSIZEY * 0.5f }, { 50,50 }, { 10,10 });

	puzzleMap->Init();
	return S_OK;
}

void PuzzleEntry::Release(void)
{
	puzzleMap->Release();
}

void PuzzleEntry::Update(void)
{
	puzzleMap->Update();
}

void PuzzleEntry::Render(void)
{
	puzzleMap->Render();
}
