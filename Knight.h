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
public:
	Knight();
	~Knight();



	KNIGHTDIRECTION _KnightDirection;
	animation* _KnightMotion;

	char str[256], str2[256];

	image* _image;
	float _x, _y;
	float _attackRange;
	RECT _rc;
	float _angle;
	float _speed;


	virtual HRESULT init(const char* imgName, POINTFLOAT point, float speed);
	virtual void release();
	virtual void update();
	virtual void render();


	void KnightMove();

	//콜백 함수 사용
	static void rightStop(void* obj);
	static void leftStop(void* obj);

	//=====================================테스트용=======================
	void Test();	//이미지 테스트용 함수 나중에 지우자
	float PX, PY;
	RECT PRC;
	//=====================================테스트용=======================



	//구울의 상태에 대한 접근자, 설정자
	KNIGHTDIRECTION getKnightDirection() { return _KnightDirection; }
	void setKnightDirection(KNIGHTDIRECTION direction) { _KnightDirection = direction; }

	animation* getKnightMotion() { return _KnightMotion; }
	void setKnightMotion(animation* ani) { _KnightMotion = ani; }
};

