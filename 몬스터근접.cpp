#include "stdafx.h"
#include "���ͱ���.h"


���ͱ���::���ͱ���()
{
}


���ͱ���::~���ͱ���()
{
}

HRESULT ���ͱ���::init()
{
	return S_OK;
}

void ���ͱ���::release()
{
}

void ���ͱ���::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void ���ͱ���::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
}

void ���ͱ���::move()
{
}

void ���ͱ���::frameCount()
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
