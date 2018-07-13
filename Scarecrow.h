#pragma once
#include "monster.h"



enum SCARECROWDIRECTION		//����ƺ� ����
{
	SCARECROW_STAND,
	SCARECROW_HIT
};

class Scarecrow :
	public monster
{

	SCARECROWDIRECTION	_scarecrowDirection;		//����Ϻ� ����
	animation*			_scarecrowMotion;			//����ƺ� ���

public:
	Scarecrow();
	~Scarecrow();


	virtual HRESULT init(POINTFLOAT point);
	virtual void release();
	virtual void update();
	virtual void render();

	void HitMotion();
	

	//���¿� ���� ������, ������
	inline SCARECROWDIRECTION getScarecrowDirection()					{ return _scarecrowDirection; }
	inline animation* getScarecrowMotion()								{ return _scarecrowMotion; }
	inline void setScarecrowDirection	(SCARECROWDIRECTION direction)	{ _scarecrowDirection = direction; }
	inline void setScarecrowMotion		(animation* ani)				{ _scarecrowMotion = ani; }


};

