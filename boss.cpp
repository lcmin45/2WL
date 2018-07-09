#include "stdafx.h"
#include "boss.h"
#include "player.h"

boss::boss() {}
boss::~boss() {}

HRESULT boss::init()
{
	//���� ������ ��ȣ
	_woodindex = 0;
	_iceindex = 0;
	_fireindex = 0;

	//���� ����Ȯ�� ����
	_woodBossDie = false;
	_iceBossDie = false;
	_fireBossDie = false;

	//���� �̹��� ��ȯ�� ���� ī��Ʈ����
	_bossMoveCount = 0;

	//���� ��ȭ ����
	_woodDialogue = false;
	_iceDialogue = false;
	_fireDialogue = false;

	//���� �������� �ִ� ����
	_woodMove = false;
	_iceMove = false;
	_fireMove = false;

	//���� ü��
	//��ġ ���� �߰����ֱ�
	_woodHpBar = new bossProgressBar;
	_woodHpBar->init(150, 30, 450, 70);

	_iceHpBar = new bossProgressBar;
	_iceHpBar->init(150, 30, 450, 70);

	_fireHpBar = new bossProgressBar;
	_fireHpBar->init(150, 30, 450, 70);

	_woodCurrentHP = _woodMaxHP = 150;
	_iceCurrentHP = _iceMaxHP = 150;
	_fireCurrentHP = _fireMaxHP = 150;

	return S_OK;
}

HRESULT boss::setting(const char * imageName, POINTFLOAT position)
{
	_frameCount = 0;
	_bossImg = IMAGEMANAGER->findImage(imageName);
	_bossRc = RectMakeCenter(position.x, position.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	_x = position.x;
	_y = position.y;
	return S_OK;
}

void boss::release() {}

void boss::render()
{

}

void boss::update()
{
	_woodHpBar->setGauge(_woodCurrentHP, _woodMaxHP);
	_woodHpBar->update();

	_iceHpBar->setGauge(_iceCurrentHP, _iceMaxHP);
	_iceHpBar->update();

	_fireHpBar->setGauge(_fireCurrentHP, _fireMaxHP);
	_fireHpBar->update();
}
