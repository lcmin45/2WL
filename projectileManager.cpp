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
	const char* tempSkillName[7] = { "�ٶ�����", "ȭ����", "��Ÿ�¿ð���", "�ͷ�ȸ����", "���ָ�", "�Ҳ�Ÿ��", "����Ŭ�кθ޶�" };
	float tempSkillTime[7] = { 0.1f, 5.0f, 10.0f, 5.0f, 0.3f, 0.2f, 10.0f };

	for (int i = 0; i < 7; i++)
	{
		coolTime[i].name = tempSkillName[i];
		coolTime[i].skillTime = tempSkillTime[i];
	}

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

bool projectileManager::fire(const char * skillName)
{
	float tempAngle = getAngle(_player->getPosition().x, _player->getPosition().y, getMousePoint().x, getMousePoint().y);

	float tempDeal = _player->getDamage();
	if (RND->getInt(100) < _player->getCritical()) tempDeal * 2.0f;

	if (skillName == "�ٶ�����" && TIMEMANAGER->getWorldTime() - coolTime[0].coolTime > coolTime[0].skillTime)
	{
		�ٶ�����* WindCutter = new �ٶ�����;
		WindCutter->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1 * tempDeal, 1.0f, PLAYER);
		vSkill.push_back(WindCutter);
		coolTime[0].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("WindSlash");

		return true;
	}
	if (skillName == "ȭ����" && TIMEMANAGER->getWorldTime() - coolTime[1].coolTime > coolTime[1].skillTime)
	{
		ȭ����* FireBall = new ȭ����;
		FireBall->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX * 2, 1 * tempDeal, 30, PLAYER);
		vSkill.push_back(FireBall);
		coolTime[1].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Fireball");

		return true;
	}
	if (skillName == "��Ÿ�¿ð���" && TIMEMANAGER->getWorldTime() - coolTime[2].coolTime > coolTime[2].skillTime)
	{
		��Ÿ�¿ð���* FireSword = new ��Ÿ�¿ð���;
		FireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 1 * tempDeal, 1.0f, PLAYER);
		vSkill.push_back(FireSword);
		coolTime[2].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Blazing");

		return true;
	}
	if (skillName == "�ͷ�ȸ����" && TIMEMANAGER->getWorldTime() - coolTime[3].coolTime > coolTime[3].skillTime)
	{
		�ͷ�ȸ����* WindTornado = new �ͷ�ȸ����;
		WindTornado->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1 * tempDeal, 1.0f, PLAYER);
		vSkill.push_back(WindTornado);
		coolTime[3].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Tornado");

		return true;
	}

	if (skillName == "���ָ�" && TIMEMANAGER->getWorldTime() - coolTime[4].coolTime > coolTime[4].skillTime)
	{
		���ָ�* EarthPunch = new ���ָ�;
		EarthPunch->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 1 * tempDeal, 1.0f, PLAYER);
		EarthPunch->fireAtt();
		vSkill.push_back(EarthPunch);
		coolTime[4].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("earthPunch");

		return true;
	}
	if (skillName == "�Ҳ�Ÿ��" && TIMEMANAGER->getWorldTime() - coolTime[5].coolTime > coolTime[5].skillTime)
	{
		�Ҳ�Ÿ��* FirePunch = new �Ҳ�Ÿ��;
		FirePunch->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 1 * tempDeal, 1.0f, PLAYER);
		vSkill.push_back(FirePunch);
		coolTime[5].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("FlameStrike");

		return true;
	}
	if (skillName == "����Ŭ�кθ޶�" && TIMEMANAGER->getWorldTime() - coolTime[6].coolTime > coolTime[6].skillTime)
	{
		����Ŭ�кθ޶�* CyclronBoomerang = new ����Ŭ�кθ޶�;
		CyclronBoomerang->fire(skillName, 1, _player->getPosition(), tempAngle, 15, 350, 1 * tempDeal, 1.0f, PLAYER);
		vSkill.push_back(CyclronBoomerang);
		coolTime[6].coolTime = TIMEMANAGER->getWorldTime();
		SOUNDMANAGER->play("Tornado");

		return true;
	}

	return false;
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

float projectileManager::getCoolTime(const char * name)
{
	for (int i = 0; i < 7; i++)
	{
		if (strcmp(name, coolTime[i].name) == 0)
		{
			float tempTime = coolTime[i].skillTime - (TIMEMANAGER->getWorldTime() - coolTime[i].coolTime);
			if (tempTime <= 0.0f) return 0.0f;
			else return tempTime;
		}
	}
}
