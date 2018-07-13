#pragma once
#include "monster.h"



enum SCARECROWDIRECTION		//허수아비 상태
{
	SCARECROW_STAND,
	SCARECROW_HIT
};

class Scarecrow :
	public monster
{

	SCARECROWDIRECTION	_scarecrowDirection;		//허수하비 방향
	animation*			_scarecrowMotion;			//허수아비 모션

public:
	Scarecrow();
	~Scarecrow();


	virtual HRESULT init(POINTFLOAT point);
	virtual void release();
	virtual void update();
	virtual void render();

	void HitMotion();
	

	//상태에 대한 접근자, 설정자
	inline SCARECROWDIRECTION getScarecrowDirection()					{ return _scarecrowDirection; }
	inline animation* getScarecrowMotion()								{ return _scarecrowMotion; }
	inline void setScarecrowDirection	(SCARECROWDIRECTION direction)	{ _scarecrowDirection = direction; }
	inline void setScarecrowMotion		(animation* ani)				{ _scarecrowMotion = ani; }


};

