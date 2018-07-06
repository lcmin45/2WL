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
	IMAGEMANAGER->addFrameImage("ºÒ²ÉÅ¸°İ", "image/skill/ºÒ²ÉÅ¸°İ.bmp", 896, 64, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ºÒ²ÉÆÄÆ¼Å¬", "image/skill/ºÒ²ÉÆÄÆ¼Å¬.bmp", 666, 94, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("È­¿°±¸", "image/skill/È­¿°±¸.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ÈëÁÖ¸Ô", "image/skill/ÈëÁÖ¸Ô.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¹Ù¶÷º£±â", "image/skill/¹Ù¶÷º£±â.bmp", 480, 1920, 4, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¹Ù¶÷ÆÄÆ¼Å¬", "image/skill/¹Ù¶÷ÆÄÆ¼Å¬.bmp", 900, 750, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueKnightBullet", "image/skill/monsterBullet/BlueKnightBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenKnightBullet", "image/skill/monsterBullet/GreenKnightBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RedKnightBullet", "image/skill/monsterBullet/RedKnightBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueMageBullet", "image/skill/monsterBullet/BlueMageBullet.bmp", 160, 256, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenMageBullet", "image/skill/monsterBullet/GreenMageBullet.bmp", 160, 256, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RedMageBullet", "image/skill/monsterBullet/RedMageBullet.bmp", 160, 256, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueRogueBullet", "image/skill/monsterBullet/BlueRogueBullet.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenRogueBullet", "image/skill/monsterBullet/GreenRogueBullet.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RedRogueBullet", "image/skill/monsterBullet/RedRogueBullet.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GhoulBullet", "image/skill/monsterBullet/GhoulBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));



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
	float tempAngle = getAngle(pt.x, pt.y, _player->getPosition().x, _player->getPosition().y);

	if (skillName == "BlueKnightBullet" || skillName == "GreenKnightBullet" || skillName == "RedKnightBullet" || skillName == "GhoulBullet")
	{
		¸ó½ºÅÍ±ÙÁ¢* monsterAtt = new ¸ó½ºÅÍ±ÙÁ¢;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (skillName == "BlueMageBullet" || skillName == "GreenMageBullet" || skillName == "RedMageBullet")
	{
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet = new ¸ó½ºÅÍÃÑ¾Ë;
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet2 = new ¸ó½ºÅÍÃÑ¾Ë;
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet3 = new ¸ó½ºÅÍÃÑ¾Ë;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI/6, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet->fire(skillName, 1, pt, tempAngle, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet->fire(skillName, 1, pt, tempAngle + PI/6, 8, 850, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (skillName == "BlueRogueBullet" || skillName == "GreenRogueBullet" || skillName == "RedRogueBullet")
	{
		¸ó½ºÅÍÃÑ¾Ë* monsterBullet4 = new ¸ó½ºÅÍÃÑ¾Ë;
		monsterBullet4->fire(skillName, 1, pt, tempAngle, 16, 850, 50, 1.0f, ENEMY);
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
