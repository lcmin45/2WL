#pragma once
#include "gameNode.h"

enum MONDIRECTION	{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
enum MONSTERFORM	{ CARD, SUMMOM, BATTLE };

class monster : public gameNode
{

protected:

	MONDIRECTION _dir;
	MONSTERFORM _form;
	image * _image;
	POINTFLOAT _position;
	POINTFLOAT _bottomPosition;
	//float _x, _y;
	//float _bottomX, _bottomY;
	float _attackRange;
	float _monsterHP;
	RECT _rc;
	RECT _Zrc;
	float _angle;
	float _speed;
	char _motionName1[128];
	char _motionName2[128];
	char _motionName3[128];
	char _motionName4[128];
	char _motionName5[128];
	char str[256];
	int _timecnt;

public:
	monster();
	~monster();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};