#include "stdafx.h"
#include "³ª¹«¼Ú±â.h"


³ª¹«¼Ú±â::³ª¹«¼Ú±â()
{
}


³ª¹«¼Ú±â::~³ª¹«¼Ú±â()
{
}

HRESULT ³ª¹«¼Ú±â::init()
{
	return S_OK;
}

void ³ª¹«¼Ú±â::release()
{
}

void ³ª¹«¼Ú±â::update()
{
	if (_img)
	{
		woodVector();
		move();
		frameCount();
		if (getDistance(_firePt.x, _firePt.y,_pt.x, _pt.y) > _range)
		{
			_pt = _firePt;
			_angle = getAngle(_pt.x, _pt.y, _player->getPosition().x, _player->getPosition().y);
			_fireCount++;
		}
		if (_fireCount > 5) _img = NULL;
	}
}

void ³ª¹«¼Ú±â::render()
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top, _frameIndex, 0);
		for (viWood = vWood.begin(); viWood != vWood.end(); ++viWood)
		{
			(*viWood)->img->frameRender(getMemDC(), (*viWood)->rc.left, (*viWood)->rc.top, (*viWood)->frameIndex, 0);
		}
	}
}

void ³ª¹«¼Ú±â::fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "³ª¹«¼Ú±â");
		_img = IMAGEMANAGER->findImage(_str);
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

void ³ª¹«¼Ú±â::move()
{
	_pt.x += cosf(_angle) * _speed;
	_pt.y -= sinf(_angle) * _speed;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	
	WOODPARTICLE* wood = new WOODPARTICLE;
	wood->pt = _pt;
	wood->rc = _rc;
	wood->img = _img;
	wood->frameIndex = 0;
	vWood.push_back(wood);
}

void ³ª¹«¼Ú±â::frameCount()
{
	_frameIndex++;
	if (_frameIndex > _img->getMaxFrameX()) _frameIndex = _img->getMaxFrameX();
}

void ³ª¹«¼Ú±â::woodVector()
{
	for (viWood = vWood.begin(); viWood != vWood.end(); ++viWood)
	{
		(*viWood)->frameIndex++;
		if ((*viWood)->frameIndex > 4) (*viWood)->frameIndex = 5;
	}
}