#pragma once
class ButtonModule
{
	enum ButtonKeyDonw { UP, DOWN };
	
private:
	ImageModule* img;
	float x, y;
	int frameX;

	ButtonKeyDonw direction;

	string typeName;
	string clickTypeName;

private:
	bool IsInRect() {
		if (AppMouse.x > x && AppMouse.x < x + img->GetFrameWidth() &&
			AppMouse.y > y && AppMouse.y < y + img->GetFrameHeight()) {
			return true;
		}

		return false;
	}

public:
	ButtonModule();
	~ButtonModule();

	HRESULT CreateButton(string nickName, float x, float y, string typing, string clickTyping = "");
	bool IsClick(void);
	void Render(void);
	
public:
	D2D_RECT_F GetRect(void) {
		return MakeRect({ x, y }, { img->GetFrameWidth(), img->GetFrameHeight() });
	}
};

