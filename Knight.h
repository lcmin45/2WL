#pragma once
#include "monster.h"
#include "Astar.h"


class Knight :
	public monster
{

public:
	Knight();
	~Knight();


	virtual HRESULT init(const char* imgName, POINTFLOAT point, int monsterRoomIndex, int key);
	virtual void release();
	virtual void update();
	virtual void render();
	
	void KnightMove();

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);
	static void MonsterDie(void*obj);

	void Test();

	void HitMotion();
	void Die();
};

