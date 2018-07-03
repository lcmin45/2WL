#include "stdafx.h"
#include "入林冈.h"


入林冈::入林冈()
{
}


入林冈::~入林冈()
{
}

HRESULT 入林冈::init()
{
	return S_OK;
}

void 入林冈::release()
{
}

void 入林冈::update()
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

void 入林冈::render()
{
	if (_img)_img->frameRender(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());
}

void 入林冈::move()
{
	if (_img)
	{
		_pt.x += cosf(_angle)*_speed;
		_pt.y += -sinf(_angle)*_speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}
}

void 入林冈::frameCount()
{
	int angle = _angle / (PI2 / 16);

	_img->setFrameX(angle);
}

void 入林冈::fireAtt()
{
	if (_img->getFrameY() == 0) _img->setFrameY(1);
	else _img->setFrameY(0);
}
