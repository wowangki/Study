//====================== 2019.12.07 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Sprite ================================//

#pragma once
#include "../Component/Component.h"

class ImageInfo;
class Transform;
class GameObject;
class Sprite final : public Component
{
private:
	ImageInfo* imageInfo;

private:
	Transform* transform;
	D2D_POINT_2L frame;

	float opacity;
	bool isReverse;
	bool isCull;

public:
	Sprite();
	explicit Sprite(GameObject* object);
	~Sprite();

	HRESULT Init(string nickName, D2D_POINT_2L frame = { 0,0 });
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	inline ImageInfo* GetImageInfo(void) const { return imageInfo; }
	inline Transform* GetTransform(void) const { return transform; }
	inline D2D_POINT_2L GetFrame(void) const { return frame; }
	inline float GetOpacity(void) const { return opacity; }
	inline bool GetIsCull(void) const { return isCull; }

	void SetImageInfo(ImageInfo* img) { this->imageInfo = img; }
	void SetFrameX(int x) { frame.x = x; }
	void SetFrameY(int y) { frame.y = y; }
	void IncreaseFrame(D2D_POINT_2L quantity) { 
		this->frame.x += quantity.x;
		this->frame.y += quantity.y;
	}

	void SetOpacity(float opacity) {
		if (opacity >= 1.0f) opacity = 1.0f;
		else if (opacity <= 0.0f) opacity = 0.0f;

		this->opacity = opacity;
	}

private:
	D2D_POINT_2F GetDxPoint(D2D_POINT_2F pos, D2D_SIZE_F size, PIVOT pivot);
};

