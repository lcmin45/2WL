#include "stdafx.h"
#include "ȭ����.h"


ȭ����::ȭ����()
{
}


ȭ����::~ȭ����()
{
}

HRESULT ȭ����::init()
{
	return S_OK;
}

void ȭ����::release()
{
}

void ȭ����::update()
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

void ȭ����::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top,_img->getFrameX(),_img->getFrameY());
}


void ȭ����::move()
{
	if (_img)
	{
		_pt.x += cosf(_angle)*_speed;
		_pt.y += -sinf(_angle)*_speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}

}

void ȭ����::frameCount()
{
	int angle = _angle / (PI2/16);
	
	_img->setFrameX(angle);
	_img->setFrameY(_frameIndex);
	_frameIndex++;
}
