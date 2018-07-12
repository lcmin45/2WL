#pragma once
#include "tileObject.h"

// 각 타일별 사이즈
#define TILESIZE 32

// 총 맵의 타일 갯수
#define MAXTILEX 200
#define MAXTILEY 200

// 책 내부 사이즈
#define BOOKSIZEX 712
#define BOOKSIZEY 484

// 책 페이지 최대값
#define MAXPAGE	10

// 이미지 색상정보
#define RGBMAGENTA RGB(255, 0, 255)
#define RGBNONE RGB(0, 0, 0)

// 특정 좌표
#define WINCENTER PointMake(WINSIZEX / 2, WINSIZEY / 2)
#define ZEROPOINT PointMake(NULL, NULL)

#define ASTARSIZESTARTX4 87
#define ASTARSIZESTARTY4 115
#define ASTARSIZEENDX4 121
#define ASTARSIZEENDY4 133
#define ASTARSIZEX4 34
#define ASTARSIZEY4 18

#define ASTARSIZESTARTX5 38
#define ASTARSIZESTARTY5 80
#define ASTARSIZEENDX5 57
#define ASTARSIZEENDY5 106
#define ASTARSIZEX5 19
#define ASTARSIZEY5 28

#define ASTARSIZESTARTX6 92
#define ASTARSIZESTARTY6 40
#define ASTARSIZEENDX6 120
#define ASTARSIZEENDY6 64
#define ASTARSIZEX6 28
#define ASTARSIZEY6 24

#define ASTARSIZESTARTX7 139
#define ASTARSIZESTARTY7 80
#define ASTARSIZEENDX7 177
#define ASTARSIZEENDY7 106
#define ASTARSIZEX7 38
#define ASTARSIZEY7 26

enum TERRAIN
{
	TR_NONE,
	TR_WAY,
	TR_WALL
};

enum OBJECT
{
	OBJ_NONE,
	OBJ_ATTACK,
	OBJ_WAY,
	OBJ_WALL,
	OBJ_FALL
};

enum OBJECTSETPOINT
{
	LEFT_TOP,
	LEFT_BOTTOM
};

enum currentCheck
{
	CH_TERRAIN,
	CH_IMAGE_OBJECT,
	CH_OBJECT,
	CH_OBJECT_IMAGE,
	CH_AUTO_WAY,
	CH_AUTO_WALL,
	CH_AUTO,
	CH_AUTO_DELETE_WAY,
	CH_AUTO_DELETE_WALL,
	CH_AUTO_DELETE_OBJECT,
	CH_ROOM_INDEX
};

enum AUTOCHECK
{
	AUTO_NONE,
	AUTO_ALL,
	AUTO_UP_DOWN
};

enum ERASER
{
	ER_NONE,
	ER_WAY,
	ER_WALL,
	ER_OBJ
};

// 페이지에 사용되는 박스 정보
struct tagBox
{
	string			boxImageName;
	string			tileImageName;
	string			objectImageName;
	int				imageObjectIndex;
	RECT			rc;
	int				frameX, frameY;
	OBJECTSETPOINT	objectSetPoint;
	POINT			objectCheckSize;
	POINT			center;
	int				imageIndex;
	POINT			startPoint;
	POINT			endPoint;
	AUTOCHECK		autoCheck;
	image*			autoTileImg;
	TERRAIN			terrain;
	int				objectIndex;
	POINT			renderPoint;
};

#define CAMERADC		CAMERAMANAGER->getCameraDC()
#define CAMERASTARTY	(CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2) / TILESIZE
#define CAMERAENDY		(CAMERAMANAGER->getCameraPoint().y + WINSIZEY / 2) / TILESIZE + 1
#define CAMERASTARTX	(CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2) / TILESIZE
#define CAMERAENDX		(CAMERAMANAGER->getCameraPoint().x + WINSIZEX / 2) / TILESIZE + 1
#define CAMERAMAXCHECK	i >= MAXTILEY || j >= MAXTILEX

//==========================================================//
//==========    맵에 사용될 타일 정보 관련 부분     ==========//
//==========================================================//

struct tagMapToolTile
{
	POINT			center;
	POINT			renderPoint;
	OBJECTSETPOINT	objectSetPoint;
	POINT			objectCheckSize;
	RECT			rc;
	TERRAIN			terrain;
	TERRAIN			objectTerrain;
	OBJECT			object;
	int				tileIndexX;
	int				tileIndexY;
	int				imageIndex;
	int				imageObjectIndex;
	int				objectIndex;
	int				terrainFrameX;
	int				terrainFrameY;
	int				imageObjectFrameX;
	int				imageObjectFrameY;
	tileObject*		objectClass;
	int				roomIndex;
};

struct tagTile
{
	POINT		center;
	TERRAIN		terrain;
	OBJECT		object;
	int			imageIndex;
	int			tileIndexX;
	int			tileIndexY;
	int			terrainFrameX;
	int			terrainFrameY;
	tileObject*	objectClass;
};

//==========================================================//
//==========    현재 선택된 타일 정보 관련 부분     ==========//
//==========================================================//

struct tagCurrentTerrain
{
	int		imageIndex;
	int		frameX;
	int		frameY;
};

struct tagCurrentObject
{
	string			imageName;
	int				imageObjectIndex;
	int				frameX;
	int				frameY;
	OBJECTSETPOINT	objectSetpoint;
	POINT			objectCheckSize;
	TERRAIN			terrain;
	int				objectIndex;
	POINT			renderPoint;
};

struct tagCurrentAuto
{
	int			imageIndex;
	POINT		startPoint;
	POINT		endPoint;
	AUTOCHECK	autoCheck;
	TERRAIN		terrain;
	int			roomIndex;
};
