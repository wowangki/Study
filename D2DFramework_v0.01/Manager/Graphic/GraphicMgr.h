#pragma once
#include <list>

class Image;
class Sprite;
class Animator;
class Camera;
class GameObject;
class GraphicMgr
{
private:
	friend class WorldMgr;

private:
	list<Image*> lImage;
	list<Sprite*> lSprite;
	list<Animator*> lAnimator;
	list<Camera*> lCamera;

	typedef list<Image*>::iterator lIIter;
	typedef list<Sprite*>::iterator lSIter;
	typedef list<Animator*>::iterator lAIter;
	typedef list<Camera*>::iterator lCIter;

	Camera* currentCam;
private:
	void RegistImage(Image* img);
	void UnRegistImage(Image* img);

	void RegistSprite(Sprite* sprite);
	void UnRegistSprite(Sprite* sprite);

	void RegistAnimator(Animator* anim);
	void UnRegistAnimator(Animator* anim);

	void RegistCam(Camera* cam);
	void UnRegistCam(Camera* cam);
	void SetCurrentCam(GameObject* object);

	void TestRenderBox(D2D_RECT_F rc, string brushName);
	
public:
	GraphicMgr();
	~GraphicMgr();

	void Release(void);
	void Render(void);

	const Camera* GetCurrentCam(void) const { return currentCam; }
};

