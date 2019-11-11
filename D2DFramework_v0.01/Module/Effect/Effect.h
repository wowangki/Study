#pragma once
class Effect
{
private:
	ImageModule* img;
	string imgName;
	POINTF pos;
	int effectSpeed;
	int frameX, frameY;
	POINT currentFrame;
	int frameTime;

	bool isActive;

public:
	Effect(string effectNickName, int _effectSpeed);
	~Effect();

	void Start(float x, float y);
	void Reset();

	void Update();
	void Render();

public:
	bool GetisActive() { return isActive; }
	string GetName() { return imgName; }
};

