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


	//if (KEYMANAGER->isOnceKeyDown(VK_F5))
	//{
	//	SCENEMANAGER->changeScene("mapTool");
	//}
	//
	//if (KEYMANAGER->isOnceKeyDown(VK_F6))
	//{
	//	SCENEMANAGER->changeScene("inGame");
	//}
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
	//나무 보스 이미지
	IMAGEMANAGER->addFrameImage("나무소환", "image/boss/나무보스/나무보스소환.bmp", 0, 0, 3200, 129, 25, 1, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addFrameImage("얼음소환", "image/boss/얼음보스/얼음보스소환.bmp", 0, 0, 500 * 2, 61 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음등장", "image/boss/얼음보스/얼음보스등장.bmp", 0, 0, 228 * 2, 54 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음스킬", "image/boss/얼음보스/얼음보스스킬.bmp", 0, 0, 306 * 2, 52 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음스킬2", "image/boss/얼음보스/얼음보스스킬2.bmp", 0, 0, 96 * 2, 50 * 2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음피격", "image/boss/얼음보스/얼음보스피격.bmp", 0, 0, 40 * 2, 48 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음죽음", "image/boss/얼음보스/얼음보스죽음.bmp", 0, 0, 32 * 2, 38 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("얼음대화", "image/boss/얼음보스/얼음대화.bmp", 850, 200, false, RGB(0, 0, 0));

	//불꽃 보스 이미지
	IMAGEMANAGER->addFrameImage("불소환", "image/boss/불보스/불보스소환.bmp", 0, 0, 350 * 2, 45 * 2, 7, 1, true, RGB(255, 0, 255));
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
	IMAGEMANAGER->addImage("buttonF", "image/UI/buttonF.bmp", 40, 40, true, RGB(255, 0, 255));

	IMAGEMANAGER->addImage("TitleScreen", "image/UI/TitleScreen.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleLogo", "image/UI/TitleLogo.bmp", 1200, 900, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("PRESS ANY BUTTON", "image/UI/PRESS ANY BUTTON.bmp", 300, 20, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("GameStart", "image/UI/GameStart.bmp", 320, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Load", "image/UI/Load.bmp", 180, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("MapTool", "image/UI/MapTool.bmp", 280, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Setting", "image/UI/Setting.bmp", 260, 100, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("EXIT", "image/UI/EXIT.bmp", 150, 100, 1, 2, true, RGB(255, 0, 255));


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
	IMAGEMANAGER->addImage("MAIN_BOOK_MARK", "image/mapTool/book/mainBookMark.bmp", 90, 324, true, RGBMAGENTA);
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
	IMAGEMANAGER->addFrameImage("OBJECT_CANDLE", "image/mapTool/object/object1.bmp", 60, 34, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_5", "image/mapTool/object/object_5.bmp", 192, 96, 6, 1, true, RGBMAGENTA);


	//============================================================//
	//======== 2018 - 07 - 06 ~ 2018 - 07 - 08 추가 이미지 ========//
	//============================================================//

	IMAGEMANAGER->addFrameImage("OBJECT_10", "image/mapTool/object/object_10.bmp", 320, 64, 5, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_11", "image/mapTool/object/object_11.bmp", 256, 64, 4, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBEJCT_12", "image/mapTool/object/object_12.bmp", 256, 96, 4, 1, true, RGBMAGENTA);

	IMAGEMANAGER->addFrameImage("SAMPLE_TILE_AUTO_ICE", "image/mapTool/tile/tile_auto_ice.bmp", 736, 224, 23, 7, false, RGBMAGENTA);
}