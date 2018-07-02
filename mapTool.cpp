#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool() {}

mapTool::~mapTool() {}


HRESULT mapTool::init(void)
{
	imageInit();

	_mapTile = new mapTile;
	_mapTile->init();

	_book = new mapToolBook;
	_book->init();	

	_moveSpeed = 10;

	_book->setMapTileClass(_mapTile);

	return S_OK;
}

void mapTool::release(void)
{
	_mapTile->release();
	_book->release();	
}

void mapTool::update(void)
{
	KEYANIMANAGER->update();
	_mapTile->setIsMouseBook(_book->getIsMouseBook());
	_mapTile->update();
	_book->update();

	if (_book->getIsMoveBook()) return;

	if (KEYMANAGER->isStayKeyDown('W')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y - _moveSpeed });

	if (KEYMANAGER->isStayKeyDown('A')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x - _moveSpeed, CAMERAMANAGER->getCameraPoint().y });

	if (KEYMANAGER->isStayKeyDown('S')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x, CAMERAMANAGER->getCameraPoint().y + _moveSpeed });

	if (KEYMANAGER->isStayKeyDown('D')) CAMERAMANAGER->setCameraPoint({ CAMERAMANAGER->getCameraPoint().x + _moveSpeed, CAMERAMANAGER->getCameraPoint().y });
}

void mapTool::render(void)
{
	_mapTile->render();
	_book->render();
}

void mapTool::imageInit(void)
{
	// 타일 이미지
	IMAGEMANAGER->addFrameImage("SAMPLETILE_ICE", "image/mapTool/sampleTile.bmp", 320, 224, 10, 7, false, RGB(0, 0, 0));
	IMAGEMANAGER->addFrameImage("SAMPLETILE_AUTO_ICE", "image/mapTool/tile/autoTile_ice.bmp", 480, 224, 15, 7, false, RGB(0, 0, 0));

	// 오브젝트 이미지
	IMAGEMANAGER->addFrameImage("OBJECT_CANDLE", "image/mapTool/object1.bmp", 60, 34, 6, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage("OBJECT_5", "image/mapTool/object5.bmp", 192, 96, 6, 1, true, MAGENTA);

	// 폰트 이미지
	IMAGEMANAGER->addImage("FONT_PAGE0",			"image/mapTool/font/font_page0.bmp", 960, 558, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_WAY",				"image/mapTool/font/font_way.bmp", 61, 22, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_WALL",				"image/mapTool/font/font_wall.bmp", 72, 22, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_OBJECT",			"image/mapTool/font/font_object.bmp", 101, 23, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_SAVE",				"image/mapTool/font/font_save.bmp", 66, 22, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_LOAD",				"image/mapTool/font/font_load.bmp", 69, 22, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_MINIMAP",			"image/mapTool/font/font_minimap.bmp", 124, 22, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_WAY",		"image/mapTool/font/font_title_way.bmp", 155, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_WALL",		"image/mapTool/font/font_title_wall.bmp", 182, 64, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_OBJECT",		"image/mapTool/font/font_title_object.bmp", 253, 66, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTOWAY",	"image/mapTool/font/font_title_auto_way.bmp", 344, 65, true, MAGENTA);
	//IMAGEMANAGER->addImage("FONT_TITLE_AUTOWALL",	"image/mapTool/font/font_title_auto_wall.bmp", 371, 65, true, MAGENTA);
	IMAGEMANAGER->addImage("FONT_TITLE_AUTOWALL", "image/mapTool/font/font_title_auto_wall.bmp", 350, 65, true, MAGENTA);
}