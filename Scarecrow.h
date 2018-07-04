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


	//=====================================�׽�Ʈ��=======================
	void Test();	//�̹��� �׽�Ʈ�� �Լ� ���߿� ������
	float PX, PY;
	RECT PRC;
	//=====================================�׽�Ʈ��=======================



	//������ ���¿� ���� ������, ������
	SCARECROWDIRECTION getScarecrowDirection() { return _scarecrowDirection; }
	void setScarecrowDirection(SCARECROWDIRECTION direction) { _scarecrowDirection = direction; }

	animation* getScarecrowMotion() { return _scarecrowMotion; }
	void setScarecrowMotion(animation* ani) { _scarecrowMotion = ani; }


};

