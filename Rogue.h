#pragma once
#include "monster.h"
#include "Astar.h"



class Rogue :
	public monster
{


public:
	Rogue();
	~Rogue();


	virtual HRESULT init(const char* imgName, POINTFLOAT point, int monsterRoomIndex);
	virtual void release();
	virtual void update();
	virtual void render();


	void RogueMove();

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);
	static void MonsterDie(void*obj);
	

	void Test();

	
};

