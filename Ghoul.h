#pragma once
#include "monster.h"


class Ghoul : public monster
{

public:
	Ghoul();
	~Ghoul();
	
	virtual HRESULT init(POINTFLOAT point,int monsterRoomIndex, int key);
	virtual void release();
	virtual void update();
	virtual void render();

	void ghoulMove();
	


	//콜백 함수 사용
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);
	static void MonsterDie(void*obj);

	void Test();	
	

	void HitMotion();
	void Die();
};

