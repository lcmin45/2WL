#include "stdafx.h"
#include "우박.h"


우박::우박()
{
}


우박::~우박()
{
}

HRESULT 우박::init()
{
	return S_OK;
}

void 우박::release()
{
}

void 우박::update()
{
	if (_img)
	{
		move();
		frameCount();
		if (_pt.x > CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2 - 100) _img = NULL;
	}
}

void 우박::render()
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top,_frameIndex, _img->getFrameY());
		_img->frameRender(getMemDC(), _rc2.left, _rc2.top, _frameIndex, _img->getFrameY());
		_img->frameRender(getMemDC(), _rc3.left, _rc3.top, _frameIndex, _img->getFrameY());
		_img->frameRender(getMemDC(), _rc4.left, _rc4.top, _frameIndex, _img->getFrameY());

		for (viHail = vHail.begin(); viHail != vHail.end(); viHail++)
		{
			if (!(*viHail)->img) continue;
			else if((*viHail)->img == IMAGEMANAGER->findImage("우박")) (*viHail)->img->frameRender(getMemDC(), (*viHail)->pt.x - (*viHail)->img->getFrameWidth() / 2, (*viHail)->pt.y - (*viHail)->img->getFrameHeight() / 2, (*viHail)->frameIndex, RND->getInt(4));
			else(*viHail)->img->frameRender(getMemDC(), (*viHail)->rc.left, (*viHail)->rc.top, (*viHail)->frameIndex,0);
		}
	}
}



void 우박::fire(const char * skillName, int amount, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		SOUNDMANAGER->play("Blizzard");
		_subject = subject;
		sprintf_s(_str, "우박범위");
		_img = IMAGEMANAGER->findImage(_str);
		_amount = amount;
		_firePt;
		_pt;
		if (angle > PI / 2 || angle < PI2 - PI / 2) _angle = PI;
		else _angle = 0;
		_pt.x = CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2 + 100;
		_pt.y = CAMERAMANAGER->getCameraPoint().y - 64;
		_pt2.x = CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2 + 100;
		_pt2.y = CAMERAMANAGER->getCameraPoint().y + 64;
		_pt3.x = CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2 + 100;
		_pt3.y = CAMERAMANAGER->getCameraPoint().y - 193;
		_pt4.x = CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2 + 100;
		_pt4.y = CAMERAMANAGER->getCameraPoint().y + 193;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_rc2 = RectMakeCenter(_pt2.x, _pt2.y, _img->getFrameWidth(), _img->getFrameHeight());
		_rc3 = RectMakeCenter(_pt3.x, _pt3.y, _img->getFrameWidth(), _img->getFrameHeight());
		_rc4 = RectMakeCenter(_pt4.x, _pt4.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;
		_startTime = TIMEMANAGER->getWorldTime();
	}
}

void 우박::move()
{
	if (_frameIndex >= _img->getMaxFrameX())
	{
		_pt.x += 10;
		_pt2.x += 10;
		_pt3.x += 10;
		_pt4.x += 10;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_rc2 = RectMakeCenter(_pt2.x, _pt2.y, _img->getFrameWidth(), _img->getFrameHeight());
		_rc3 = RectMakeCenter(_pt3.x, _pt3.y, _img->getFrameWidth(), _img->getFrameHeight());
		_rc4 = RectMakeCenter(_pt4.x, _pt4.y, _img->getFrameWidth(), _img->getFrameHeight());
		createHail();
		moveHail();
	}
}

void 우박::frameCount()
{
	_frameIndex++;
	_img->setFrameX(_frameIndex);
	_img->setFrameY(0);
	if(_frameIndex > _img->getMaxFrameX()) _frameIndex = _img->getMaxFrameX();
}

void 우박::createHail()
{
	for (int i = 0; i < 3; i++)
	{
		collision* col = new collision;
		col->img = IMAGEMANAGER->findImage("우박");
		float angle = RND->getFloat(PI2);
		col->pt.x = _pt.x + cos(angle) * RND->getFloat(129 / 2);
		col->pt.y = _pt.y - sin(angle) * RND->getFloat(129 / 2) - 200;
		col->ptStart = col->pt;
		col->frameIndex = 0;
		vHail.push_back(col);

		collision* col2 = new collision;
		col2->img = IMAGEMANAGER->findImage("우박");
		float angle2 = RND->getFloat(PI2);
		col2->pt.x = _pt2.x + cos(angle2) * RND->getFloat(129 / 2);
		col2->pt.y = _pt2.y - sin(angle2) * RND->getFloat(129 / 2) - 200;
		col2->ptStart = col2->pt;
		col2->frameIndex = 0;
		vHail.push_back(col2);

		collision* col3 = new collision;
		col3->img = IMAGEMANAGER->findImage("우박");
		float angle3 = RND->getFloat(PI2);
		col3->pt.x = _pt3.x + cos(angle3) * RND->getFloat(129 / 2);
		col3->pt.y = _pt3.y - sin(angle3) * RND->getFloat(129 / 2) - 200;
		col3->ptStart = col3->pt;
		col3->frameIndex = 0;
		vHail.push_back(col3);

		collision* col4 = new collision;
		col4->img = IMAGEMANAGER->findImage("우박");
		float angle4 = RND->getFloat(PI2);
		col4->pt.x = _pt4.x + cos(angle4) * RND->getFloat(129 / 2);
		col4->pt.y = _pt4.y - sin(angle4) * RND->getFloat(129 / 2) - 200;
		col4->ptStart = col4->pt;
		col4->frameIndex = 0;
		vHail.push_back(col4);
	}
}

void 우박::moveHail()
{
	for (viHail = vHail.begin(); viHail != vHail.end(); viHail++)
	{
		float distance = getDistance((*viHail)->pt.x, (*viHail)->pt.y, (*viHail)->ptStart.x, (*viHail)->ptStart.y);
		(*viHail)->frameIndex++;
		if ((*viHail)->frameIndex > (*viHail)->img->getMaxFrameX()) (*viHail)->frameIndex = (*viHail)->img->getMaxFrameX();
		if (distance < 200)
		{
			(*viHail)->pt.x += 10;
			(*viHail)->pt.y += 20;
			(*viHail)->ptStart.x += 10;
		}
		else if ((*viHail)->img == IMAGEMANAGER->findImage("우박") && distance >= 200)
		{
			(*viHail)->pt.x += 10;
			(*viHail)->ptStart.x += 10;
			(*viHail)->frameIndex = 2;
			(*viHail)->img = NULL;
			(*viHail)->img = IMAGEMANAGER->findImage("얼음효과");
			(*viHail)->rc = RectMakeCenter((*viHail)->pt.x, (*viHail)->pt.y, (*viHail)->img->getFrameWidth(), (*viHail)->img->getFrameHeight());
		}

		else if ((*viHail)->img == IMAGEMANAGER->findImage("얼음효과") && (*viHail)->frameIndex >= (*viHail)->img->getMaxFrameX())
		{
			viHail = vHail.erase(viHail);
		}
	}
}

void 우박::collisionHail()
{
}
