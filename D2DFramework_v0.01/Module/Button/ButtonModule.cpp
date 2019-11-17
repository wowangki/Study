#include "stdafx.h"
#include "ButtonModule.h"


ButtonModule::ButtonModule()
	:img(nullptr),
	direction(UP),
	frameX(0)
{
}


ButtonModule::~ButtonModule()
{
}

HRESULT ButtonModule::CreateButton(string nickName, float x, float y, string typing, string clickTyping)
{
	img = _IMAGE->FindImage(nickName);
	if (img == nullptr) return E_FAIL;

	typeName = typing;
	if (clickTyping == "") clickTypeName = typeName;

	this->x = x;
	this->y = y;

	return S_OK;
}

bool ButtonModule::IsClick(void)
{
	if (!IsInRect()) { direction = UP; return false; }
	if (_KEYCODE->StayKeyDown(VK_LBUTTON)) direction = DOWN;
	if (_KEYCODE->IsKeyUp(VK_LBUTTON) && direction == DOWN) {
		direction = UP;
		return true;
	}

	return false;
}

void ButtonModule::Render(void)
{
	img->FrameRender(x, y, frameX, (int)direction);

	if (direction == DOWN) _FONT->Render(clickTypeName, GetRect());
	else _FONT->Render(typeName, GetRect());
}
