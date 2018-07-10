#include "stdafx.h"
#include "ºÒ²ÉÅ¸°Ý.h"


ºÒ²ÉÅ¸°Ý::ºÒ²ÉÅ¸°Ý()
{
}


ºÒ²ÉÅ¸°Ý::~ºÒ²ÉÅ¸°Ý()
{
}

HRESULT ºÒ²ÉÅ¸°Ý::init()
{
	return S_OK;
}

void ºÒ²ÉÅ¸°Ý::release()
{
}

void ºÒ²ÉÅ¸°Ý::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void ºÒ²ÉÅ¸°Ý::render()
{
	for (viParticle = vParticle.begin(); viParticle != vParticle.end(); viParticle++)
	{
		viParticle->img->frameRender(getMemDC(), viParticle->rc.left, viParticle->rc.top, viParticle->indexX, viParticle->indexY);
	}
	if (_img)_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, _img->getFrameY());
}

void ºÒ²ÉÅ¸°Ý::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
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


		PARTICLE particle;
		ZeroMemory(&particle, sizeof(PARTICLE));
		particle.img = IMAGEMANAGER->findImage("ºÒ²ÉÆÄÆ¼Å¬");

		for (int i = 0; i < 20; i++)
		{
			particle.startTime = TIMEMANAGER->getWorldTime();
			particle.angle = RND->getFloat(PI2);
			particle.indexX = RND->getInt(3);
			particle.indexY = RND->getInt(4);
			particle.pt.x = _rc.left + (_rc.right - _rc.left) / 2 + RND->getInt(40) - 10;
			particle.pt.y = _rc.top + (_rc.bottom - _rc.top) / 2 + RND->getInt(40) - 10;
			particle.rc = RectMakeCenter(particle.pt.x, particle.pt.y, particle.img->getFrameWidth(), particle.img->getFrameHeight());
			vParticle.push_back(particle);
		}
	}
}
void ºÒ²ÉÅ¸°Ý::move()
{

	_pt.x += cosf(_angle) * 3;
	_pt.y += -sinf(_angle) * 3;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());

	if (vParticle.size() != 0)
	{
		for (viParticle = vParticle.begin(); viParticle != vParticle.end(); viParticle++)
		{
			viParticle->pt.x += cosf(viParticle->angle) * 2 + cosf(_angle) * 3;
			viParticle->pt.y += -sinf(viParticle->angle) * 2 + -sinf(_angle) * 3;
			viParticle->rc = RectMakeCenter(viParticle->pt.x, viParticle->pt.y, viParticle->img->getFrameWidth(), viParticle->img->getFrameHeight());
		}
	}
}

void ºÒ²ÉÅ¸°Ý::frameCount()
{
	if (_angle <= PI / 4 || _angle > PI2 - PI / 4) _img->setFrameY(0);
	if (_angle > PI / 4 && _angle <= PI - PI / 4)_img->setFrameY(1);
	if (_angle > PI - PI / 4 && _angle <= PI + PI / 4) _img->setFrameY(2);
	if (_angle > PI + PI / 4 && _angle <= PI2 - PI / 4)_img->setFrameY(3);

	if (TIMEMANAGER->getWorldTime() - _startTime >= 0.08f)
	{
		_frameIndex++;
		_startTime = TIMEMANAGER->getWorldTime();
	}

	if (vParticle.size() != 0)
	{
		for (viParticle = vParticle.begin(); viParticle != vParticle.end();)
		{
			if (TIMEMANAGER->getWorldTime() - viParticle->startTime > 0.2f) viParticle->indexX++;
			if (viParticle->indexX > viParticle->img->getMaxFrameX()) viParticle->indexX = viParticle->img->getMaxFrameX();
			//if (getAngle(_pt.x,_pt.y, viParticle->pt.x, viParticle->pt.y))

			if (getDistance(viParticle->pt.x, viParticle->pt.y, _pt.x, _pt.y) > 50)
			{
				viParticle = vParticle.erase(viParticle);

			}
			else viParticle++;
		}
	}

	if (_frameIndex > _img->getMaxFrameY()) _img = NULL;
}



