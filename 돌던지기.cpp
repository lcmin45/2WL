#include "stdafx.h"
#include "돌던지기.h"


돌던지기::돌던지기()
{
}


돌던지기::~돌던지기()
{
}

HRESULT 돌던지기::init()
{
	return S_OK;
}

void 돌던지기::release()
{
}

void 돌던지기::update()
{
	if (_img)
	{
		move();
		frameCount();

		if (getDistance(_pt.x, _pt.y, _firePt.x, _firePt.y) > _range) _img = NULL;
	}
}

void 돌던지기::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
}

void 돌던지기::fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		SOUNDMANAGER->play("ThrowBoulder");
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage("돌던지기");
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_fireAngle = 0;
		_pt.x = _pt.x + cosf(_angle) * 50;
		_pt.y = _pt.y - sinf(_angle) * 50 - 50;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;

		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void 돌던지기::move()
{
	if (TIMEMANAGER->getWorldTime() - _startTime > 1.0f)
	{
		_pt.x += cosf(_angle) * _speed;
		_pt.y -= sinf(_angle) * _speed;
	}
	else
	{
		_pt.y++;
		_angle = getAngle(_pt.x, _pt.y,_player->getPosition().x, _player->getPosition().y);
	}
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
}

void 돌던지기::frameCount()
{
	if (_img == IMAGEMANAGER->findImage("돌던지기2")) return;
	if (TIMEMANAGER->getWorldTime() - _startTime > 0.5f)
	{
		_img = IMAGEMANAGER->findImage("돌던지기2");
		SOUNDMANAGER->play("ThrowBoulder");
	}
}
