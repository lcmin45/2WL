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
		�Ҳ�Ÿ�� firePunchAtt;
		ZeroMemory(&firePunchAtt, sizeof(�Ҳ�Ÿ��));
		firePunchAtt.fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
		vFirePunchAtt.push_back(firePunchAtt);
	}
	if (skillName == "�ٶ�����")
	{
		�ٶ����� windCutterAtt;
		ZeroMemory(&windCutterAtt, sizeof(�ٶ�����));
		windCutterAtt.fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
		vWindCutterAtt.push_back(windCutterAtt);
	}
	if (skillName == "���ָ�")
	{
		���ָ� earthPunchAtt;
		ZeroMemory(&earthPunchAtt, sizeof(���ָ�));
		earthPunchAtt.fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f);
		earthPunchAtt.fireAtt();
		vEarthPunchAtt.push_back(earthPunchAtt);
	}

	if (skillName == "ȭ����")
	{
		ȭ���� fireBallAtt;
		ZeroMemory(&fireBallAtt, sizeof(ȭ����));
		fireBallAtt.fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 50, 30);
		vFireBallAtt.push_back(fireBallAtt);
	}

	if (skillName == "��Ÿ�¿ð���")
	{
		��Ÿ�¿ð��� fireSword;
		ZeroMemory(&fireSword, sizeof(��Ÿ�¿ð���));
		fireSword.fire(skillName, 1, _player->getPosition(), 8, 200, 50, 1.0f);
		vFireSword.push_back(fireSword);
	}
}

void projectileManager::vectorCheck()
{
	if (vFirePunchAtt.size() != 0)
	{
		for (viFirePunchAtt = vFirePunchAtt.begin(); viFirePunchAtt != vFirePunchAtt.end();)
		{
			if (!viFirePunchAtt->getImage())
			{
				viFirePunchAtt = vFirePunchAtt.erase(viFirePunchAtt);
			}
			else
			{
				viFirePunchAtt->update();
				viFirePunchAtt++;
			}
		}
	}
	if (vWindCutterAtt.size() != 0)
	{
		for (viWindCutterAtt = vWindCutterAtt.begin(); viWindCutterAtt != vWindCutterAtt.end();)
		{
			if (!viWindCutterAtt->getImage())
			{
				viWindCutterAtt = vWindCutterAtt.erase(viWindCutterAtt);
			}
			else
			{
				viWindCutterAtt->update();
				viWindCutterAtt++;
			}
		}
	}
	if (vEarthPunchAtt.size() != 0)
	{
		for (viEarthPunchAtt = vEarthPunchAtt.begin(); viEarthPunchAtt != vEarthPunchAtt.end();)
		{
			if (!viEarthPunchAtt->getImage())
			{
				viEarthPunchAtt = vEarthPunchAtt.erase(viEarthPunchAtt);
			}
			else
			{
				viEarthPunchAtt->update();
				viEarthPunchAtt++;
			}
		}
	}
	if (vFireBallAtt.size() != 0)
	{
		for (viFireBallAtt = vFireBallAtt.begin(); viFireBallAtt != vFireBallAtt.end();)
		{
			if (!viFireBallAtt->getImage())
			{
				viFireBallAtt = vFireBallAtt.erase(viFireBallAtt);
			}
			else
			{
				viFireBallAtt->update();
				viFireBallAtt++;
			}
		}
	}
	if (vFireSword.size() != 0)
	{
		for (viFireSword = vFireSword.begin(); viFireSword != vFireSword.end();)
		{
			if (!viFireSword->getImage())
			{
				viFireSword = vFireSword.erase(viFireSword);
			}
			else
			{
				viFireSword->update();
				viFireSword++;
			}
		}
	}
}

void projectileManager::vectorDraw()
{
	if (vFirePunchAtt.size() != 0)
	{
		for (viFirePunchAtt = vFirePunchAtt.begin(); viFirePunchAtt != vFirePunchAtt.end(); viFirePunchAtt++)
		{
			viFirePunchAtt->render();
		}
	}
	if (vWindCutterAtt.size() != 0)
	{
		for (viWindCutterAtt = vWindCutterAtt.begin(); viWindCutterAtt != vWindCutterAtt.end(); viWindCutterAtt++)
		{
			viWindCutterAtt->render();
		}
	}
	if (vEarthPunchAtt.size() != 0)
	{
		for (viEarthPunchAtt = vEarthPunchAtt.begin(); viEarthPunchAtt != vEarthPunchAtt.end(); viEarthPunchAtt++)
		{
			viEarthPunchAtt->render();
		}
	}
	if (vFireBallAtt.size() != 0)
	{
		for (viFireBallAtt = vFireBallAtt.begin(); viFireBallAtt != vFireBallAtt.end(); viFireBallAtt++)
		{
			viFireBallAtt->render();
		}
	}
	if (vFireSword.size() != 0)
	{
		for (viFireSword = vFireSword.begin(); viFireSword != vFireSword.end(); viFireSword++)
		{
			viFireSword->render();
		}
	}
}
