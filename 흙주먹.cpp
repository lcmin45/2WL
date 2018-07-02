#include "stdafx.h"
#include "���ָ�.h"


���ָ�::���ָ�()
{
}


���ָ�::~���ָ�()
{
}

HRESULT ���ָ�::init()
{
	return S_OK;
}

void ���ָ�::release()
{
}

void ���ָ�::update()
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

void ���ָ�::render()
{
	if (_img)_img->frameRender(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());
}

void ���ָ�::move()
{
	if (_img)
	{
		_pt.x += cosf(_angle)*_speed;
		_pt.y += -sinf(_angle)*_speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}
}

void ���ָ�::frameCount()
{
	int angle = _angle / (PI2 / 16);

	_img->setFrameX(angle);
}

void ���ָ�::fireAtt()
{
	if (_img->getFrameY() == 0) _img->setFrameY(1);
	else _img->setFrameY(0);
}
