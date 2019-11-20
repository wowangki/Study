//====================== 2019.11.21 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Animate ==============================//

#pragma once

class Transform;
class ImageModule;
class Animate final
{
private:
	Transform* transform;		//TRANSFORM

private:
	string imgKey;				//IMAGEKEY
	ImageModule* image;			//IMAGE
	bool isReverse;				//IsReverse;
	float opacity;				//opacity;

	D2D_POINT_2L currentFrame;	//CurrentFRAME
	float currentTime;			//currentFrameTime
	float frameTime;			//frameTime
	bool isCull;				//ISCULL

	bool isPlay;				//IsPlay
	
public:
	Animate();
	explicit Animate(string imgKey, Transform* myTransform);
	~Animate();

	HRESULT Init(void);
	void Release(void);
	void Update(void);
	void Render(void);

	bool IsCulling(void);
	
	inline float GetOpacity(void) const { return opacity; }
	inline bool GetIsReverse(void) const { return isReverse; }

	void ChangeImage(string imgKey) {
		this->imgKey = imgKey;
		image = _IMAGE->FindImage(this->imgKey);
	}

	void SetOpacity(float opacity) { this->opacity = opacity; }
	void SetIsReverse(bool isReverse) { this->isReverse = isReverse; }

	void Play(void) { 
		if (!isPlay) {
			isPlay = true;
			currentFrame = { 0,0 };
		}
	}

	void Stop(void) {
		if (isPlay) {
			isPlay = false;
			currentFrame = { 0,0 };
		}
	}

	void Pause(void) {
		if (isPlay) isPlay = false;
	};

	void Resume(void) {
		if (!isPlay) isPlay = true;
	};
};

