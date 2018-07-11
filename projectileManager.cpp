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

	if (skillName == "불꽃타격" && TIMEMANAGER->getWorldTime() - coolTime[0] > 0.2f)
	{
		불꽃타격* FirePunch = new 불꽃타격;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
		coolTime[0] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("FlameStrike");
	}
	if (skillName == "바람베기" && TIMEMANAGER->getWorldTime() - coolTime[1] > 0.1f)
	{
		바람베기* WindCutter = new 바람베기;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
		coolTime[1] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("WindSlash");
	}
	if (skillName == "흙주먹" && TIMEMANAGER->getWorldTime() - coolTime[2] > 0.3f)
	{
		흙주먹* EarthPunch = new 흙주먹;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
		coolTime[2] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("earthPunch");
	}

	if (skillName == "화염구" && TIMEMANAGER->getWorldTime() - coolTime[3] > 5.0f)
	{
		화염구* FireBall = new 화염구;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 1, 30, PLAYER);
		vSkill.push_back(FireBall);
		coolTime[3] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Fireball");
	}

	if (skillName == "불타는올가미" && TIMEMANAGER->getWorldTime() - coolTime[4] > 10.0f)
	{
		불타는올가미* FireSword = new 불타는올가미;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
		coolTime[4] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Blazing");
	}

	if (skillName == "맹렬회오리" && TIMEMANAGER->getWorldTime() - coolTime[5] > 5.0f)
	{
		맹렬회오리* WindTornado = new 맹렬회오리;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
		coolTime[5] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Tornado");
	}

	if (skillName == "사이클론부메랑" && TIMEMANAGER->getWorldTime() - coolTime[6] > 10.0f)
	{
		사이클론부메랑* CyclronBoomerang = new 사이클론부메랑;
		CyclronBoomerang->fire(skillName, 1, _player->getPosition(), tempAngle, 15, 350, 1, 1.0f, PLAYER);
		vSkill.push_back(CyclronBoomerang);
		coolTime[6] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Tornado");
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
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 2.5f, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (!strcmp(skillName, "BlueMageBullet") || !strcmp(skillName, "GreenMageBullet") || !strcmp(skillName, "RedMageBullet"))
	{
		몬스터총알* monsterBullet = new 몬스터총알;
		몬스터총알* monsterBullet2 = new 몬스터총알;
		몬스터총알* monsterBullet3 = new 몬스터총알;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI / 6, 8, 850, 20.0f, 1.0f, ENEMY);
		monsterBullet2->fire(skillName, 1, pt, tempAngle, 8, 850, 1, 20.0f, ENEMY);
		monsterBullet3->fire(skillName, 1, pt, tempAngle + PI / 6, 8, 850, 20.0f, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
	{
		몬스터총알* monsterBullet4 = new 몬스터총알;
		monsterBullet4->fire(skillName, 1, pt, tempAngle, 16, 850, 10.0f, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet4);
	}
	if (!strcmp(skillName, "얼음던지기"))
	{
		얼음던지기매니저* IceM = new 얼음던지기매니저;
		IceM->fire(skillName, 1, pt, 20.0f, 850, 1, 5.0f, ENEMY);
		IceM->getPlayerAddressLink(_player);
		vSkill.push_back(IceM);
	}
	if (!strcmp(skillName, "우박"))
	{
		우박* hail = new 우박;
		hail->fire(skillName, 1, tempAngle, 16, 850, 5.0F, 5.0f, ENEMY);
		vSkill.push_back(hail);
	}
	if (!strcmp(skillName, "돌던지기"))
	{
		돌던지기* stonThrow = new 돌던지기;
		stonThrow->fire(skillName, 1, pt, 16, 850, 30.0F, 5.0f, ENEMY);
		stonThrow->getPlayerAddressLink(_player);
		vSkill.push_back(stonThrow);
	}
	if (!strcmp(skillName, "나무솟기"))
	{
		나무솟기* woodUp = new 나무솟기;
		woodUp->fire(skillName, 1, pt, tempAngle, 20, 850, 0.5f, 1.0f, ENEMY);
		woodUp->getPlayerAddressLink(_player);
		vSkill.push_back(woodUp);
	}
	if (!strcmp(skillName, "메테오"))
	{
		메테오* meteor = new 메테오;
		meteor->fire(skillName, 1, tempAngle, 50, 850, 5.0f, 1.0f, ENEMY);
		vSkill.push_back(meteor);
	}
	if (!strcmp(skillName, "불기둥"))
	{
		불기둥* flamestrike = new 불기둥;
		flamestrike->fire(skillName, 1, pt, tempAngle, 50, 850, 1.0f, 1.0f, ENEMY);
		flamestrike->getPlayerAddressLink(_player);
		vSkill.push_back(flamestrike);
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
