#include "stdafx.h"
#include "¸ó½ºÅÍÃÑ¾Ë.h"


¸ó½ºÅÍÃÑ¾Ë::¸ó½ºÅÍÃÑ¾Ë()
{
}


¸ó½ºÅÍÃÑ¾Ë::~¸ó½ºÅÍÃÑ¾Ë()
{
}

HRESULT ¸ó½ºÅÍÃÑ¾Ë::init()
{
	return S_OK;
}

void ¸ó½ºÅÍÃÑ¾Ë::release()
{
}

void ¸ó½ºÅÍÃÑ¾Ë::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void ¸ó½ºÅÍÃÑ¾Ë::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());
}

void ¸ó½ºÅÍÃÑ¾Ë::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage(_str);
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_angle = angle;
		_pt.x = _pt.x + cosf(_angle) * 50;
		_pt.y = _pt.y - sinf(_angle) * 50;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;

		_startTime = TIMEMANAGER->getWorldTime();
		if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
			_startTime = 1;
	}
}

void ¸ó½ºÅÍÃÑ¾Ë::move()
{
	if (_img)
	{
		if (TIMEMANAGER->getWorldTime() - _startTime >= 1.0f)
		{
			_pt.x += cosf(_angle)*_speed;
			_pt.y += -sinf(_angle)*_speed;
			_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		}
	}
}

void ¸ó½ºÅÍÃÑ¾Ë::frameCount()
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

	if (_frameIndex > _img->getMaxFrameX()) _frameIndex = 0;
	if (_range < getDistance(_firePt.x, _firePt.y, _pt.x, _pt.y)) _img = NULL;

}
