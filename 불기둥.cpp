#include "stdafx.h"
#include "ºÒ±âµÕ.h"


ºÒ±âµÕ::ºÒ±âµÕ()
{
}


ºÒ±âµÕ::~ºÒ±âµÕ()
{
}

HRESULT ºÒ±âµÕ::init()
{
	return S_OK;
}

void ºÒ±âµÕ::release()
{
}

void ºÒ±âµÕ::update()
{
	if (_img)
	{
		move();
		frameCount();
		if (TIMEMANAGER->getWorldTime() - _startTime > 4.0f) _img = NULL;
	}
}

void ºÒ±âµÕ::render()
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, 0);
	}
}

void ºÒ±âµÕ::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "ºÒ±âµÕ");
		_img = IMAGEMANAGER->findImage("ºÒ±âµÕ");
		_amount = amount;
		_pt = pt;
		_firePt = pt;
		_angle = angle;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;
		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void ºÒ±âµÕ::move()
{
	if (_frameIndex > _img->getMaxFrameX())
	{
		_angle = getAngle(_pt.x, _pt.y, _player->getPosition().x, _player->getPosition().y);
		_pt.x += cosf(_angle) * _speed;
		_pt.y -= sinf(_angle) * _speed;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		if (_frameIndex > _img->getMaxFrameX()) _frameIndex = 0;
	}

}

void ºÒ±âµÕ::frameCount()
{
	_frameIndex++;
}

