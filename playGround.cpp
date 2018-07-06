#include "stdafx.h"
#include "playGround.h"


playGround::playGround() {}
playGround::~playGround() {}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	settingAddImage();

	SCENEMANAGER->addScene("intro", new intro);
	SCENEMANAGER->addScene("ending", new ending);
	SCENEMANAGER->addScene("loading", new loading);
	SCENEMANAGER->addScene("inGame", new inGame);
	SCENEMANAGER->addScene("mapTool", new mapTool);

	SCENEMANAGER->changeScene("mapTool");

	return S_OK;
}

void playGround::release(void)
{
	gameNode::release();
}

void playGround::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("mapTool");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("inGame");
	}

	SCENEMANAGER->update();
}

void playGround::render(void)
{
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SCENEMANAGER->render();

	//TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());

	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}




void playGround::settingAddImage(void)
{
	//======================================= MONSTER ======================================================
	IMAGEMANAGER->addFrameImage("SummonMonster", "image/Effect/SummonMonster.bmp", 0, 0, 64, 1856, 1, 29, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Ghoul", "image/monster/Ghoul.bmp", 0, 0, 560, 304, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Scarecrow", "image/monster/Scarecrow.bmp", 0, 0, 80, 60, 2, 1, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RedKnight", "image/monster/RedKnight.bmp", 0, 0, 420 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueKnight", "image/monster/BlueKnight.bmp", 0, 0, 420 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenKnight", "image/monster/GreenKnight.bmp", 0, 0, 420 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RedMage", "image/monster/RedMage.bmp", 0, 0, 280 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueMage", "image/monster/BlueMage.bmp", 0, 0, 280 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenMage", "image/monster/GreenMage.bmp", 0, 0, 280 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("RedRogue", "image/monster/RedRogue.bmp", 0, 0, 300 * 2, 160 * 2, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueRogue", "image/monster/BlueRogue.bmp", 0, 0, 300 * 2, 160 * 2, 10, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenRogue", "image/monster/GreenRogue.bmp", 0, 0, 300 * 2, 160 * 2, 10, 4, true, RGB(255, 0, 255));

	//========================================== BOSS ===============================================
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

	//====================================================== UI ====================================================
	IMAGEMANAGER->addImage("mouse", "image/UI/mouse.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerIcon", "image/UI/playerIcon.bmp", 75, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerFrontHp", "image/UI/playerFrontHp.bmp", 230, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerBackHp", "image/UI/playerBackHp.bmp", 250, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("playerCoin", "image/UI/playerCoin.bmp", 30, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonF", "image/UI/buttonF.bmp", 40, 40, true, RGB(255, 0, 255));

	//====================================================== ITEM ===================================================
	IMAGEMANAGER->addFrameImage("coinFrame", "image/item/coinFrame.bmp", 150, 25, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item0", "image/item/item0.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item1", "image/item/item1.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item2", "image/item/item2.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item3", "image/item/item3.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item4", "image/item/item4.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item5", "image/item/item5.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item6", "image/item/item6.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item7", "image/item/item7.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item8", "image/item/item8.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("item9", "image/item/item9.bmp", 25, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("inventory", "image/item/inventory.bmp", 400, 500, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("storeNpc", "image/store/storeNpc.bmp", 50, 75, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("storeTable", "image/store/storeTable.bmp", 160, 64, true, RGB(255, 0, 255));

	//===================================================== PLAYER ===================================================
	IMAGEMANAGER->addFrameImage("player", "image/player/player.bmp", 1600, 1900, 16, 19, true, RGB(255, 0, 255));
}