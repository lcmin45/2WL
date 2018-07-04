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
#define MAXPAGE	8

// 이미지 색상정보
#define RGBMAGENTA RGB(255, 0, 255)
#define RGBNONE RGB(0, 0, 0)

// 특정 좌표
#define WINCENTER PointMake(WINSIZEX / 2, WINSIZEY / 2)
#define ZEROPOINT PointMake(NULL, NULL)

// 페이지에 사용되는 박스 정보
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
//==========    현재 선택된 타일 정보 관련 부분     ==========//
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
//==========    맵에 사용될 타일 정보 관련 부분     ==========//
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