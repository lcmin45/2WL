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
	_woodHpBar->init(380, 0, "bossfrontBar", 360, 25, "bossbackBar", 450, 60);

	_iceHpBar = new bossProgressBar;
	_iceHpBar->init(380, 0, "bossfrontBar", 360, 25, "bossbackBar", 450, 60);

	_fireHpBar = new bossProgressBar;
	_fireHpBar->init(380, 0, "bossfrontBar", 360, 25, "bossbackBar", 450, 60);

	_woodCurrentHP = _woodMaxHP = 500;
	_iceCurrentHP = _iceMaxHP = 500;
	_fireCurrentHP = _fireMaxHP = 500;

	_speed = 5.0f;
	_jump = 0.0f;

	_skill = false;

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
	
}
