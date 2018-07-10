#pragma once
#include "monster.h"
#include "Astar.h"


class Mage :
	public monster
{

public:
	Mage();
	~Mage();
	

	virtual HRESULT init(const char* imgName, POINTFLOAT point, int monsterRoomIndex);
	virtual void release();
	virtual void update();
	virtual void render();


	void MageMove();

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);
	static void MonsterDie(void*obj);
	

	void Test();

};

