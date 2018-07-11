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

	if (skillName == "불꽃타격")
	{
		불꽃타격* FirePunch = new 불꽃타격;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
	}
	if (skillName == "바람베기")
	{
		바람베기* WindCutter = new 바람베기;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
	}
	if (skillName == "흙주먹")
	{
		흙주먹* EarthPunch = new 흙주먹;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
	}

	if (skillName == "화염구")
	{
		화염구* FireBall = new 화염구;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 1, 30, PLAYER);
		vSkill.push_back(FireBall);
	}

	if (skillName == "불타는올가미")
	{
		불타는올가미* FireSword = new 불타는올가미;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
	}

	if (skillName == "맹렬회오리")
	{
		맹렬회오리* WindTornado = new 맹렬회오리;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
	}

	if (skillName == "사이클론부메랑")
	{
		사이클론부메랑* CyclronBoomerang = new 사이클론부메랑;
		CyclronBoomerang->fire(skillName, 1, _player->getPosition(), tempAngle, 15, 350, 1, 1.0f, PLAYER);
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
	if (!strcmp(skillName, "BlueKnightBullet") || !strcmp(skillName, "GreenKnightBullet") || !strcmp(skillName, "RedKnightBullet") || !strcmp(skillName, "GhoulBullet"))
	{
		몬스터근접* monsterAtt = new 몬스터근접;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 1, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (!strcmp(skillName, "BlueMageBullet") || !strcmp(skillName, "GreenMageBullet") || !strcmp(skillName, "RedMageBullet"))
	{
		몬스터총알* monsterBullet = new 몬스터총알;
		몬스터총알* monsterBullet2 = new 몬스터총알;
		몬스터총알* monsterBullet3 = new 몬스터총알;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI / 6, 8, 850, 1, 1.0f, ENEMY);
		monsterBullet2->fire(skillName, 1, pt, tempAngle, 8, 850, 1, 1.0f, ENEMY);
		monsterBullet3->fire(skillName, 1, pt, tempAngle + PI / 6, 8, 850, 1, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
	{
		몬스터총알* monsterBullet4 = new 몬스터총알;
		monsterBullet4->fire(skillName, 1, pt, tempAngle, 16, 850, 1, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet4);
	}
	if (!strcmp(skillName, "얼음던지기"))
	{
		얼음던지기매니저* IceM = new 얼음던지기매니저;
		IceM->fire(skillName, 1, pt, 20.0f, 850, 1, 1.0f, ENEMY);
		IceM->getPlayerAddressLink(_player);
		vSkill.push_back(IceM);
	}
	if (!strcmp(skillName, "우박"))
	{
		우박* hail = new 우박;
		hail->fire(skillName, 1, tempAngle, 16, 850, 1, 1.0f, ENEMY);
		vSkill.push_back(hail);
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
