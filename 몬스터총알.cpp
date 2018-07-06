#include "stdafx.h"
#include "�����Ѿ�.h"


�����Ѿ�::�����Ѿ�()
{
}


�����Ѿ�::~�����Ѿ�()
{
}

HRESULT �����Ѿ�::init()
{
	return S_OK;
}

void �����Ѿ�::release()
{
}

void �����Ѿ�::update()
{
	move();
}

void �����Ѿ�::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top, _img->getFrameX(), _img->getFrameY());
}

void �����Ѿ�::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
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
		_pt.x = _pt.x + cosf(_angle) * 100;
		_pt.y = _pt.y - sinf(_angle) * 100;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;

		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void �����Ѿ�::move()
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

void �����Ѿ�::frameCount()
{
}
