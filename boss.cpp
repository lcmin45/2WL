#include "stdafx.h"
#include "boss.h"
#include "player.h"

boss::boss() {}
boss::~boss() {}

HRESULT boss::init()
{
	//���� ���� �̹���
	IMAGEMANAGER->addFrameImage("������ȯ", "image/boss/��������/����������ȯ.bmp", 0, 0, 3200, 129, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 294 * 2, 58 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 420 * 2, 69 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/boss/��������/���������������̵�.bmp", 0, 0, 138 * 2, 51 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/�������������̵�.bmp", 0, 0, 138 * 2, 51 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/boss/��������/����������ų.bmp", 0, 0, 210 * 2, 58 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2������", "image/boss/��������/����������ų2������.bmp", 0, 0, 430 * 2, 58 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2����", "image/boss/��������/����������ų2����.bmp", 0, 0, 430 * 2, 58 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����������ǰ�", "image/boss/��������/���������������ǰ�.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������ǰ�", "image/boss/��������/�������������ǰ�.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 34 * 2, 45 * 2, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������ȭ", "image/boss/��������/������ȭ.bmp", 850, 200, false, RGB(0, 0, 0));

	//���� ���� �̹���
	IMAGEMANAGER->addFrameImage("������ȯ", "image/boss/��������/����������ȯ.bmp", 0, 0, 500 * 2, 61 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 228 * 2, 54 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/boss/��������/����������ų.bmp", 0, 0, 306 * 2, 52 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2", "image/boss/��������/����������ų2.bmp", 0, 0, 96 * 2, 50 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ǰ�", "image/boss/��������/���������ǰ�.bmp", 0, 0, 40 * 2, 48 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 32 * 2, 38 * 2, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("������ȭ", "image/boss/��������/������ȭ.bmp", 850, 200, false, RGB(0, 0, 0));

	//�Ҳ� ���� �̹���
	IMAGEMANAGER->addFrameImage("�Ҽ�ȯ", "image/boss/�Һ���/�Һ�����ȯ.bmp", 0, 0, 350 * 2, 45 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҵ���", "image/boss/�Һ���/�Һ�������.bmp", 0, 0, 350 * 2, 33 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҿ�����", "image/boss/�Һ���/�Һ����������̵�.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҿ���", "image/boss/�Һ���/�Һ��������̵�.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų������", "image/boss/�Һ���/�Һ�����ų������.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų����", "image/boss/�Һ���/�Һ�����ų����.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų2", "image/boss/�Һ���/�Һ�����ų2������.bmp", 0, 0, 135 * 2, 40 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ǰ�", "image/boss/�Һ���/�Һ����ǰ�.bmp", 0, 0, 42 * 2, 37 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "image/boss/�Һ���/�Һ�������.bmp", 0, 0, 28 * 2, 30 * 2, 1, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("�Ҵ�ȭ", "image/boss/�Һ���/�Ҵ�ȭ.bmp", 850, 200, true, RGB(255, 0, 255));

	//���� ������ ��ȣ
	_woodindex = 0;
	_iceindex = 0;
	_fireindex = 0;

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
