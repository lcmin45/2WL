#pragma once
#include "monster.h"

class player;

enum GHOULDIRECTION
{
	GHOUL_RIGHT_STAND,
	GHOUL_LEFT_STAND,
	GHOUL_RIGHT_MOVE,
	GHOUL_LEFT_MOVE,
	GHOUL_RIGHT_ATTACK,
	GHOUL_LEFT_ATTACK,
	GHOUL_RIGHT_HIT,
	GHOUL_LEFT_HIT,
	GHOUL_RIGHT_DIE,
	GHOUL_LEFT_DIE
};


class Ghoul : public monster
{
public:
	Ghoul();
	~Ghoul();

	GHOULDIRECTION _ghoulDirection;
	animation* _ghoulMotion;

	image* _image;
	float _x, _y;
	float _attackRange;
	RECT _rc;
	float _angle;
	float _speed;


	virtual HRESULT init(POINTFLOAT point, float speed);
	virtual void release();
	virtual void update();
	virtual void render();


	void ghoulMove();

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);

	//=====================================�׽�Ʈ��=======================
	void Test();	//�̹��� �׽�Ʈ�� �Լ� ���߿� ������
	float PX, PY;
	RECT PRC;
	//=====================================�׽�Ʈ��=======================
	


	//������ ���¿� ���� ������, ������
	GHOULDIRECTION getGhoulDirection() { return _ghoulDirection; }
	void setGhoulDirection(GHOULDIRECTION direction) { _ghoulDirection = direction; }

	animation* getGhoulMotion() { return _ghoulMotion; }
	void setGhoulMotion(animation* ani) { _ghoulMotion = ani; }
};

