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
	IMAGEMANAGER->addFrameImage("�Ҳ�Ÿ��", "image/skill/�Ҳ�Ÿ��.bmp", 896, 64, 16, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ҳ���ƼŬ", "image/skill/�Ҳ���ƼŬ.bmp", 666, 94, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ȭ����", "image/skill/ȭ����.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ָ�", "image/skill/���ָ�.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٶ�����", "image/skill/�ٶ�����.bmp", 480, 1920, 4, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٶ���ƼŬ", "image/skill/�ٶ���ƼŬ.bmp", 900, 750, 6, 5, true, RGB(255, 0, 255));
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
	float tempAngle = getAngle(pt.x, pt.y, _player->getPosition().x, _player->getPosition().y);

	if (skillName == "BlueKnightBullet" || skillName == "GreenKnightBullet" || skillName == "RedKnightBullet" || skillName == "GhoulBullet")
	{
		���ͱ���* monsterAtt = new ���ͱ���;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (skillName == "BlueMageBullet" || skillName == "GreenMageBullet" || skillName == "RedMageBullet")
	{
		�����Ѿ�* monsterBullet = new �����Ѿ�;
		�����Ѿ�* monsterBullet2 = new �����Ѿ�;
		�����Ѿ�* monsterBullet3 = new �����Ѿ�;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI/6, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet->fire(skillName, 1, pt, tempAngle, 8, 850, 50, 1.0f, ENEMY);
		monsterBullet->fire(skillName, 1, pt, tempAngle + PI/6, 8, 850, 50, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (skillName == "BlueRogueBullet" || skillName == "GreenRogueBullet" || skillName == "RedRogueBullet")
	{
		�����Ѿ�* monsterBullet4 = new �����Ѿ�;
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
