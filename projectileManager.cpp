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

	if (skillName == "ºÒ²ÉÅ¸°İ" && TIMEMANAGER->getWorldTime() - coolTime[0] > 0.2f)
	{
		ºÒ²ÉÅ¸°İ* FirePunch = new ºÒ²ÉÅ¸°İ;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
		coolTime[0] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("FlameStrike");
	}
	if (skillName == "¹Ù¶÷º£±â" && TIMEMANAGER->getWorldTime() - coolTime[1] > 0.1f)
	{
		¹Ù¶÷º£±â* WindCutter = new ¹Ù¶÷º£±â;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
		coolTime[1] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("WindSlash");
	}
	if (skillName == "ÈëÁÖ¸Ô" && TIMEMANAGER->getWorldTime() - coolTime[2] > 0.3f)
	{
		ÈëÁÖ¸Ô* EarthPunch = new ÈëÁÖ¸Ô;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
		coolTime[2] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("earthPunch");
	}

	if (skillName == "È­¿°±¸" && TIMEMANAGER->getWorldTime() - coolTime[3] > 5.0f)
	{
		È­¿°±¸* FireBall = new È­¿°±¸;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 1, 30, PLAYER);
		vSkill.push_back(FireBall);
		coolTime[3] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Fireball");
	}

	if (skillName == "ºÒÅ¸´Â¿Ã°¡¹Ì" && TIMEMANAGER->getWorldTime() - coolTime[4] > 10.0f)
	{
		ºÒÅ¸´Â¿Ã°¡¹Ì* FireSword = new ºÒÅ¸´Â¿Ã°¡¹Ì;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
		coolTime[4] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Blazing");
	}

	if (skillName == "¸Í·ÄÈ¸¿À¸®" && TIMEMANAGER->getWorldTime() - coolTime[5] > 5.0f)
	{
		¸Í·ÄÈ¸¿À¸®* WindTornado = new ¸Í·ÄÈ¸¿À¸®;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
		coolTime[5] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Tornado");
	}

	if (skillName == "»çÀÌÅ¬·ĞºÎ¸Ş¶û" && TIMEMANAGER->getWorldTime() - coolTime[6] > 10.0f)
	{
		»çÀÌÅ¬·ĞºÎ¸Ş¶û* CyclronBoomerang = new »çÀÌÅ¬·ĞºÎ¸Ş¶û;
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
		¸ó½ºÅÍ±ÙÁ¢* monsterAtt = new ¸ó½ºÅÍ±ÙÁ¢;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 2.5f, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (!strcmp(skillName, "BlueMageBullet") || !strcmp(skillName, "GreenMageBullet") || !strcmp(skillName, "RedMageBullet"))
	{
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet = new ¸ó½ºÅÍÃÑ¾Ë;
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet2 = new ¸ó½ºÅÍÃÑ¾Ë;
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet3 = new ¸ó½ºÅÍÃÑ¾Ë;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI / 6, 8, 850, 20.0f, 1.0f, ENEMY);
		monsterBullet2->fire(skillName, 1, pt, tempAngle, 8, 850, 1, 20.0f, ENEMY);
		monsterBullet3->fire(skillName, 1, pt, tempAngle + PI / 6, 8, 850, 20.0f, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
	{
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet4 = new ¸ó½ºÅÍÃÑ¾Ë;
		monsterBullet4->fire(skillName, 1, pt, tempAngle, 16, 850, 10.0f, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet4);
	}
	if (!strcmp(skillName, "¾óÀ½´øÁö±â"))
	{
		¾óÀ½´øÁö±â¸Å´ÏÀú* IceM = new ¾óÀ½´øÁö±â¸Å´ÏÀú;
		IceM->fire(skillName, 1, pt, 20.0f, 850, 1, 5.0f, ENEMY);
		IceM->getPlayerAddressLink(_player);
		vSkill.push_back(IceM);
	}
	if (!strcmp(skillName, "¿ì¹Ú"))
	{
		¿ì¹Ú* hail = new ¿ì¹Ú;
		hail->fire(skillName, 1, tempAngle, 16, 850, 5.0F, 5.0f, ENEMY);
		vSkill.push_back(hail);
	}
	if (!strcmp(skillName, "µ¹´øÁö±â"))
	{
		µ¹´øÁö±â* stonThrow = new µ¹´øÁö±â;
		stonThrow->fire(skillName, 1, pt, 16, 850, 30.0F, 5.0f, ENEMY);
		stonThrow->getPlayerAddressLink(_player);
		vSkill.push_back(stonThrow);
	}
	if (!strcmp(skillName, "³ª¹«¼Ú±â"))
	{
		³ª¹«¼Ú±â* woodUp = new ³ª¹«¼Ú±â;
		woodUp->fire(skillName, 1, pt, tempAngle, 20, 850, 0.5f, 1.0f, ENEMY);
		woodUp->getPlayerAddressLink(_player);
		vSkill.push_back(woodUp);
	}
	if (!strcmp(skillName, "¸ŞÅ×¿À"))
	{
		¸ŞÅ×¿À* meteor = new ¸ŞÅ×¿À;
		meteor->fire(skillName, 1, tempAngle, 50, 850, 5.0f, 1.0f, ENEMY);
		vSkill.push_back(meteor);
	}
	if (!strcmp(skillName, "ºÒ±âµÕ"))
	{
		ºÒ±âµÕ* flamestrike = new ºÒ±âµÕ;
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
