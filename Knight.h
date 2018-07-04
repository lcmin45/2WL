#pragma once
#include "monster.h"


enum KNIGHTDIRECTION
{
	KNIGHT_RIGHT_STAND,
	KNIGHT_LEFT_STAND,
	KNIGHT_RIGHT_MOVE,
	KNIGHT_LEFT_MOVE,
	KNIGHT_RIGHT_ATTACK,
	KNIGHT_LEFT_ATTACK,
	KNIGHT_RIGHT_HIT,
	KNIGHT_LEFT_HIT,
	KNIGHT_RIGHT_DIE,
	KNIGHT_LEFT_DIE
};


class Knight :
	public monster
{
	KNIGHTDIRECTION _KnightDirection;
	animation* _KnightMotion;

	char str[256], str2[256];


public:
	Knight();
	~Knight();




	virtual HRESULT init(const char* imgName, POINTFLOAT point, float speed);
	virtual void release();
	virtual void update();
	virtual void render();


	void KnightMove();

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);

	//=====================================�׽�Ʈ��=======================
	void Test();	//�̹��� �׽�Ʈ�� �Լ� ���߿� ������
	float PX, PY;
	RECT PRC;
	//=====================================�׽�Ʈ��=======================



	//������ ���¿� ���� ������, ������
	KNIGHTDIRECTION getKnightDirection() { return _KnightDirection; }
	void setKnightDirection(KNIGHTDIRECTION direction) { _KnightDirection = direction; }

	animation* getKnightMotion() { return _KnightMotion; }
	void setKnightMotion(animation* ani) { _KnightMotion = ani; }
};

