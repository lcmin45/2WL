#include "stdafx.h"
#include "��������.h"


��������::��������()
{
}


��������::~��������()
{
}

HRESULT ��������::init()
{
	return S_OK;
}

void ��������::release()
{
}

void ��������::update()
{
	if (_img)
	{
		move();
		frameCount();

		if (getDistance(_pt.x, _pt.y, _firePt.x, _firePt.y) > _range) _img = NULL;
	}
}

void ��������::render()
{
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top);
}

void ��������::fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		SOUNDMANAGER->play("ThrowBoulder");
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage("��������");
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

void ��������::move()
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

void ��������::frameCount()
{
	if (_img == IMAGEMANAGER->findImage("��������2")) return;
	if (TIMEMANAGER->getWorldTime() - _startTime > 0.5f)
	{
		_img = IMAGEMANAGER->findImage("��������2");
		SOUNDMANAGER->play("ThrowBoulder");
	}
}
