#pragma once
#include "tileObject.h"

// �� Ÿ�Ϻ� ������
#define TILESIZE 32

// �� ���� Ÿ�� ����
#define MAXTILEX 200
#define MAXTILEY 200

// å ���� ������
#define BOOKSIZEX 712
#define BOOKSIZEY 484

// å ������ �ִ밪
#define MAXPAGE	10

// �̹��� ��������
#define RGBMAGENTA RGB(255, 0, 255)
#define RGBNONE RGB(0, 0, 0)

// Ư�� ��ǥ
#define WINCENTER PointMake(WINSIZEX / 2, WINSIZEY / 2)
#define ZEROPOINT PointMake(NULL, NULL)

#define ASTARSIZESTARTX4 88
#define ASTARSIZESTARTY4 116
#define ASTARSIZEENDX4 120
#define ASTARSIZEENDY4 132
#define ASTARSIZEX4 32
#define ASTARSIZEY4 16

#define ASTARSIZESTARTX5 39
#define ASTARSIZESTARTY5 79
#define ASTARSIZEENDX5 56
#define ASTARSIZEENDY5 105
#define ASTARSIZEX5 17
#define ASTARSIZEY5 26

#define ASTARSIZESTARTX6 93
#define ASTARSIZESTARTY6 41
#define ASTARSIZEENDX6 119
#define ASTARSIZEENDY6 63
#define ASTARSIZEX6 26
#define ASTARSIZEY6 22

#define ASTARSIZESTARTX7 140
#define ASTARSIZESTARTY7 81
#define ASTARSIZEENDX7 176
#define ASTARSIZEENDY7 105
#define ASTARSIZEX7 36
#define ASTARSIZEY7 24

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

// �������� ���Ǵ� �ڽ� ����
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
//==========    �ʿ� ���� Ÿ�� ���� ���� �κ�     ==========//
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
//==========    ���� ���õ� Ÿ�� ���� ���� �κ�     ==========//
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
