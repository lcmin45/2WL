#pragma once
#include "tileObject.h"
// ∞¢ ≈∏¿œ∫∞ ªÁ¿Ã¡Ó
#define TILESIZE 32

// √— ∏ ¿« ≈∏¿œ ∞πºˆ
#define MAXTILEX 500
#define MAXTILEY 500

#define MAGENTA RGB(255, 0, 255)

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
	image*	img;
	image*	boxImage;
	image*	checkImage;
	POINT	center;
	RECT	rc;	
	TERRAIN terrain;
	OBJECT	object;
	int		tileIndexX;
	int		tileIndexY;
	int		imageIndex;
	int		terrainFrameX;
	int		terrainFrameY;
	int		objectIndex;
	int		objectFrameX;
	int		objectFrameY;
	bool	isCheck;
	tileObject* objectClass;
};

struct tagTile
{
	image*	img;
	TERRAIN terrain;
	OBJECT	object;
	int		tileIndexX;
	int		tileIndexY;
	int		terrainFrameX;
	int		terrainFrameY;
	int		objectFrameX;
	int		objectFrameY;
};