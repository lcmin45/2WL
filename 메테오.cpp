#include "stdafx.h"
#include "메테오.h"


메테오::메테오()
{
}


메테오::~메테오()
{
}

HRESULT 메테오::init()
{
	return S_OK;
}

void 메테오::release()
{
}

void 메테오::update()
{
	if (_img)
	{
		if (TIMEMANAGER->getWorldTime() - _startTime < 0.3f && TIMEMANAGER->getWorldTime() - _playTime < 3.0f)
		{
			createMeteor();
			_startTime = TIMEMANAGER->getWorldTime();
		}
		moveMeteor();
	}
}

void 메테오::render()
{
	for (viMeteor = vMeteor.begin(); viMeteor != vMeteor.end(); viMeteor++)
	{
		if ((*viMeteor)->img) (*viMeteor)->img->frameRender(getMemDC(), (*viMeteor)->rc.left, (*viMeteor)->rc.top, (*viMeteor)->frameIndex, 0);
		if ((*viMeteor)->img2) (*viMeteor)->img2->frameRender(getMemDC(), (*viMeteor)->rc2.left, (*viMeteor)->rc2.top, (*viMeteor)->frameIndex2, 0);
	}
}

void 메테오::fire(const char * skillName, int amount, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "메테오");
		_img = IMAGEMANAGER->findImage("메테오");
		_amount = amount;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;
		_startTime = TIMEMANAGER->getWorldTime();
		_playTime = TIMEMANAGER->getWorldTime();
	}
}

void 메테오::createMeteor()
{
	for (int i = 0; i < RND->getInt(2); i++)
	{
		METEOR* Meteor = new METEOR;
		Meteor->img2 = _img;
		Meteor->img = IMAGEMANAGER->findImage("우박범위");
		Meteor->pt.x = RND->getFloat(1088) + 80;
		Meteor->pt.y = RND->getFloat(736) + 3895;
		Meteor->rc = RectMakeCenter(Meteor->pt.x, Meteor->pt.y, Meteor->img->getFrameWidth(), Meteor->img->getFrameHeight());
		Meteor->pt2.x = Meteor->pt.x + cosf(PI / 4) * 1600;
		Meteor->pt2.y = Meteor->pt.y - sinf(PI / 4) * 1600;
		Meteor->rc2 = RectMakeCenter(Meteor->pt2.x, Meteor->pt2.y, Meteor->img2->getFrameWidth(), Meteor->img2->getFrameHeight());
		Meteor->frameIndex = Meteor->frameIndex2 = 0;
		Meteor->startTime = TIMEMANAGER->getWorldTime();
		vMeteor.push_back(Meteor);
	}
}

void 메테오::moveMeteor()
{
	RECT temp;
	for (viMeteor = vMeteor.begin(); viMeteor != vMeteor.end(); ++viMeteor)
	{
		if ((*viMeteor)->img2 == _img)
		{
			if (TIMEMANAGER->getWorldTime() - (*viMeteor)->startTime > 1.0f)
			{
				(*viMeteor)->pt2.x += cosf(PI + PI / 4) * 30;
				(*viMeteor)->pt2.y -= sinf(PI + PI / 4) * 30;
			}
			(*viMeteor)->rc2 = RectMakeCenter((*viMeteor)->pt2.x, (*viMeteor)->pt2.y, (*viMeteor)->img2->getFrameWidth(), (*viMeteor)->img2->getFrameHeight());
			(*viMeteor)->frameIndex++;
			(*viMeteor)->frameIndex2++;
			if ((*viMeteor)->frameIndex2 > (*viMeteor)->img2->getMaxFrameX()) (*viMeteor)->frameIndex2 = 0;
			if ((*viMeteor)->frameIndex > (*viMeteor)->img->getMaxFrameX()) (*viMeteor)->frameIndex = (*viMeteor)->img->getMaxFrameX();
		}
		if (PtInRect(&(*viMeteor)->rc, { (long)(*viMeteor)->pt2.x,(long)(*viMeteor)->pt2.y }) && (*viMeteor)->img != IMAGEMANAGER->findImage("메테오효과"))
		{
			if ((*viMeteor)->frameIndex != 0) (*viMeteor)->frameIndex = 0;
			(*viMeteor)->img = IMAGEMANAGER->findImage("메테오효과");
			(*viMeteor)->img2 = NULL;
		}

		if ((*viMeteor)->img == IMAGEMANAGER->findImage("메테오효과"))
		{
			(*viMeteor)->frameIndex++;
		}
	}
	for (viMeteor = vMeteor.begin(); viMeteor != vMeteor.end();)
	{
		if ((*viMeteor)->frameIndex > (*viMeteor)->img->getMaxFrameX()) viMeteor = vMeteor.erase(viMeteor);
		else ++viMeteor;
	}
}
