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

	if (skillName == "�Ҳ�Ÿ��" && TIMEMANAGER->getWorldTime() - coolTime[0] > 0.2f)
	{
		�Ҳ�Ÿ��* FirePunch = new �Ҳ�Ÿ��;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
		coolTime[0] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("FlameStrike");
	}
	if (skillName == "�ٶ�����" && TIMEMANAGER->getWorldTime() - coolTime[1] > 0.1f)
	{
		�ٶ�����* WindCutter = new �ٶ�����;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
		coolTime[1] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("WindSlash");
	}
	if (skillName == "���ָ�" && TIMEMANAGER->getWorldTime() - coolTime[2] > 0.3f)
	{
		���ָ�* EarthPunch = new ���ָ�;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
		coolTime[2] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("earthPunch");
	}

	if (skillName == "ȭ����" && TIMEMANAGER->getWorldTime() - coolTime[3] > 5.0f)
	{
		ȭ����* FireBall = new ȭ����;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 1, 30, PLAYER);
		vSkill.push_back(FireBall);
		coolTime[3] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Fireball");
	}

	if (skillName == "��Ÿ�¿ð���" && TIMEMANAGER->getWorldTime() - coolTime[4] > 10.0f)
	{
		��Ÿ�¿ð���* FireSword = new ��Ÿ�¿ð���;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
		coolTime[4] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Blazing");
	}

	if (skillName == "�ͷ�ȸ����" && TIMEMANAGER->getWorldTime() - coolTime[5] > 5.0f)
	{
		�ͷ�ȸ����* WindTornado = new �ͷ�ȸ����;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
		coolTime[5] = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Tornado");
	}

	if (skillName == "����Ŭ�кθ޶�" && TIMEMANAGER->getWorldTime() - coolTime[6] > 10.0f)
	{
		����Ŭ�кθ޶�* CyclronBoomerang = new ����Ŭ�кθ޶�;
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
		���ͱ���* monsterAtt = new ���ͱ���;
		monsterAtt->fire(skillName, 1, pt, tempAngle, 15, 350, 2.5f, 1.0f, ENEMY);
		vSkill.push_back(monsterAtt);
	}

	if (!strcmp(skillName, "BlueMageBullet") || !strcmp(skillName, "GreenMageBullet") || !strcmp(skillName, "RedMageBullet"))
	{
		�����Ѿ�* monsterBullet = new �����Ѿ�;
		�����Ѿ�* monsterBullet2 = new �����Ѿ�;
		�����Ѿ�* monsterBullet3 = new �����Ѿ�;
		monsterBullet->fire(skillName, 1, pt, tempAngle - PI / 6, 8, 850, 20.0f, 1.0f, ENEMY);
		monsterBullet2->fire(skillName, 1, pt, tempAngle, 8, 850, 1, 20.0f, ENEMY);
		monsterBullet3->fire(skillName, 1, pt, tempAngle + PI / 6, 8, 850, 20.0f, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet);
		vSkill.push_back(monsterBullet2);
		vSkill.push_back(monsterBullet3);
	}
	if (!strcmp(skillName, "BlueRogueBullet") || !strcmp(skillName, "GreenRogueBullet") || !strcmp(skillName, "RedRogueBullet"))
	{
		�����Ѿ�* monsterBullet4 = new �����Ѿ�;
		monsterBullet4->fire(skillName, 1, pt, tempAngle, 16, 850, 10.0f, 1.0f, ENEMY);
		vSkill.push_back(monsterBullet4);
	}
	if (!strcmp(skillName, "����������"))
	{
		����������Ŵ���* IceM = new ����������Ŵ���;
		IceM->fire(skillName, 1, pt, 20.0f, 850, 1, 5.0f, ENEMY);
		IceM->getPlayerAddressLink(_player);
		vSkill.push_back(IceM);
	}
	if (!strcmp(skillName, "���"))
	{
		���* hail = new ���;
		hail->fire(skillName, 1, tempAngle, 16, 850, 5.0F, 5.0f, ENEMY);
		vSkill.push_back(hail);
	}
	if (!strcmp(skillName, "��������"))
	{
		��������* stonThrow = new ��������;
		stonThrow->fire(skillName, 1, pt, 16, 850, 30.0F, 5.0f, ENEMY);
		stonThrow->getPlayerAddressLink(_player);
		vSkill.push_back(stonThrow);
	}
	if (!strcmp(skillName, "�����ڱ�"))
	{
		�����ڱ�* woodUp = new �����ڱ�;
		woodUp->fire(skillName, 1, pt, tempAngle, 20, 850, 0.5f, 1.0f, ENEMY);
		woodUp->getPlayerAddressLink(_player);
		vSkill.push_back(woodUp);
	}
	if (!strcmp(skillName, "���׿�"))
	{
		���׿�* meteor = new ���׿�;
		meteor->fire(skillName, 1, tempAngle, 50, 850, 5.0f, 1.0f, ENEMY);
		vSkill.push_back(meteor);
	}
	if (!strcmp(skillName, "�ұ��"))
	{
		�ұ��* flamestrike = new �ұ��;
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
