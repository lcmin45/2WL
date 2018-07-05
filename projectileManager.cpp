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
	IMAGEMANAGER->addFrameImage("¹Ù¶÷ÆÄÆ¼Å¬", "image/skill/¹Ù¶÷ÆÄÆ¼Å¬.bmp", 192, 160, 8, 8, true, RGB(255, 0, 255));


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
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
		vSkill.push_back(FirePunch);
	}
	if (skillName == "¹Ù¶÷º£±â")
	{
		¹Ù¶÷º£±â* WindCutter = new ¹Ù¶÷º£±â;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
		vSkill.push_back(WindCutter);
	}
	if (skillName == "ÈëÁÖ¸Ô")
	{
		ÈëÁÖ¸Ô* EarthPunch = new ÈëÁÖ¸Ô;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
	}

	if (skillName == "È­¿°±¸")
	{
		È­¿°±¸* FireBall = new È­¿°±¸;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 50, 30);
		vSkill.push_back(FireBall);
	}

	if (skillName == "ºÒÅ¸´Â¿Ã°¡¹Ì")
	{
		ºÒÅ¸´Â¿Ã°¡¹Ì* FireSword = new ºÒÅ¸´Â¿Ã°¡¹Ì;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 50, 1.0f);
		vSkill.push_back(FireSword);
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
