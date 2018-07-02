#pragma once

#define TILESIZE 16

struct tagTile
{
	int		imageindex;
	POINT	centerPoint;
	RECT	rc;
	int		terrainFrameX;
	int		terrainFrameY;
	int		objFrameX;
	int		objFrameY;


};