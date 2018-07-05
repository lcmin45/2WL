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
	IMAGEMANAGER->addFrameImage("�ٶ���ƼŬ", "image/skill/�ٶ���ƼŬ.bmp", 192, 160, 8, 8, true, RGB(255, 0, 255));


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
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
		vSkill.push_back(FirePunch);
	}
	if (skillName == "�ٶ�����")
	{
		�ٶ�����* WindCutter = new �ٶ�����;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
		vSkill.push_back(WindCutter);
	}
	if (skillName == "���ָ�")
	{
		���ָ�* EarthPunch = new ���ָ�;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
	}

	if (skillName == "ȭ����")
	{
		ȭ����* FireBall = new ȭ����;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 50, 30);
		vSkill.push_back(FireBall);
	}

	if (skillName == "��Ÿ�¿ð���")
	{
		��Ÿ�¿ð���* FireSword = new ��Ÿ�¿ð���;
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
