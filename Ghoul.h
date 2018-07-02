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

	//콜백 함수 사용
	static void rightStop(void* obj);
	static void leftStop(void* obj);

	//=====================================테스트용=======================
	void Test();	//이미지 테스트용 함수 나중에 지우자
	float PX, PY;
	RECT PRC;
	//=====================================테스트용=======================
	


	//구울의 상태에 대한 접근자, 설정자
	GHOULDIRECTION getGhoulDirection() { return _ghoulDirection; }
	void setGhoulDirection(GHOULDIRECTION direction) { _ghoulDirection = direction; }

	animation* getGhoulMotion() { return _ghoulMotion; }
	void setGhoulMotion(animation* ani) { _ghoulMotion = ani; }
};

