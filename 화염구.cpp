#include "stdafx.h"
#include "È­¿°±¸.h"


È­¿°±¸::È­¿°±¸()
{
}


È­¿°±¸::~È­¿°±¸()
{
}

HRESULT È­¿°±¸::init()
{
	return S_OK;
}

void È­¿°±¸::release()
{
}

void È­¿°±¸::update()
{
	if (_img)
	{
		move();
		frameCount();
	}

	if (_range < getDistance(_firePt.x, _firePt.y, _pt.x, _pt.y))
	{
		_img = NULL;
	}
}

void È­¿°±¸::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top,_img->getFrameX(),_img->getFrameY());
}


void È­¿°±¸::move()
{
	if (_img)
	{
		_pt.x += cosf(_angle)*_speed;
		_pt.y += -sinf(_angle)*_speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}

}

void È­¿°±¸::frameCount()
{
	int angle = _angle / (PI2/16);
	
	_img->setFrameX(angle);
	_img->setFrameY(_frameIndex);
	_frameIndex++;
}
