#include "stdafx.h"
#include "playGround.h"


playGround::playGround() {}
playGround::~playGround() {}

HRESULT playGround::init(void)
{
	gameNode::init(true);
	 
	settingAddImage();
	settingAddSound();

	SCENEMANAGER->addScene("intro", new intro);
	SCENEMANAGER->addScene("inGame", new inGame);
	SCENEMANAGER->addScene("loading", new loading);
	SCENEMANAGER->addScene("ending", new ending);
	SCENEMANAGER->addScene("mapTool", new mapTool);

	SCENEMANAGER->changeScene("intro");

	return S_OK;
}

void playGround::release(void)
{
	gameNode::release();
}

void playGround::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeScene("intro");
		CAMERAMANAGER->setCameraPoint({ 0, 0 });
	}

	SCENEMANAGER->update();
}

void playGround::render(void)
{
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SCENEMANAGER->render();
	IMAGEMANAGER->findImage("Black")->alphaRender(getMemDC(), CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, _BlackAalpha);

	TIMEMANAGER->render(CAMERADC);

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
	//���� ü�¹�
	IMAGEMANAGER->addImage("bossfrontBar", "image/boss/bossHpBarTop.bmp", 360, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbackBar", "image/boss/bossHpBarBottom.bmp", 450, 60, true, RGB(255, 0, 255));

	//���� ���� �̹���
	IMAGEMANAGER->addFrameImage("������ȯ", "image/boss/��������/����������ȯ.bmp", 0, 0, 3328, 129, 26, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 294 * 2, 58 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 420 * 2, 69 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/boss/��������/���������������̵�.bmp", 0, 0, 138 * 2, 51 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/�������������̵�.bmp", 0, 0, 138 * 2, 51 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/boss/��������/����������ų.bmp", 0, 0, 210 * 2, 58 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2������", "image/boss/��������/����������ų2������.bmp", 0, 0, 387 * 2, 58 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2����", "image/boss/��������/����������ų2����.bmp", 0, 0, 387 * 2, 58 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����������ǰ�", "image/boss/��������/���������������ǰ�.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���������ǰ�", "image/boss/��������/�������������ǰ�.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 34 * 2, 45 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȭ", "image/boss/��������/������ȭ.bmp", 850, 200, false, RGB(0, 0, 0));

	//���� ���� �̹���
	IMAGEMANAGER->addFrameImage("������ȯ", "image/boss/��������/����������ȯ.bmp", 0, 0, 550 * 2, 61 * 2, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 228 * 2, 54 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų", "image/boss/��������/����������ų.bmp", 0, 0, 306 * 2, 52 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������ų2", "image/boss/��������/����������ų2.bmp", 0, 0, 96 * 2, 50 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ǰ�", "image/boss/��������/���������ǰ�.bmp", 0, 0, 40 * 2, 48 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/boss/��������/������������.bmp", 0, 0, 32 * 2, 38 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("������ȭ", "image/boss/��������/������ȭ.bmp", 850, 200, false, RGB(0, 0, 0));

	//�Ҳ� ���� �̹���
	IMAGEMANAGER->addFrameImage("�Ҽ�ȯ", "image/boss/�Һ���/�Һ�����ȯ.bmp", 0, 0, 400 * 2, 45 * 2, 8, 1, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addImage("buttonZ", "image/UI/buttonZ.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonX", "image/UI/buttonX.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonC", "image/UI/buttonC.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("buttonF", "image/UI/buttonF.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mouseL", "image/UI/mouseL.bmp", 40, 40, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skillSet", "image/UI/skillSet.bmp", 400, 560, true, RGB(255, 0, 255));
	//SKILL UI
	IMAGEMANAGER->addImage("UI�ٶ�����", "image/UI/�ٶ�����.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI���ָ�", "image/UI/���ָ�.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI�Ҳ�Ÿ��", "image/UI/�Ҳ�Ÿ��.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UIȭ����", "image/UI/ȭ����.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI��Ÿ�¿ð���", "image/UI/��Ÿ�¿ð���.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI�ͷ�ȸ����", "image/UI/�ͷ�ȸ����.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI����Ŭ�кθ޶�", "image/UI/����Ŭ�кθ޶�.bmp", 50, 50, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("TitleScreen", "image/UI/TitleScreen.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleLogo", "image/UI/TitleLogo.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Black", "image/UI/Black.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PRESS ANY BUTTON", "image/UI/PRESS ANY BUTTON.bmp", 300, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GameStart", "image/UI/GameStart.bmp", 320, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Load", "image/UI/Load.bmp", 180, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MapTool", "image/UI/MapTool.bmp", 280, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Setting", "image/UI/Setting.bmp", 260, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("EXIT", "image/UI/EXIT.bmp", 150, 100, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("��Ż", "image/UI/��Ż.bmp", 52*2, 42*2, 2, 1, true, RGB(255, 0, 255));


	IMAGEMANAGER->addImage("option", "image/UI/option.bmp", 600, 400, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionBar", "image/UI/optionBar.bmp", 400, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("optionChoiceBar", "image/UI/optionChoiceBar.bmp", 40, 40, true, RGB(255, 0, 255)); 
	IMAGEMANAGER->addFrameImage("optionIcon", "image/UI/optionIcon.bmp", 50, 100,1,2, true, RGB(255, 0, 255));

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

	//===================================================== SKILL ===================================================

	IMAGEMANAGER->addFrameImage("�Ҳ�Ÿ��", "image/skill/�Ҳ�Ÿ��.bmp", 750, 600, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ҳ���ƼŬ", "image/skill/�Ҳ���ƼŬ.bmp", 300, 200, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�Ҳ���ƼŬ2", "image/skill/�Ҳ���ƼŬ2.bmp", 700, 400, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("ȭ����", "image/skill/ȭ����.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���ָ�", "image/skill/���ָ�.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٶ�����", "image/skill/�ٶ�����.bmp", 480, 1920, 4, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ٶ���ƼŬ", "image/skill/�ٶ���ƼŬ.bmp", 900, 750, 6, 5, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueKnightBullet", "image/skill/monsterBullet/BlueKnightBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenKnightBullet", "image/skill/monsterBullet/GreenKnightBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RedKnightBullet", "image/skill/monsterBullet/RedKnightBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueMageBullet", "image/skill/monsterBullet/BlueMageBullet.bmp", 160, 256, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenMageBullet", "image/skill/monsterBullet/GreenMageBullet.bmp", 160, 256, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RedMageBullet", "image/skill/monsterBullet/RedMageBullet.bmp", 160, 256, 5, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("BlueRogueBullet", "image/skill/monsterBullet/BlueRogueBullet.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GreenRogueBullet", "image/skill/monsterBullet/GreenRogueBullet.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("RedRogueBullet", "image/skill/monsterBullet/RedRogueBullet.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GhoulBullet", "image/skill/monsterBullet/GhoulBullet.bmp", 240, 480, 4, 8, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����������", "image/skill/bossSkill/����������.bmp", 200, 55, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ڹ���", "image/skill/bossSkill/��ڹ���.bmp", 3200, 129, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���", "image/skill/bossSkill/���.bmp", 128, 128, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȿ��", "image/skill/bossSkill/����ȿ��.bmp", 120, 40, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����ڱ�", "image/skill/bossSkill/�����ڱ�.bmp", 405, 70, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������", "image/skill/bossSkill/��������.bmp", 27, 37, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��������2", "image/skill/bossSkill/��������2.bmp", 25, 28, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���׿�", "image/skill/bossSkill/���׿�.bmp", 1020, 175, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���׿�ȿ��", "image/skill/bossSkill/���׿�ȿ��.bmp", 1419, 129, 11, 1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�ұ��", "image/skill/bossSkill/�ұ��.bmp", 200, 134, 10, 1, true, RGB(255, 0, 255));



	//========================================================================================================================//
	//==================================== MAP TOOL IMAGE && TILE, OBJECT IMAGE ==============================================//
	//========================================================================================================================//

	// ������ ��Ʈ �̹���
	IMAGEMANAGER->addImage("FONT_BOX", "image/mapTool/font/font_box.bmp", 171, 42, true, RGBMAGENTA);
	// 0 ������ ��Ʈ �̹���
	IMAGEMANAGER->addImage("FONT_PAGE0", "image/mapTool/font/font_page0.bmp", 960, 558, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_WAY", "image/mapTool/font/font_way.bmp", 61, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_WALL", "image/mapTool/font/font_wall.bmp", 72, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_OBJECT", "image/mapTool/font/font_object.bmp", 101, 23, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_SAVE", "image/mapTool/font/font_save.bmp", 66, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_LOAD", "image/mapTool/font/font_load.bmp", 69, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_MINIMAP", "image/mapTool/font/font_minimap.bmp", 124, 22, true, RGBMAGENTA);
	// �������� Ÿ��Ʋ ���� �̹���
	IMAGEMANAGER->addImage("FONT_TITLE_TILE", "image/mapTool/font/font_title_tile.bmp", 143, 57, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTO", "image/mapTool/font/font_title_auto.bmp", 190, 65, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_WAY", "image/mapTool/font/font_title_way.bmp", 155, 64, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_WALL", "image/mapTool/font/font_title_wall.bmp", 182, 64, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_OBJECT", "image/mapTool/font/font_title_object.bmp", 253, 66, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTOWAY", "image/mapTool/font/font_title_auto_way.bmp", 344, 65, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTOWALL", "image/mapTool/font/font_title_auto_wall.bmp", 350, 65, true, RGBMAGENTA);

	// �������� Ÿ�� �ڽ� �̹���
	IMAGEMANAGER->addImage("PAGE_BOX_1_1", "image/mapTool/book/view_1_1.bmp", 42, 42, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_1_2", "image/mapTool/book/view_1_2.bmp", 42, 97, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_2_1", "image/mapTool/book/view_2_1.bmp", 93, 42, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_2_2", "image/mapTool/book/view_2_2.bmp", 93, 97, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_3_2", "image/mapTool/book/view_3_2.bmp", 144, 97, true, RGBMAGENTA);

	// å ���� �̹���
	IMAGEMANAGER->addFrameImage("MINI_ICON_BOOK", "image/mapTool/book/miniIconBook.bmp", 1200, 104, 15, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("MAIN_BOOK", "image/mapTool/book/mainBook.bmp", 960, 18900, 1, 35, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("MAIN_BOOK_MARK", "image/mapTool/book/bookMark.bmp", 90, 396, true, RGBMAGENTA);


	IMAGEMANAGER->addFrameImage("MAIN_BOOK_CHANGE", "image/mapTool/book/mainBookChange.bmp", 1920, 3240, 2, 6, true, RGBMAGENTA);

	// �� Ÿ�� �̹���
	IMAGEMANAGER->addImage("TILE_BLACK", "image/mapTool/tile/tileBlack.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("TILE_BLUE", "image/mapTool/tile/tileBlue.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("TILE_RED", "image/mapTool/tile/tileRed.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("TILE_WHITE", "image/mapTool/tile/tileWhite.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);

	// ���� Ÿ�� �̹���
	IMAGEMANAGER->addFrameImage("SAMPLETILE_ICE", "image/mapTool/tile/sampleTile.bmp", 320, 224, 10, 7, false, RGBNONE);
	IMAGEMANAGER->addFrameImage("SAMPLETILE_AUTO_ICE", "image/mapTool/tile/autoTile_ice.bmp", 480, 224, 15, 7, false, RGBNONE);

	// ������Ʈ �̹���
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_1_3", "image/mapTool/object/imageObject_1_3.bmp", 384, 96, 12, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_2_2", "image/mapTool/object/imageObject_2_2.bmp", 384, 128, 6, 2, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_2_3", "image/mapTool/object/imageObject_2_3.bmp", 576, 192, 9, 2, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_2_4", "image/mapTool/object/imageObject_2_4.bmp", 384, 128, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_3_2", "image/mapTool/object/imageObject_3_2.bmp", 576, 64, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_3_4", "image/mapTool/object/imageObject_3_4.bmp", 576, 128, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_5", "image/mapTool/object/object_5.bmp", 192, 96, 6, 1, true, RGBMAGENTA);


	//============================================================//
	//======== 2018 - 07 - 06 ~ 2018 - 07 - 08 �߰� �̹��� ========//
	//============================================================//

	IMAGEMANAGER->addFrameImage("OBJECT_10", "image/mapTool/object/object_10.bmp", 320, 64, 5, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_11", "image/mapTool/object/object_11.bmp", 256, 64, 4, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_12", "image/mapTool/object/object_12.bmp", 256, 96, 4, 1, true, RGBMAGENTA);

	IMAGEMANAGER->addFrameImage("SAMPLE_TILE_AUTO_ICE", "image/mapTool/tile/tile_auto_ice.bmp", 736, 224, 23, 7, false, RGBNONE);

	// ���� Ÿ�� �̹���
	IMAGEMANAGER->addFrameImage("AUTO_TILE_IMAGE", "image/mapTool/tile/autoTile.bmp", 1088, 768, 34, 24, false, RGBNONE);
	IMAGEMANAGER->addFrameImage("AUTO_TILE_IMAGE_2", "image/mapTool/tile/autoTile_2.bmp", 384, 320, 12, 10, false, RGBNONE);

	IMAGEMANAGER->addFrameImage("FRAME_OBJECT", "image/mapTool/object/frameObject.bmp", 192, 192, 6, 3, true, RGBMAGENTA);
}

void playGround::settingAddSound(void)
{
	//================================================= MONSTER ===========================================

	SOUNDMANAGER->addSound("EnemySummon", "sound/Monster/EnemySummon.WAV", false, false);
	SOUNDMANAGER->addSound("EnemyHurt", "sound/Monster/EnemyHurt.WAV", false, false);
	SOUNDMANAGER->addSound("GhoulAttack", "sound/Monster/GhoulAttack.WAV", false, false);
	SOUNDMANAGER->addSound("KnightAttack", "sound/Monster/KnightAttack.WAV", false, false);
	SOUNDMANAGER->addSound("MageAttack", "sound/Monster/MageAttack.WAV", false, false);
	SOUNDMANAGER->addSound("MageAttackMove", "sound/Monster/MageAttackMove.WAV", false, false);
	SOUNDMANAGER->addSound("RogueAttack", "sound/Monster/RogueAttack.WAV", false, false);
	SOUNDMANAGER->addSound("GhoulDie", "sound/Monster/GhoulDie.WAV", false, false);
	SOUNDMANAGER->addSound("KnightDie", "sound/Monster/KnightDie.WAV", false, false);
	SOUNDMANAGER->addSound("EnemyDie", "sound/Monster/EnemyDie.WAV", false, false);

	//================================================= UI ================================================

	SOUNDMANAGER->addSound("MenuMove", "sound/UI/MenuMove.WAV", false, false);
	SOUNDMANAGER->addSound("MenuOpen", "sound/UI/MenuOpen.WAV", false, false);

	//================================================= BGM ===============================================

	SOUNDMANAGER->addSound("TitleScreen", "sound/BGM/TitleScreen.WAV", true, true);
	SOUNDMANAGER->addSound("MapTool", "sound/BGM/MapTool.mp3", true, true);		//�̰͸� mp3 �ФФФ� ���� ã�ҳ�
	SOUNDMANAGER->addSound("Earth", "sound/BGM/Earth.WAV", true, true);
	SOUNDMANAGER->addSound("Boss", "sound/BGM/Boss.WAV", true, true);
	SOUNDMANAGER->addSound("Ending", "sound/BGM/Ending.WAV", true, true);

	//================================================= BOSS ===============================================

	SOUNDMANAGER->addSound("firebossskill", "sound/boss/��/firebossskill.WAV", false, false);
	SOUNDMANAGER->addSound("firebossskill2", "sound/boss/��/firebossskill2.WAV", false, false);
	SOUNDMANAGER->addSound("firebossHurt", "sound/boss/��/firebossHurt.WAV", false, false);

	SOUNDMANAGER->addSound("icebossskill", "sound/boss/����/icebossskill.WAV", false, false);
	SOUNDMANAGER->addSound("icebossskillboom", "sound/boss/����/icebossskillboom.WAV", false, false);
	SOUNDMANAGER->addSound("icebossskill2", "sound/boss/����/icebossskill2.WAV", false, false);
	SOUNDMANAGER->addSound("icebossHurt", "sound/boss/����/icebossHurt.WAV", false, false);

	SOUNDMANAGER->addSound("woodbossskill", "sound/boss/����/woodbossskill.WAV", false, false);
	SOUNDMANAGER->addSound("woodbossskillboom", "sound/boss/����/woodbossskillboom.WAV", false, false);
	SOUNDMANAGER->addSound("woodbossskill2", "sound/boss/����/woodbossskill2.WAV", false, false);
	SOUNDMANAGER->addSound("woodbossHurt", "sound/boss/����/woddboosHurt.WAV", false, false);

	//================================================= PLAYER ===============================================
	SOUNDMANAGER->addSound("playerFootStep", "sound/player/playerFootStep.WAV", false, false);
	SOUNDMANAGER->addSound("playerDash", "sound/player/playerDash.WAV", false, false);
	SOUNDMANAGER->addSound("playerDead", "sound/player/playerDead.WAV", false, false);
	SOUNDMANAGER->addSound("takeItem", "sound/player/takeItem.WAV", false, false);
	SOUNDMANAGER->addSound("failTakeItem", "sound/player/failTakeItem.WAV", false, false);
	SOUNDMANAGER->addSound("dropItem", "sound/player/dropItem.WAV", false, false);
	SOUNDMANAGER->addSound("takeCoin", "sound/player/takeCoin.WAV", false, false);
	SOUNDMANAGER->addSound("openInventory", "sound/player/openInventory.WAV", false, false);

	//================================================= PLAYER SKILL =========================================
	SOUNDMANAGER->addSound("Blazing", "sound/skill/player/Blazing.WAV", false, false);
	SOUNDMANAGER->addSound("earthPunch", "sound/skill/player/earthPunch.WAV", false, false);
	SOUNDMANAGER->addSound("Fireball", "sound/skill/player/Fireball.WAV", false, false);
	SOUNDMANAGER->addSound("FlameStrike", "sound/skill/player/FlameStrike.WAV", false, false);
	SOUNDMANAGER->addSound("Tornado", "sound/skill/player/Tornado.WAV", false, false);
	SOUNDMANAGER->addSound("WindSlash", "sound/skill/player/WindSlash.WAV", false, false);

	SOUNDMANAGER->addSound("openSkillSet", "sound/player/openSkillSet.WAV", false, false);
	SOUNDMANAGER->addSound("changeSkillSet", "sound/player/changeSkillSet.WAV", false, false);
	SOUNDMANAGER->addSound("failChangeSkillSet", "sound/player/failChangeSkillSet.WAV", false, false);

}
