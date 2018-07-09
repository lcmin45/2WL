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
	


	//콜백 함수 사용
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);

	void Test();	
	
	
};

