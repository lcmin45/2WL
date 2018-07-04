#pragma once
#include "monster.h"



enum SCARECROWDIRECTION
{
	SCARECROW_STAND,
	SCARECROW_HIT
};




class Scarecrow :
	public monster
{

	SCARECROWDIRECTION _scarecrowDirection;
	animation* _scarecrowMotion;


public:
	Scarecrow();
	~Scarecrow();


	virtual HRESULT init(POINTFLOAT point);
	virtual void release();
	virtual void update();
	virtual void render();


	//=====================================테스트용=======================
	void Test();	//이미지 테스트용 함수 나중에 지우자
	float PX, PY;
	RECT PRC;
	//=====================================테스트용=======================



	//구울의 상태에 대한 접근자, 설정자
	SCARECROWDIRECTION getScarecrowDirection() { return _scarecrowDirection; }
	void setScarecrowDirection(SCARECROWDIRECTION direction) { _scarecrowDirection = direction; }

	animation* getScarecrowMotion() { return _scarecrowMotion; }
	void setScarecrowMotion(animation* ani) { _scarecrowMotion = ani; }


};

