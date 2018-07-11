#include "stdafx.h"
#include "얼음던지기.h"


얼음던지기::얼음던지기()
{
}


얼음던지기::~얼음던지기()
{
}

HRESULT 얼음던지기::init()
{
	return S_OK;
}

void 얼음던지기::release()
{
}

void 얼음던지기::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void 얼음던지기::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
}

void 얼음던지기::fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage(_str);
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_fireAngle = 0;
		_pt.x = _pt.x + cosf(_angle) * 50;
		_pt.y = _pt.y - sinf(_angle) * 50;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;

		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void 얼음던지기::move()
{
	if (_img)
	{
		if (TIMEMANAGER->getWorldTime() - _startTime >= 2.0f)
		{
			_pt.x += cosf(_angle)*_speed;
			_pt.y += -sinf(_angle)*_speed;
			_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		}
		else
		{
			_angle = getAngle(_pt.x, _pt.y, _player->getPosition().x, _player->getPosition().y);
			_pt.x = _firePt.x + cosf(_fireAngle) * 50;
			_pt.y = _firePt.y - sinf(_fireAngle) * 50;
			_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
			_fireAngle += PI2 / 32;
		}
	}
}

void 얼음던지기::frameCount()
{
	_count++;
	if (_count % 3 == 0)
	{
		_img->setFrameX(_frameIndex);
		_frameIndex++;
		_count = 0;
	}

	if (_frameIndex > _img->getMaxFrameX()) _frameIndex = _img->getMaxFrameX();
	if (_range < getDistance(_firePt.x, _firePt.y, _pt.x, _pt.y)) _img = NULL;
}
