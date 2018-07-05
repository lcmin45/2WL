#include "stdafx.h"
#include "사이클론부메랑.h"


사이클론부메랑::사이클론부메랑()
{
}


사이클론부메랑::~사이클론부메랑()
{
}


HRESULT 사이클론부메랑::init()
{
	return S_OK;
}

void 사이클론부메랑::release()
{
}

void 사이클론부메랑::update()
{
	if (_img)
	{
		move();
		frameCount();
	}

	POINT tempPt;
	tempPt.x =_firePt.x;
	tempPt.y = _firePt.y;
	if (PtInRect(&_rc, tempPt))
	{
		if (_img4) _img4 = NULL;
		else
		{
			count++;
			if (_img3&&count % 4 == 0)_img3 = NULL;
			else
			{
				if (_img2&&count % 8 == 0) _img2 = NULL;
				else
				{
					if (_img&&count % 12 == 0)_img = NULL;
				}
			}
		}
	}
}

void 사이클론부메랑::render()
{
	if (_img)
	{
		if (_img2)
		{
			_img2->setFrameY(1);
			_img2->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex2, _img->getFrameY());
		}
		if (_img3)
		{
			_img3->setFrameY(2);
			_img3->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex3, _img->getFrameY());
		}
		if (_img4)
		{
			_img4->setFrameY(3);
			_img4->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex4, _img->getFrameY());
		}
		_img->setFrameY(0);
		_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, _img->getFrameY());
	}
}


void 사이클론부메랑::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage("바람파티클");
		_img3 = IMAGEMANAGER->findImage("바람파티클");
		_img2 = IMAGEMANAGER->findImage("바람파티클");
		_img4 = IMAGEMANAGER->findImage("바람파티클");
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_angle = angle;
		_pt.x = _pt.x + cosf(_angle) * 100;
		_pt.y = _pt.y - sinf(_angle) * 100;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img2->getFrameWidth(), _img2->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;
	}
}

void 사이클론부메랑::move()
{
	if (_img)
	{
		if (turn)
		{
			_pt.x += cosf(getAngle(_pt.x,_pt.y, _firePt.x, _firePt.y))*_speed;
			_pt.y += -sinf(getAngle(_pt.x, _pt.y, _firePt.x, _firePt.y))*_speed;
			_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
			return;
		}

		_pt.x += cosf(_angle)*_speed;
		_pt.y += -sinf(_angle)*_speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		if (getDistance(_pt.x, _pt.y, _firePt.x, _firePt.y) > _range) turn = true;
	}

}

void 사이클론부메랑::frameCount()
{
	_frameIndex++;
	_frameIndex2++;
	_frameIndex3++;
	_frameIndex4++;

	if (_frameIndex	>4) _frameIndex = 0;
	if (_frameIndex2>3) _frameIndex2 = 0;
	if (_frameIndex3>5) _frameIndex3 = 0;
	if (_frameIndex4>4) _frameIndex4 = 0;
}
