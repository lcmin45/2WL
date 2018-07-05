#pragma once
#include "monster.h"
#include "Astar.h"

class player;

enum GHOULDIRECTION
{
	GHOUL_RIGHT_STAND,
	GHOUL_LEFT_STAND,
	GHOUL_RIGHT_MOVE,
	GHOUL_LEFT_MOVE,
	GHOUL_RIGHT_ATTACK,
	GHOUL_LEFT_ATTACK,
	GHOUL_RIGHT_HIT,
	GHOUL_LEFT_HIT,
	GHOUL_RIGHT_DIE,
	GHOUL_LEFT_DIE
};


class Ghoul : public monster
{
	GHOULDIRECTION _ghoulDirection;
	animation* _ghoulMotion;
	Astar* _Astar;

public:
	Ghoul();
	~Ghoul();
	
	virtual HRESULT init(POINTFLOAT point, int index);
	virtual void release();
	virtual void update();
	virtual void render();


	void ghoulMove();
	inline void HitHP(float att) { _monsterHP -= att; }
	inline float getHP() { return _monsterHP; }

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);
	static void summonOn(void * obj);

	//=====================================�׽�Ʈ��=======================
	void Test();	//�̹��� �׽�Ʈ�� �Լ� ���߿� ������
	float PX, PY;
	RECT PRC;
	//=====================================�׽�Ʈ��=======================
	


	//������ ���¿� ���� ������, ������
	void setImage(image* img) { _image = img; }
	void setForm(MONSTERFORM form) { _form = form; }

	GHOULDIRECTION getGhoulDirection() { return _ghoulDirection; }
	void setGhoulDirection(GHOULDIRECTION direction) { _ghoulDirection = direction; }

	animation* getGhoulMotion() { return _ghoulMotion; }
	void setGhoulMotion(animation* ani) { _ghoulMotion = ani; }
};

