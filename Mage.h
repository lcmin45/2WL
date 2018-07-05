#pragma once
#include "monster.h"
#include "Astar.h"


enum MAGEDIRECTION
{
	MAGE_RIGHT_STAND,
	MAGE_LEFT_STAND,
	MAGE_RIGHT_MOVE,
	MAGE_LEFT_MOVE,
	MAGE_RIGHT_ATTACK,
	MAGE_LEFT_ATTACK,
	MAGE_RIGHT_HIT,
	MAGE_LEFT_HIT,
	MAGE_RIGHT_DIE,
	MAGE_LEFT_DIE
};


class Mage :
	public monster
{
	MAGEDIRECTION _MageDirection;
	animation* _MageMotion;


public:
	Mage();
	~Mage();
	

	virtual HRESULT init(const char* imgName, POINTFLOAT point,int index);
	virtual void release();
	virtual void update();
	virtual void render();


	void MageMove();
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



	// ���¿� ���� ������, ������
	char getImageName() { return str[256]; }

	void setImage(image* img) { _image = img; }
	void setForm(MONSTERFORM form) { _form = form; }

	MAGEDIRECTION getMageDirection() { return _MageDirection; }
	void setMageDirection(MAGEDIRECTION direction) { _MageDirection = direction; }

	animation* getMageMotion() { return _MageMotion; }
	void setMageMotion(animation* ani) { _MageMotion = ani; }
};

