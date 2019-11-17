#pragma once

// Abstract Class
class GameObject;
class Component {
protected:
	GameObject* myObject;

public:
	virtual void Init(void) = 0;
	virtual void Release(void) = 0;
	virtual void Update(void) = 0;
	virtual void Render(void) = 0;

	inline GameObject* GetMyObject(void) { return myObject; }
	void SetMyObject(GameObject* myObject) { this->myObject = myObject; }

};