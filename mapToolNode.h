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
#define MAXPAGE	8

// �̹��� ��������
#define RGBMAGENTA RGB(255, 0, 255)
#define RGBNONE RGB(0, 0, 0)

// Ư�� ��ǥ
#define WINCENTER PointMake(WINSIZEX / 2, WINSIZEY / 2)
#define ZEROPOINT PointMake(NULL, NULL)

// �������� ���Ǵ� �ڽ� ����
struct tagBox
{
	string	imageName;
	string	boxName;
	RECT	rc;
	POINT	center;
	int		imageIndex;
	int		frameX;
	int		frameY;
	int		objectIndex;
	POINT	renderPoint;
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
	OBJ_WALL
};

struct tagMapToolTile
{
	POINT			center;
	POINT			renderPoint;
	RECT			rc;
	TERRAIN			terrain;
	OBJECT			object;
	int				tileIndexX;
	int				tileIndexY;
	int				imageIndex;
	int				imageObjectIndex;
	int				objectIndex;
	int				terrainFrameX;
	int				terrainFrameY;
	tileObject*		objectClass;
	int				roomIndex;
};

struct tagTile
{
	POINT		center;
	TERRAIN		terrain;
	OBJECT		object;
	int			tileIndexX;
	int			tileIndexY;
	int			imageIndex;
	int			terrainFrameX;
	int			terrainFrameY;
	tileObject*	objectClass;
};

//==========================================================//
//==========    ���� ���õ� Ÿ�� ���� ���� �κ�     ==========//
//==========================================================//

enum currentCheck
{
	CH_TERRAIN,
	CH_IMAGE_OBJECT,
	CH_OBJECT,
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

struct tagCurrentTerrain
{
	int		imageIndex;
	int		frameX;
	int		frameY;
};

struct tagCurrentObject
{
	int		objectIndex;
	POINT	renderPoint;
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