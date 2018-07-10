#pragma once
#include "monster.h"
#include "Astar.h"


class Knight :
	public monster
{

public:
	Knight();
	~Knight();


	virtual HRESULT init(const char* imgName, POINTFLOAT point,int index, int monsterRoomIndex);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void KnightMove();

	//콜백 함수 사용
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);
	static void MonsterDie(void*obj);

	void Test();

};

