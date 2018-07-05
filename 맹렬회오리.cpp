#include "stdafx.h"
#include "맹렬회오리.h"


맹렬회오리::맹렬회오리()
{
}


맹렬회오리::~맹렬회오리()
{
}

HRESULT 맹렬회오리::init()
{
	return S_OK;
}

void 맹렬회오리::release()
{
}

void 맹렬회오리::update()
{
	if (TIMEMANAGER->getWorldTime() - _startTime >= 0.15f) _img2 = NULL;
	if (TIMEMANAGER->getWorldTime() - _startTime >= 0.2f) _img3 = NULL;
	if (TIMEMANAGER->getWorldTime() - _startTime >= 0.25f) _img4 = NULL;
	if (TIMEMANAGER->getWorldTime() - _startTime >= 0.3f) _img = NULL;
	frameCount();
}

void 맹렬회오리::render()
{
	
	if (_img)
	{
		if (_img2)
		{
			_img2->setFrameY(1);
			_img2->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex2, _img->getFrameY());
		}
		if (_img3)
		{
			_img3->setFrameY(2);
			_img3->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex3, _img->getFrameY());
		}
		if (_img4)
		{
			_img4->setFrameY(3);
			_img4->frameRender(getMemDC(), _rc.left, _rc.top - 10, _frameIndex4, _img->getFrameY());
		}
		_img->setFrameY(0);
		_img->frameRender(getMemDC(), _rc.left, _rc.top-20, _frameIndex, _img->getFrameY());
	}
}

void 맹렬회오리::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage("바람파티클");
		_img3 = IMAGEMANAGER->findImage("바람파티클");
		_img2 = IMAGEMANAGER->findImage("바람파티클");
		_img4 = IMAGEMANAGER->findImage("바람파티클");
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_angle = angle;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;
		_frameIndex = 0;
		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void 맹렬회오리::move()
{
}

void 맹렬회오리::frameCount()
{
	_frameIndex++;
	_frameIndex2++;
	_frameIndex3++;
	_frameIndex4++;

	if(_frameIndex	>4) _frameIndex	 = 0;
	if(_frameIndex2	>3) _frameIndex2 = 0;
	if(_frameIndex3	>5) _frameIndex3 = 0;
	if(_frameIndex4	>4) _frameIndex4 = 0;
}
