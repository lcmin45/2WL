#include "stdafx.h"
#include "바람베기.h"


바람베기::바람베기()
{
}


바람베기::~바람베기()
{
}

HRESULT 바람베기::init()
{
	return S_OK;
}

void 바람베기::release()
{
}

void 바람베기::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void 바람베기::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void 바람베기::move()
{
}

void 바람베기::frameCount()
{
	_count++;
	if (_count % 3 == 0)
	{
		int angle = _angle / (PI2 / 16);

		_img->setFrameY(angle);
		_img->setFrameX(_frameIndex);
		_frameIndex++;
		_count = 0;
	}

	if (_frameIndex > _img->getMaxFrameX()) _img = NULL;
}
