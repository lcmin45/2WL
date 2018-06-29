#include "stdafx.h"
#include "UI.h"

UI::UI() {}
UI::~UI() {}

HRESULT UI::init()
{
	_image = IMAGEMANAGER->addImage("mouse", "image/UI/mouse.bmp", 50, 50, true, RGB(255, 0, 255));

	return S_OK;
}

void UI::release() {}

void UI::update() {}

void UI::render()
{
	_image->render(CAMERAMANAGER->getCameraDC(), _ptMouse.x - _image->getWidth() / 2, _ptMouse.y - _image->getHeight() / 2);
}