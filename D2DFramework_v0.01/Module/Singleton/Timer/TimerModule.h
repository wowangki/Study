#pragma once
class TimerModule
{
private:
	bool isHardware;

	float timeScale;
	float timeElapsed;
	__int64 _periodTime;
	__int64 _lastTime;
	__int64 _curTime;

	unsigned long frameRate;
	unsigned long FPSFrameCount;

	float FPSTimeElapsed;
	float worldTime;

public:
	TimerModule();
	~TimerModule();

	void UpdateTime(float frameLock = 60.0f);
	void RenderTime(void);

	inline float GetElapsedTime(void) const { return timeElapsed; }
	inline float GetTime(void) const { return worldTime; }
	inline float GetFPSTime(void) { return (float)frameRate; }

public:
	static TimerModule* GetInstance() {
		static TimerModule instance;
		return &instance;
	}
};

