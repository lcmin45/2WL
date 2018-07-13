#include "stdafx.h"
#include "화염구.h"


화염구::화염구()
{
}


화염구::~화염구()
{
}

HRESULT 화염구::init()
{
	return S_OK;
}

void 화염구::release()
{
}

void 화염구::update()
{
	if (_img)
	{
		if (_img != IMAGEMANAGER->findImage("메테오효과"))
		{
			move();
			frameCount();
		}
		if (_img == IMAGEMANAGER->findImage("메테오효과")) _frameIndex++;
		else if (_range < getDistance(_firePt.x, _firePt.y, _pt.x, _pt.y) || (PtInRect(&_tile[(int)_pt.y / TILESIZE * MAXTILEX + (int)_pt.x / TILESIZE].rc, { (int)_pt.x,(int)_pt.y }) && _tile[(int)_pt.y / TILESIZE * MAXTILEX + (int)_pt.x / TILESIZE].terrain == TR_WALL))
		{
			_img = IMAGEMANAGER->findImage("메테오효과");
			_frameIndex = 0;
		}
		if (_img == IMAGEMANAGER->findImage("메테오효과") && _frameIndex > _img->getMaxFrameX())
		{
			_img = NULL;
		}
	}
}

void 화염구::render()
{
	if (_img)
	{
		if (_img == IMAGEMANAGER->findImage("화염구"))_img->frameRender(getMemDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());
		if (_img == IMAGEMANAGER->findImage("메테오효과"))_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, _img->getFrameY());
	}
}


void 화염구::move()
{
	if (_img)
	{
		_pt.x += cosf(_angle)*_speed;
		_pt.y += -sinf(_angle)*_speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}

}

void 화염구::frameCount()
{
	int angle = _angle / (PI2/16);
	
	_img->setFrameX(angle);
	_img->setFrameY(_frameIndex);
	_frameIndex++;
}
