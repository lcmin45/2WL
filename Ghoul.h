#pragma once
#include "monster.h"


class Ghoul : public monster
{

public:
	Ghoul();
	~Ghoul();
	
	virtual HRESULT init(POINTFLOAT point, int index,int monsterRoomIndex);
	virtual void release();
	virtual void update();
	virtual void render();

	void ghoulMove();
	


	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);

	void Test();	
	
	
};

