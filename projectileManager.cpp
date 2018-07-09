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

	if (skillName == "ºÒ²ÉÅ¸°İ")
	{
		ºÒ²ÉÅ¸°İ* FirePunch = new ºÒ²ÉÅ¸°İ;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
	}
	if (skillName == "¹Ù¶÷º£±â")
	{
		¹Ù¶÷º£±â* WindCutter = new ¹Ù¶÷º£±â;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
	}
	if (skillName == "ÈëÁÖ¸Ô")
	{
		ÈëÁÖ¸Ô* EarthPunch = new ÈëÁÖ¸Ô;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
	}

	if (skillName == "È­¿°±¸")
	{
		È­¿°±¸* FireBall = new È­¿°±¸;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 50, 30, PLAYER);
		vSkill.push_back(FireBall);
	}

	if (skillName == "ºÒÅ¸´Â¿Ã°¡¹Ì")
	{
		ºÒÅ¸´Â¿Ã°¡¹Ì* FireSword = new ºÒÅ¸´Â¿Ã°¡¹Ì;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
	}

	if (skillName == "¸Í·ÄÈ¸¿À¸®")
	{
		¸Í·ÄÈ¸¿À¸®* WindTornado = new ¸Í·ÄÈ¸¿À¸®;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
	}

	if (skillName == "»çÀÌÅ¬·ĞºÎ¸Ş¶û")
	{
		»çÀÌÅ¬·ĞºÎ¸Ş¶û* CyclronBoomerang = new »çÀÌÅ¬·ĞºÎ¸Ş¶û;
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
		¸ó½ºÅÍ±ÙÁ¢* monsterAtt = new ¸ó½ºÅÍ±ÙÁ¢;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (!strcmp(skillName, "BlueMageBullet") || !strcmp(skillName, "GreenMageBullet") || !strcmp(skillName, "RedMageBullet"))
	{
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet = new ¸ó½ºÅÍÃÑ¾Ë;
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet2 = new ¸ó½ºÅÍÃÑ¾Ë;
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet3 = new ¸ó½ºÅÍÃÑ¾Ë;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI/6, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet2->fire(skillName, 1, pt, tempAngle, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet3->fire(skillName, 1, pt, tempAngle + PI/6, 8, 850, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
	{
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet4 = new ¸ó½ºÅÍÃÑ¾Ë;
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
