#pragma once
#include "gameNode.h"

enum MONSTERFORM
{
	CARD,
	SUMMOM,
	BATTLE


};

class monster : public gameNode
{

protected:

	MONSTERFORM _form;
	image * _image;
	float _x, _y;
	float _bottomX, _bottomY;
	float _attackRange;
	RECT _rc;
	RECT _Zrc;
	float _angle;
	float _speed;

public:
	monster();
	~monster();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};