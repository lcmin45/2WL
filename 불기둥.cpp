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
		fireVector();
		move();
		frameCount();
		if (getDistance(_firePt.x, _firePt.y, _pt.x, _pt.y) > _range)
		{
			_pt = _firePt;
			_angle = getAngle(_pt.x, _pt.y, _player->getPosition().x, _player->getPosition().y);
			_fireCount++;
		}
		if (_fireCount > 4) _img = NULL;
	}
}

void �ұ��::render()
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, 0);
		for (viflamestrike = vflamestrike.begin(); viflamestrike != vflamestrike.end(); ++viflamestrike)
		{
			if((*viflamestrike)->img)(*viflamestrike)->img->frameRender(getMemDC(), (*viflamestrike)->rc.left, (*viflamestrike)->rc.top, (*viflamestrike)->frameIndex, 0);
		}
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
	_pt.x += cosf(_angle) * _speed;
	_pt.y -= sinf(_angle) * _speed;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());

	FIRE* flamestrike = new FIRE;
	flamestrike->pt = _pt;
	flamestrike->rc = _rc;
	flamestrike->img = _img;
	flamestrike->frameIndex = 0;
	vflamestrike.push_back(flamestrike);
}

void �ұ��::frameCount()
{
	_frameIndex++;
	if (_frameIndex > _img->getMaxFrameX()) _frameIndex = _img->getMaxFrameX();
}

void �ұ��::fireVector()
{
	for (viflamestrike = vflamestrike.begin(); viflamestrike != vflamestrike.end();)
	{
		(*viflamestrike)->frameIndex++;
		if ((*viflamestrike)->frameIndex > 9)
		{
			(*viflamestrike)->img = NULL;
			viflamestrike = vflamestrike.erase(viflamestrike);
		}
		else ++viflamestrike;
	}
}
