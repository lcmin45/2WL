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

//==========================================================//
//==========    ���� ���õ� Ÿ�� ���� ���� �κ�     ==========//
//==========================================================//

enum currentCheck
{
	CH_TERRAIN,
	CH_OBJECT,
	CH_AUTO
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
	int		imageIndex;
	POINT	startPoint;
	POINT	endPoint;
};

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
	POINT		center;
	POINT		renderPoint;
	RECT		rc;
	TERRAIN		terrain;
	OBJECT		object;
	int			tileIndexX;
	int			tileIndexY;
	int			imageIndex;
	int			terrainFrameX;
	int			terrainFrameY;
	int			objectIndex;
	tileObject*	objectClass;
};

struct tagTile
{
	image*		img;
	TERRAIN		terrain;
	OBJECT		object;
	int			tileIndexX;
	int			tileIndexY;
	int			imageIndex;
	int			terrainFrameX;
	int			terrainFrameY;
	tileObject*	objectClass;
};