#include "stdafx.h"
#include "����������Ŵ���.h"


����������Ŵ���::����������Ŵ���()
{
}


����������Ŵ���::~����������Ŵ���()
{
}

HRESULT ����������Ŵ���::init()
{
	return S_OK;
}

void ����������Ŵ���::release()
{
}

void ����������Ŵ���::update()
{
	if (_img)
	{
		if (TIMEMANAGER->getWorldTime() - _startTime <= 0.7f)
		{
			if (count % 3 == 0);
			{����������* IceThrow = new ����������;
			IceThrow->fire(_str, _amount, _pt, _speed, _range, _damage, _coolTime, _subject);
			IceThrow->getPlayerAddressLink(_player);
			vIceThrow.push_back(IceThrow);
			count = 0; }
		}
		if (vIceThrow.size() != 0)
		{
			for (viIceThrow = vIceThrow.begin(); viIceThrow != vIceThrow.end();)
			{
				if (!(*viIceThrow)->getImage())
				{
					viIceThrow = vIceThrow.erase(viIceThrow);
				}
				else
				{
					(*viIceThrow)->update();
					viIceThrow++;
				}
			}
		}
		else _img = NULL;
	}
}

void ����������Ŵ���::render()
{
	if (_img)
	{
		if (vIceThrow.size() != 0)
		{
			for (viIceThrow = vIceThrow.begin(); viIceThrow != vIceThrow.end(); viIceThrow++)
			{
				(*viIceThrow)->render();
			}
		}
	}
}

void ����������Ŵ���::fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		_subject = subject;
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage(_str);
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;

		_startTime = TIMEMANAGER->getWorldTime();
	}
}
