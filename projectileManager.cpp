#include "stdafx.h"
#include "projectileManager.h"


projectileManager::projectileManager()
{
}


projectileManager::~projectileManager()
{
}

HRESULT projectileManager::init()
{


	return S_OK;
}

void projectileManager::release()
{
}

void projectileManager::update()
{
	vectorCheck();
}

void projectileManager::render()
{
	vectorDraw();
}

void projectileManager::fire(const char * skillName)
{
	float tempAngle = getAngle(_player->getPosition().x, _player->getPosition().y, getMousePoint().x, getMousePoint().y);

	if (skillName == "�Ҳ�Ÿ��")
	{
		�Ҳ�Ÿ��* FirePunch = new �Ҳ�Ÿ��;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
	}
	if (skillName == "�ٶ�����")
	{
		�ٶ�����* WindCutter = new �ٶ�����;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
	}
	if (skillName == "���ָ�")
	{
		���ָ�* EarthPunch = new ���ָ�;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
	}

	if (skillName == "ȭ����")
	{
		ȭ����* FireBall = new ȭ����;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 50, 30, PLAYER);
		vSkill.push_back(FireBall);
	}

	if (skillName == "��Ÿ�¿ð���")
	{
		��Ÿ�¿ð���* FireSword = new ��Ÿ�¿ð���;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
	}

	if (skillName == "�ͷ�ȸ����")
	{
		�ͷ�ȸ����* WindTornado = new �ͷ�ȸ����;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
	}

	if (skillName == "����Ŭ�кθ޶�")
	{
		����Ŭ�кθ޶�* CyclronBoomerang = new ����Ŭ�кθ޶�;
		CyclronBoomerang->fire(skillName, 1, _player->getPosition(), tempAngle, 15, 350, 50, 1.0f, PLAYER);
		vSkill.push_back(CyclronBoomerang);
	}
}

void projectileManager::fire(const char * skillName, POINTFLOAT pt)
{
	float tempAngle = 0;
	tempAngle = getAngle(
		pt.x, 
		pt.y, 
		_player->getPosition().x, 
		_player->getPosition().y);
	if (!strcmp(skillName, "BlueKnightBullet") || !strcmp(skillName, "GreenKnightBullet")|| !strcmp(skillName, "RedKnightBullet") || !strcmp(skillName, "GhoulBullet"))
	{
		���ͱ���* monsterAtt = new ���ͱ���;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (!strcmp(skillName, "BlueMageBullet") || !strcmp(skillName, "GreenMageBullet") || !strcmp(skillName, "RedMageBullet"))
	{
		�����Ѿ�* monsterBullet = new �����Ѿ�;
		�����Ѿ�* monsterBullet2 = new �����Ѿ�;
		�����Ѿ�* monsterBullet3 = new �����Ѿ�;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI/6, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet2->fire(skillName, 1, pt, tempAngle, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet3->fire(skillName, 1, pt, tempAngle + PI/6, 8, 850, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
	{
		�����Ѿ�* monsterBullet4 = new �����Ѿ�;
		monsterBullet4->fire(skillName, 1, pt, tempAngle, 8, 850, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet4);
	}
}

void projectileManager::vectorCheck()
{
	if (vSkill.size() != 0)
	{
		for (viSkill = vSkill.begin(); viSkill != vSkill.end();)
		{
			if (!(*viSkill)->getImage())
			{
				viSkill = vSkill.erase(viSkill);
			}
			else
			{
				(*viSkill)->update();
				viSkill++;
			}
		}
	}
}

void projectileManager::vectorDraw()
{
	if (vSkill.size() != 0)
	{
		for (viSkill = vSkill.begin(); viSkill != vSkill.end(); viSkill++)
		{
			(*viSkill)->render();
		}
	}
}
