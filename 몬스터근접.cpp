#include "stdafx.h"
#include "몬스터근접.h"


몬스터근접::몬스터근접()
{
}


몬스터근접::~몬스터근접()
{
}

HRESULT 몬스터근접::init()
{
	return S_OK;
}

void 몬스터근접::release()
{
}

void 몬스터근접::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void 몬스터근접::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
}

void 몬스터근접::move()
{
}

void 몬스터근접::frameCount()
{
	_count++;
	if (_count % 3 == 0)
	{
		int angle = _angle / (PI2 / 8);

		_img->setFrameY(angle);
		_img->setFrameX(_frameIndex);
		_frameIndex++;
		_count = 0;
	}

	if (_frameIndex > _img->getMaxFrameX()) _img = NULL;
}
