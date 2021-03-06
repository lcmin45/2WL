#include "stdafx.h"
#include "skill.h"

skill::skill() {}
skill::~skill() {}

HRESULT skill::init()
{
	return S_OK;
}

void skill::release() {}

void skill::update()
{
	
}

void skill::render()
{
	
}

void skill::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime,SUBJECT subject)
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
	}
}

void skill::move()
{
}

void skill::frameCount()
{
}
