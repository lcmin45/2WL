#pragma once
#include "monster.h"


enum ROGUEDIRECTION
{
	ROGUE_RIGHT_STAND,
	ROGUE_LEFT_STAND,
	ROGUE_RIGHT_MOVE,
	ROGUE_LEFT_MOVE,
	ROGUE_RIGHT_ATTACK,
	ROGUE_LEFT_ATTACK,
	ROGUE_RIGHT_HIT,
	ROGUE_LEFT_HIT,
	ROGUE_RIGHT_DIE,
	ROGUE_LEFT_DIE
};

class Rogue :
	public monster
{

	ROGUEDIRECTION _RogueDirection;
	animation* _RogueMotion;

	char str[256], str2[256];


public:
	Rogue();
	~Rogue();


	virtual HRESULT init(const char* imgName, POINTFLOAT point, float speed);
	virtual void release();
	virtual void update();
	virtual void render();


	void RogueMove();

	//�ݹ� �Լ� ���
	static void rightStop(void* obj);
	static void leftStop(void* obj);

	//=====================================�׽�Ʈ��=======================
	void Test();	//�̹��� �׽�Ʈ�� �Լ� ���߿� ������
	float PX, PY;
	RECT PRC;
	//=====================================�׽�Ʈ��=======================



	//������ ���¿� ���� ������, ������
	ROGUEDIRECTION getRogueDirection() { return _RogueDirection; }
	void setRogueDirection(ROGUEDIRECTION direction) { _RogueDirection = direction; }

	animation* getRogueMotion() { return _RogueMotion; }
	void setRogueMotion(animation* ani) { _RogueMotion = ani; }

};

