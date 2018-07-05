#include "stdafx.h"
#include "불타는올가미.h"


불타는올가미::불타는올가미() 
{
}


불타는올가미::~불타는올가미()
{
}

HRESULT 불타는올가미::init()
{
	count2 = 0;
	return S_OK;
}

void 불타는올가미::release(){}

void 불타는올가미::update()
{
	if (_img)
	{		
		move();
		//frameCount();
		
	}

	if (vParticle.size() != 0)
	{
		for (viParticle = vParticle.begin(); viParticle != vParticle.end();)
		{
			viParticle->img->setFrameX(viParticle->index);
			viParticle->index++;

			if (viParticle->index > viParticle->img->getMaxFrameX())
			{
				viParticle = vParticle.erase(viParticle);

			}
			else viParticle++;
		}
	}
	else
	{
	
		for (int i = 0; i < MAXPARTICLE; i++)
		{
			pImg[i] = NULL;
			_img = NULL;
		}
	}

}

void 불타는올가미::render()
{
	if (_img)
	{
		_img->frameRender(getMemDC(), _rc.left, _rc.top);		
		for (int i = 0; i < MAXPARTICLE; i++)
		{
			pImg[i]->frameRender(getMemDC(), sRect[i].left, sRect[i].top);
		}

		for (viParticle = vParticle.begin(); viParticle != vParticle.end(); viParticle++)
		{
			viParticle->img->frameRender(getMemDC(), viParticle->rc.left, viParticle->rc.top, viParticle->index, 0);
		}
	}
}

void 불타는올가미::fire(const char * skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject)
{
	if (!_img)
	{
		sprintf_s(_str, "%s", skillName);
		_img = IMAGEMANAGER->findImage("불꽃파티클");
		_amount = amount;
		_firePt = pt;
		_pt = pt;
		_angle = PI + PI2 / 32;
		_pt.x = _firePt.x + cosf(_angle) * 50;
		_pt.y = _firePt.y - sinf(_angle) * 50;

		_rc = RectMakeCenter(_firePt.x, _firePt.y, _img->getFrameWidth(), _img->getFrameHeight());
		_speed = speed;
		_range = range;
		_damage = damage;
		_coolTime = coolTime;
		_frameIndex = 0;

		string str[MAXPARTICLE];

		for (int i = 0; i < MAXPARTICLE; i++)
		{
			pImg[i] = IMAGEMANAGER->findImage("불꽃파티클");
			sword[i].x = _firePt.x + cosf(_angle) * (50 + (i + 1) * 30);
			sword[i].y = _firePt.y - sinf(_angle) * (50 + (i + 1) * 30);
			sRect[i] = RectMakeCenter(sword[i].x, sword[i].y, pImg[i]->getFrameWidth(), pImg[i]->getFrameHeight());
			swordIndex[i] = (i % 2 == 0 ? 0 : 1);
			pImg[i]->setFrameX(swordIndex[i]);
		}
		count = 0;
		spin = 0;
	}
}



void 불타는올가미::move()
{
	if (_angle > (PI2*2 + PI + PI / 6))
	{
		for (int i = 0; i < MAXPARTICLE; i++)
		{
			swordIndex[i]++;
			pImg[i]->setFrameX(swordIndex[i]);
		}
		_frameIndex++;
		_img->setFrameX(_frameIndex);
		_pt.x -= cosf(_angle) * 2;
		_pt.y -= sinf(_angle) * 2;
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());


		for (int i = 0; i < MAXPARTICLE; i++)
		{
			sword[i].x -= cosf(_angle) * 2;
			sword[i].y -= sinf(_angle) * 2;
			sRect[i] = RectMakeCenter(sword[i].x, sword[i].y, pImg[i]->getFrameWidth(), pImg[i]->getFrameHeight());
		}
		return;
	}
	else _angle += PI2 / 16;

	_pt.x = _firePt.x + cosf(_angle) * 50;
	_pt.y = _firePt.y - sinf(_angle) * 50;
	_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());


	for (int i = 0; i < MAXPARTICLE; i++)
	{
		sword[i].x = _firePt.x + cosf(_angle) * (50 + (i + 1) * 30);
		sword[i].y = _firePt.y - sinf(_angle) * (50 + (i + 1) * 30);
		sRect[i] = RectMakeCenter(sword[i].x, sword[i].y, pImg[i]->getFrameWidth(), pImg[i]->getFrameHeight());
	}

	_img->setFrameX(_frameIndex);
	
	PARTICLE particle;
	ZeroMemory(&particle, sizeof(PARTICLE));
	particle.img = IMAGEMANAGER->findImage("불꽃파티클");
	
	particle.pt = sword[MAXPARTICLE - 1];
	particle.rc = RectMakeCenter(particle.pt.x, particle.pt.y, particle.img->getFrameWidth(), particle.img->getFrameHeight());
	vParticle.push_back(particle);			
}