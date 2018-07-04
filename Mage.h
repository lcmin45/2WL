#pragma once
#include "monster.h"


enum MAGEDIRECTION
{
	MAGE_RIGHT_STAND,
	MAGE_LEFT_STAND,
	MAGE_RIGHT_MOVE,
	MAGE_LEFT_MOVE,
	MAGE_RIGHT_ATTACK,
	MAGE_LEFT_ATTACK,
	MAGE_RIGHT_HIT,
	MAGE_LEFT_HIT,
	MAGE_RIGHT_DIE,
	MAGE_LEFT_DIE
};


class Mage :
	public monster
{
	MAGEDIRECTION _MageDirection;
	animation* _MageMotion;

	char str[256], str2[256];

public:
	Mage();
	~Mage();
	

	virtual HRESULT init(const char* imgName, POINTFLOAT point, float speed);
	virtual void release();
	virtual void update();
	virtual void render();


	void MageMove();

	//콜백 함수 사용
	static void rightStop(void* obj);
	static void leftStop(void* obj);

	//=====================================테스트용=======================
	void Test();	//이미지 테스트용 함수 나중에 지우자
	float PX, PY;
	RECT PRC;
	//=====================================테스트용=======================



	//구울의 상태에 대한 접근자, 설정자
	MAGEDIRECTION getMageDirection() { return _MageDirection; }
	void setMageDirection(MAGEDIRECTION direction) { _MageDirection = direction; }

	animation* getMageMotion() { return _MageMotion; }
	void setMageMotion(animation* ani) { _MageMotion = ani; }
};

