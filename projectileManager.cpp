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

	string str[MAXPARTICLE];

	for (int i = 0; i < MAXPARTICLE; i++)
	{
		str[i] = i;
		IMAGEMANAGER->addFrameImage(str[i], "image/skill/�Ҳ���ƼŬ.bmp", 666, 94, 9, 1, true, RGB(255, 0, 255));
	}
	string pStr[64];
	for (int i = 0; i < 64; i++)
	{
		pStr[i] = i + MAXPARTICLE;
		IMAGEMANAGER->addFrameImage(pStr[i], "image/skill/�Ҳ���ƼŬ.bmp", 666, 94, 9, 1, true, RGB(255, 0, 255));
	}
	

	firePunchAtt = new �Ҳ�Ÿ��;
	windCutterAtt = new �ٶ�����;
	earthPunchAtt = new ���ָ�;



	fireBallAtt = new ȭ����;



	fireSword = new ��Ÿ�¿ð���;

	return S_OK;
}

void projectileManager::release()
{
	
}

void projectileManager::update()
{
	if (firePunchAtt) firePunchAtt->update();
	if (windCutterAtt) windCutterAtt->update();
	if (earthPunchAtt) earthPunchAtt->update();

	if (fireBallAtt) fireBallAtt->update();


	if (fireSword) fireSword->update();


	if (fireSword->getErase())
	{
		/*delete fireSword;
		ZeroMemory(&fireSword, sizeof(fireSword));
		fireSword = new ��Ÿ�¿ð���;*/
	}
}

void projectileManager::render()
{
	if (firePunchAtt) firePunchAtt->render();
	if (windCutterAtt) windCutterAtt->render();
	if (earthPunchAtt) earthPunchAtt->render();

	if (fireBallAtt) fireBallAtt->render();

	if (fireSword) fireSword->render();
}

void projectileManager::fire(const char * skillName)
{
	float tempAngle = getAngle(_player->getPosition().x, _player->getPosition().y, getMousePoint().x, getMousePoint().y);

	if (skillName == "�Ҳ�Ÿ��")
	{
		firePunchAtt->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50,1.0f);
	}
	if (skillName == "�ٶ�����")
	{
		windCutterAtt->fire(skillName, 1, _player->getPosition(), tempAngle, 100, 200, 50, 1.0f);
	}
	if (skillName == "���ָ�")
	{
		if (earthPunchAtt->getImage()) return;
		earthPunchAtt->fire(skillName, 1, _player->getPosition(), tempAngle, 8, 200, 50, 1.0f);
		earthPunchAtt->fireAtt();
	}

	if (skillName == "ȭ����")
	{
		fireBallAtt->fire(skillName, 1, _player->getPosition(), tempAngle, 30, WINSIZEX*2, 50, 30);
	}

	if (skillName == "��Ÿ�¿ð���")
	{
		fireSword->fire(skillName, 1, _player->getPosition(), 8, 200, 50, 1.0f);
	}
}
