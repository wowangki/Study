//====================== 2019.11.17 ========================//
//================== MADE BY KIM WANKI =====================//
//================== Image Component =======================//

#pragma once
#include "../Component/Component.h"

class Transform;
class ImageInfo;
class Image final : public Component
{
private:
	ImageInfo* imageInfo;

private:
	Transform* transform;
	float opacity;
	bool isCull;

private:
	DEFINE_COMPONENT(Image, Component, false);

public:
	explicit Image(GameObject* object);
	~Image();

	HRESULT Init(string nickName);
	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;

	inline ImageInfo* GetImageInfo(void) const { return imageInfo; }
	inline Transform* GetTransform(void) const { return transform; }
	inline float GetOpacity(void) const { return opacity; }
	inline bool GetIsCull(void) const { return isCull; }

	void SetImageInfo(ImageInfo* img) { this->imageInfo = img; }
	void SetOpacity(float opacity) {
		if (opacity >= 1.0f) opacity = 1.0f;
		else if (opacity <= 0.0f) opacity = 0.0f;

		this->opacity = opacity;
	}
	
};
