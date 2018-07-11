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

	void HitMotion();
	

	//상태에 대한 접근자, 설정자
	SCARECROWDIRECTION getScarecrowDirection() { return _scarecrowDirection; }
	void setScarecrowDirection(SCARECROWDIRECTION direction) { _scarecrowDirection = direction; }

	animation* getScarecrowMotion() { return _scarecrowMotion; }
	void setScarecrowMotion(animation* ani) { _scarecrowMotion = ani; }


};

