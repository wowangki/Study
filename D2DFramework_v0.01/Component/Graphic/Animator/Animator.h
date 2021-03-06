//====================== 2019.12.07 ========================//
//================== MADE BY KIM WANKI =====================//
//=================== Animator =============================//

#pragma once
#include "../Component/Component.h"
#include <map>
#define DEFAULT_FRAMETIME 1.0f

class Sprite;
class Animator final : public Component
{
public:
	DEFINE_COMPONENT(Animator, Component, false);

private:
	map<int, Sprite*> mSprite;
	typedef map<int, Sprite*>::iterator mIter;

	float currentTime;
	float frameTime;

public:
	explicit Animator(GameObject* object);
	virtual ~Animator();

	void AddSprite(int state, string nickName);
	void RemoveSprite(int state);
	void ChangeSprite(int state, string nickName);
	Sprite* FindSprite(int state);
	Sprite* FindSprite(ImageInfo * img);
	Sprite* FindSprite(Sprite* sprite);

	virtual void Release(void) override;
	virtual void Update(void) override;
	virtual void Render(void) override;
};