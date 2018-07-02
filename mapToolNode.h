#pragma once

// å ���� ������
#define BOOKSIZEX 712
#define BOOKSIZEY 484

// å ������ �ִ밪
#define MAXPAGE	8

#define WINCENTER PointMake(WINSIZEX / 2, WINSIZEY / 2)
#define ZEROPOINT PointMake(NULL, NULL)


struct tagBox 
{
	image*	baseImg;
	RECT	rc;
	POINT	center;
	int		imageIndex;
	int		frameX;
	int		frameY;
	int		objectIndex;
	POINT	renderPoint;
};