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
	//보스 체력바
	IMAGEMANAGER->addImage("bossfrontBar", "image/boss/bossHpBarTop.bmp", 360, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("bossbackBar", "image/boss/bossHpBarBottom.bmp", 450, 60, true, RGB(255, 0, 255));

	//나무 보스 이미지
	IMAGEMANAGER->addFrameImage("나무소환", "image/boss/나무보스/나무보스소환.bmp", 0, 0, 3328, 129, 26, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무등장", "image/boss/나무보스/나무보스등장.bmp", 0, 0, 294 * 2, 58 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무점프", "image/boss/나무보스/나무보스점프.bmp", 0, 0, 420 * 2, 69 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무오른쪽", "image/boss/나무보스/나무보스오른쪽이동.bmp", 0, 0, 138 * 2, 51 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무왼쪽", "image/boss/나무보스/나무보스왼쪽이동.bmp", 0, 0, 138 * 2, 51 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무스킬", "image/boss/나무보스/나무보스스킬.bmp", 0, 0, 210 * 2, 58 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무스킬2오른쪽", "image/boss/나무보스/나무보스스킬2오른쪽.bmp", 0, 0, 387 * 2, 58 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무스킬2왼쪽", "image/boss/나무보스/나무보스스킬2왼쪽.bmp", 0, 0, 387 * 2, 58 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무오른쪽피격", "image/boss/나무보스/나무보스오른쪽피격.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무왼쪽피격", "image/boss/나무보스/나무보스왼쪽피격.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무죽음", "image/boss/나무보스/나무보스죽음.bmp", 0, 0, 34 * 2, 45 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("나무대화", "image/boss/나무보스/나무대화.bmp", 850, 200, false, RGB(0, 0, 0));

	//얼음 보스 이미지
	IMAGEMANAGER->addFrameImage("얼음소환", "image/boss/얼음보스/얼음보스소환.bmp", 0, 0, 550 * 2, 61 * 2, 11, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음등장", "image/boss/얼음보스/얼음보스등장.bmp", 0, 0, 228 * 2, 54 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음스킬", "image/boss/얼음보스/얼음보스스킬.bmp", 0, 0, 306 * 2, 52 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음스킬2", "image/boss/얼음보스/얼음보스스킬2.bmp", 0, 0, 96 * 2, 50 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음피격", "image/boss/얼음보스/얼음보스피격.bmp", 0, 0, 40 * 2, 48 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음죽음", "image/boss/얼음보스/얼음보스죽음.bmp", 0, 0, 32 * 2, 38 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("얼음대화", "image/boss/얼음보스/얼음대화.bmp", 850, 200, false, RGB(0, 0, 0));

	//불꽃 보스 이미지
	IMAGEMANAGER->addFrameImage("불소환", "image/boss/불보스/불보스소환.bmp", 0, 0, 400 * 2, 45 * 2, 8, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불등장", "image/boss/불보스/불보스등장.bmp", 0, 0, 350 * 2, 33 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불오른쪽", "image/boss/불보스/불보스오른쪽이동.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불왼쪽", "image/boss/불보스/불보스왼쪽이동.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬오른쪽", "image/boss/불보스/불보스스킬오른쪽.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬왼쪽", "image/boss/불보스/불보스스킬왼쪽.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬2", "image/boss/불보스/불보스스킬2오른쪽.bmp", 0, 0, 135 * 2, 40 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불피격", "image/boss/불보스/불보스피격.bmp", 0, 0, 42 * 2, 37 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불죽음", "image/boss/불보스/불보스죽음.bmp", 0, 0, 28 * 2, 30 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("불대화", "image/boss/불보스/불대화.bmp", 850, 200, true, RGB(255, 0, 255));

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
	IMAGEMANAGER->addImage("UI바람베기", "image/UI/바람베기.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI흙주먹", "image/UI/흙주먹.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI불꽃타격", "image/UI/불꽃타격.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI화염구", "image/UI/화염구.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI불타는올가미", "image/UI/불타는올가미.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI맹렬회오리", "image/UI/맹렬회오리.bmp", 50, 50, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("UI사이클론부메랑", "image/UI/사이클론부메랑.bmp", 50, 50, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("TitleScreen", "image/UI/TitleScreen.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleLogo", "image/UI/TitleLogo.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Black", "image/UI/Black.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PRESS ANY BUTTON", "image/UI/PRESS ANY BUTTON.bmp", 300, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GameStart", "image/UI/GameStart.bmp", 320, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Load", "image/UI/Load.bmp", 180, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MapTool", "image/UI/MapTool.bmp", 280, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Setting", "image/UI/Setting.bmp", 260, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("EXIT", "image/UI/EXIT.bmp", 150, 100, 1, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("포탈", "image/UI/포탈.bmp", 52*2, 42*2, 2, 1, true, RGB(255, 0, 255));


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

	IMAGEMANAGER->addFrameImage("불꽃타격", "image/skill/불꽃타격.bmp", 750, 600, 5, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불꽃파티클", "image/skill/불꽃파티클.bmp", 300, 200, 6, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불꽃파티클2", "image/skill/불꽃파티클2.bmp", 700, 400, 7, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("화염구", "image/skill/화염구.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("흙주먹", "image/skill/흙주먹.bmp", 2048, 256, 16, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("바람베기", "image/skill/바람베기.bmp", 480, 1920, 4, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("바람파티클", "image/skill/바람파티클.bmp", 900, 750, 6, 5, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("얼음던지기", "image/skill/bossSkill/얼음던지기.bmp", 200, 55, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("우박범위", "image/skill/bossSkill/우박범위.bmp", 3200, 129, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("우박", "image/skill/bossSkill/우박.bmp", 128, 128, 4, 4, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음효과", "image/skill/bossSkill/얼음효과.bmp", 120, 40, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무솟기", "image/skill/bossSkill/나무솟기.bmp", 405, 70, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돌던지기", "image/skill/bossSkill/돌던지기.bmp", 27, 37, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("돌던지기2", "image/skill/bossSkill/돌던지기2.bmp", 25, 28, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메테오", "image/skill/bossSkill/메테오.bmp", 1020, 175, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("메테오효과", "image/skill/bossSkill/메테오효과.bmp", 1419, 129, 11, 1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불기둥", "image/skill/bossSkill/불기둥.bmp", 200, 134, 10, 1, true, RGB(255, 0, 255));



	//========================================================================================================================//
	//==================================== MAP TOOL IMAGE && TILE, OBJECT IMAGE ==============================================//
	//========================================================================================================================//

	// 페이지 폰트 이미지
	IMAGEMANAGER->addImage("FONT_BOX", "image/mapTool/font/font_box.bmp", 171, 42, true, RGBMAGENTA);
	// 0 페이지 폰트 이미지
	IMAGEMANAGER->addImage("FONT_PAGE0", "image/mapTool/font/font_page0.bmp", 960, 558, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_WAY", "image/mapTool/font/font_way.bmp", 61, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_WALL", "image/mapTool/font/font_wall.bmp", 72, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_OBJECT", "image/mapTool/font/font_object.bmp", 101, 23, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_SAVE", "image/mapTool/font/font_save.bmp", 66, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_LOAD", "image/mapTool/font/font_load.bmp", 69, 22, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_MINIMAP", "image/mapTool/font/font_minimap.bmp", 124, 22, true, RGBMAGENTA);
	// 페이지별 타일틀 폰드 이미지
	IMAGEMANAGER->addImage("FONT_TITLE_TILE", "image/mapTool/font/font_title_tile.bmp", 143, 57, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTO", "image/mapTool/font/font_title_auto.bmp", 190, 65, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_WAY", "image/mapTool/font/font_title_way.bmp", 155, 64, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_WALL", "image/mapTool/font/font_title_wall.bmp", 182, 64, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_OBJECT", "image/mapTool/font/font_title_object.bmp", 253, 66, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTOWAY", "image/mapTool/font/font_title_auto_way.bmp", 344, 65, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTOWALL", "image/mapTool/font/font_title_auto_wall.bmp", 350, 65, true, RGBMAGENTA);

	// 페이지별 타일 박스 이미지
	IMAGEMANAGER->addImage("PAGE_BOX_1_1", "image/mapTool/book/view_1_1.bmp", 42, 42, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_1_2", "image/mapTool/book/view_1_2.bmp", 42, 97, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_2_1", "image/mapTool/book/view_2_1.bmp", 93, 42, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_2_2", "image/mapTool/book/view_2_2.bmp", 93, 97, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("PAGE_BOX_3_2", "image/mapTool/book/view_3_2.bmp", 144, 97, true, RGBMAGENTA);

	// 책 관련 이미지
	IMAGEMANAGER->addFrameImage("MINI_ICON_BOOK", "image/mapTool/book/miniIconBook.bmp", 1200, 104, 15, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("MAIN_BOOK", "image/mapTool/book/mainBook.bmp", 960, 18900, 1, 35, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("MAIN_BOOK_MARK", "image/mapTool/book/bookMark.bmp", 90, 396, true, RGBMAGENTA);


	IMAGEMANAGER->addFrameImage("MAIN_BOOK_CHANGE", "image/mapTool/book/mainBookChange.bmp", 1920, 3240, 2, 6, true, RGBMAGENTA);

	// 맵 타일 이미지
	IMAGEMANAGER->addImage("TILE_BLACK", "image/mapTool/tile/tileBlack.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("TILE_BLUE", "image/mapTool/tile/tileBlue.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("TILE_RED", "image/mapTool/tile/tileRed.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);
	IMAGEMANAGER->addImage("TILE_WHITE", "image/mapTool/tile/tileWhite.bmp", TILESIZE, TILESIZE, true, RGBMAGENTA);

	// 셈플 타일 이미지
	IMAGEMANAGER->addFrameImage("SAMPLETILE_ICE", "image/mapTool/tile/sampleTile.bmp", 320, 224, 10, 7, false, RGBNONE);
	IMAGEMANAGER->addFrameImage("SAMPLETILE_AUTO_ICE", "image/mapTool/tile/autoTile_ice.bmp", 480, 224, 15, 7, false, RGBNONE);

	// 오브젝트 이미지
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_1_3", "image/mapTool/object/imageObject_1_3.bmp", 384, 96, 12, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_2_2", "image/mapTool/object/imageObject_2_2.bmp", 384, 128, 6, 2, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_2_3", "image/mapTool/object/imageObject_2_3.bmp", 576, 192, 9, 2, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_2_4", "image/mapTool/object/imageObject_2_4.bmp", 384, 128, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_3_2", "image/mapTool/object/imageObject_3_2.bmp", 576, 64, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("IMAGE_OBJECT_3_4", "image/mapTool/object/imageObject_3_4.bmp", 576, 128, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_5", "image/mapTool/object/object_5.bmp", 192, 96, 6, 1, true, RGBMAGENTA);


	//============================================================//
	//======== 2018 - 07 - 06 ~ 2018 - 07 - 08 추가 이미지 ========//
	//============================================================//

	IMAGEMANAGER->addFrameImage("OBJECT_10", "image/mapTool/object/object_10.bmp", 320, 64, 5, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_11", "image/mapTool/object/object_11.bmp", 256, 64, 4, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_12", "image/mapTool/object/object_12.bmp", 256, 96, 4, 1, true, RGBMAGENTA);

	IMAGEMANAGER->addFrameImage("SAMPLE_TILE_AUTO_ICE", "image/mapTool/tile/tile_auto_ice.bmp", 736, 224, 23, 7, false, RGBNONE);

	// 오토 타일 이미지
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
	SOUNDMANAGER->addSound("MapTool", "sound/BGM/MapTool.mp3", true, true);		//이것만 mp3 ㅠㅠㅠㅠ 한참 찾았네
	SOUNDMANAGER->addSound("Earth", "sound/BGM/Earth.WAV", true, true);
	SOUNDMANAGER->addSound("Boss", "sound/BGM/Boss.WAV", true, true);
	SOUNDMANAGER->addSound("Ending", "sound/BGM/Ending.WAV", true, true);

	//================================================= BOSS ===============================================

	SOUNDMANAGER->addSound("firebossskill", "sound/boss/불/firebossskill.WAV", false, false);
	SOUNDMANAGER->addSound("firebossskill2", "sound/boss/불/firebossskill2.WAV", false, false);
	SOUNDMANAGER->addSound("firebossHurt", "sound/boss/불/firebossHurt.WAV", false, false);

	SOUNDMANAGER->addSound("icebossskill", "sound/boss/얼음/icebossskill.WAV", false, false);
	SOUNDMANAGER->addSound("icebossskillboom", "sound/boss/얼음/icebossskillboom.WAV", false, false);
	SOUNDMANAGER->addSound("icebossskill2", "sound/boss/얼음/icebossskill2.WAV", false, false);
	SOUNDMANAGER->addSound("icebossHurt", "sound/boss/얼음/icebossHurt.WAV", false, false);

	SOUNDMANAGER->addSound("woodbossskill", "sound/boss/나무/woodbossskill.WAV", false, false);
	SOUNDMANAGER->addSound("woodbossskillboom", "sound/boss/나무/woodbossskillboom.WAV", false, false);
	SOUNDMANAGER->addSound("woodbossskill2", "sound/boss/나무/woodbossskill2.WAV", false, false);
	SOUNDMANAGER->addSound("woodbossHurt", "sound/boss/나무/woddboosHurt.WAV", false, false);

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
