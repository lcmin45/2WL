#include "stdafx.h"
#include "�ٶ�����.h"


�ٶ�����::�ٶ�����()
{
}


�ٶ�����::~�ٶ�����()
{
}

HRESULT �ٶ�����::init()
{
	return S_OK;
}

void �ٶ�����::release()
{
}

void �ٶ�����::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void �ٶ�����::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
	if (KEYMANAGER->isToggleKey(VK_TAB)) Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
}

void �ٶ�����::move()
{
}

void �ٶ�����::frameCount()
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
