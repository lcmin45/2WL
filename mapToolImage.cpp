#include "stdafx.h"
#include "mapTool.h"

void mapTool::imageInit(void)
{
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
	IMAGEMANAGER->addFrameImage("OBJECT_CANDLE", "image/mapTool/object1.bmp", 60, 34, 6, 1, true, RGBMAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_5", "image/mapTool/object/object_5.bmp", 192, 96, 6, 1, true, RGBMAGENTA);
}