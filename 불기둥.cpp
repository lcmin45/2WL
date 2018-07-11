#include "stdafx.h"
#include "�ұ��.h"


�ұ��::�ұ��()
{
}


�ұ��::~�ұ��()
{
}

HRESULT �ұ��::init()
{
	return S_OK;
}

void �ұ��::release()
{
}

void �ұ��::update()
{
	if (_img)
	{
		move();
		frameCount();
		if (TIMEMANAGER->getWorldTime() - _startTime > 4.0f) _img = NULL;
	}
}

void �ұ��::render()
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, 0);
	}
}

void �ұ��::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "�ұ��");
		_img = IMAGEMANAGER->findImage("�ұ��");
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

void �ұ��::move()
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

void �ұ��::frameCount()
{
	_frameIndex++;
}

