#include "stdafx.h"
#include "boss.h"

boss::boss() {}
boss::~boss() {}

HRESULT boss::init()
{
	//���� ���� �̹���
	IMAGEMANAGER->addFrameImage("������ȯ", "image/boss/��������/����������ȯ.bmp", 0, 0, 3200, 129, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 294*2, 58 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 420 * 2, 69 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/boss/��������/���������������̵�.bmp", 0, 0, 184 * 2, 51 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/�������������̵�.bmp", 0, 0, 184 * 2, 51 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/boss/��������/����������ų.bmp", 0, 0, 210 * 2, 58 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2������", "image/boss/��������/����������ų2������.bmp", 0, 0, 430 * 2, 58 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2����", "image/boss/��������/����������ų2����.bmp", 0, 0, 430 * 2, 58 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����������ǰ�", "image/boss/��������/���������������ǰ�.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������ǰ�", "image/boss/��������/�������������ǰ�.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 34 * 2, 45 * 2, 1, 1, true, RGB(255, 0, 255));

	//���� ���� �̹���
	IMAGEMANAGER->addFrameImage("������ȯ", "image/boss/��������/����������ȯ.bmp", 0, 0, 500 * 2, 61 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 228 * 2, 54 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "image/boss/��������/�����������̵�.bmp", 0, 0, 31 * 2, 42 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "image/boss/��������/�����������̵�.bmp", 0, 0, 32 * 2, 35 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/boss/��������/���������������̵�.bmp", 0, 0, 32 * 2, 40 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/�������������̵�.bmp", 0, 0, 32 * 2,40 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/boss/��������/����������ų.bmp", 0, 0, 306 * 2, 52 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2", "image/boss/��������/����������ų2.bmp", 0, 0,96*2, 50*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ǰ�", "image/boss/��������/���������ǰ�.bmp", 0, 0, 40 * 2, 48 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 32 * 2, 38 * 2, 1, 1, true, RGB(255, 0, 255));

	//�Ҳ� ���� �̹���
	IMAGEMANAGER->addFrameImage("�Ҽ�ȯ", "image/boss/�Һ���/�Һ�����ȯ.bmp", 0, 0, 350 * 2, 45 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҵ���", "image/boss/�Һ���/�Һ�������.bmp", 0, 0, 350 * 2, 33 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҿ�����", "image/boss/�Һ���/�Һ����������̵�.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҿ���", "image/boss/�Һ���/�Һ��������̵�.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų������", "image/boss/�Һ���/�Һ�����ų������.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų����", "image/boss/�Һ���/�Һ�����ų����.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų2������", "image/boss/�Һ���/�Һ�����ų2������.bmp", 0, 0, 135 * 2, 40 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ҽ�ų2����", "image/boss/�Һ���/�Һ�����ų2����.bmp", 0, 0, 135 * 2, 40 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ǰ�", "image/boss/�Һ���/�Һ����ǰ�.bmp", 0, 0, 42 * 2, 37 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", "image/boss/�Һ���/�Һ�������.bmp", 0, 0, 28 * 2, 30 * 2, 1, 1, true, RGB(255, 0, 255));

	_woodBossDie = false;
	_iceBossDie= false;
	_fireBossDie= false;
	_index = 0;

	_woodDirection = WOODDIRECTION_SOHWAN;
	_iceDirection = ICEDIRECTION_SOHWAN;
	_fireDirection = FIREDIRECTION_SHOW;

	return S_OK;
}

HRESULT boss::setting(const char * imageName, POINT position)
{
	_frameCount = 0;
	_bossImg = IMAGEMANAGER->findImage(imageName);
	_bossRc = RectMakeCenter(position.x, position.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	return S_OK;
}

void boss::release() {}

void boss::render()
{
	_bossImg->frameRender(CAMERAMANAGER->getCameraDC(), _bossRc.left, _bossRc.top, _index,0);
}

void boss::update()
{
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		++_index;
		if (_woodDirection == WOODDIRECTION_SHOW || _iceDirection == ICEDIRECTION_SHOW || _fireDirection == FIREDIRECTION_SHOW)
		{
			if (_index > _bossImg->getMaxFrameX())
			{
				_index = 0;
			}
		}
		_frameCount = 0;
	}
}

void boss::woodMove()
{
}

void boss::iceMove()
{
}

void boss::fireMove()
{
}

void boss::woodSkill()
{
}

void boss::iceSkill()
{
}

void boss::fireSkill()
{
}
