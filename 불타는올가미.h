#pragma once
#include "skill.h"



class ��Ÿ�¿ð��� : public skill
{
private:
	vector<PARTICLE>			vParticle;
	vector<PARTICLE>::iterator	viParticle;

	image * pImg[MAXPARTICLE];
	POINTFLOAT sword[MAXPARTICLE];
	int swordIndexX[MAXPARTICLE];
	int swordIndexY[MAXPARTICLE];
	int count;
	int count2;
	int spin;

	int indexX;
	int indexY;

	bool erase = false;
public:
	��Ÿ�¿ð���();
	~��Ÿ�¿ð���();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char* skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject);
	virtual void move();

	bool getErase() { return erase; }
};

