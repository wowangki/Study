#include "stdafx.h"
#include "TimerModule.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

TimerModule::TimerModule()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodTime)) {
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
		timeScale = 1.0f / _periodTime;
	}
	else {
		isHardware = false;
		_lastTime = timeGetTime();
		timeScale = 0.001f;
	}
}


TimerModule::~TimerModule()
{
}

void TimerModule::UpdateTime(float frameLock)
{
	if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	else _curTime = timeGetTime();

	timeElapsed = (_curTime - _lastTime) * timeScale;

	if (frameLock > 0.0f) {
		while (timeElapsed < (1.0f / frameLock))
		{
			if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			timeElapsed = (_curTime - _lastTime) * timeScale;
		}
	}

	_lastTime = _curTime;
	FPSFrameCount++;
	FPSTimeElapsed += timeElapsed;
	worldTime += timeElapsed;

	if (FPSTimeElapsed > 1.0f) {
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0.0f;
	}
}

void TimerModule::RenderTime(void)
{
	WCHAR timeString[256];
#if defined(DEBUG) || defined(_DEBUG)
	static TCHAR timeTextString[] = L"WorldTime : %.2f\nFrameCount : %f\nFPS : %d";

	//	유니코드 기반으로 프로그램을 만들 때는 wsprintf 도 유용한데 플롯 지원 안함
	//	그래서 float 사용하려면 _stprintf_s 를 사용하면 됨
	_stprintf_s(timeString, timeTextString, worldTime, timeElapsed, frameRate);
	_FONT->Render(timeString, RectF(0.0f, 0.0f, 200.0f, 100.0f));
#else
	static TCHAR timeTextString[] = L"FPS : %d";

	_stprintf_s(timeString, timeTextString, frameRate);
	_FONT->Render(timeString, RectF(WINSIZEX - 50.0f, 0.0f, 100.0f, 30.0f));
#endif
}
