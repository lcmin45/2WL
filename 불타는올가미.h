#pragma once
#include "skill.h"

#define MAXPARTICLE 5

struct PARTICLE 
{
	image* img;
	POINTFLOAT pt;
	RECT rc;
	int index;
};

class 불타는올가미 : public skill
{
private:
	vector<PARTICLE>			vParticle;
	vector<PARTICLE>::iterator	viParticle;

	image * pImg[MAXPARTICLE];
	POINTFLOAT sword[MAXPARTICLE];
	RECT sRect[MAXPARTICLE];
	int swordIndex[MAXPARTICLE];
	int count;
	int count2;
	int spin;

	bool erase = false;
public:
	불타는올가미();
	~불타는올가미();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char* skillName, int amount, POINTFLOAT pt, float speed, float range, float damage, float coolTime, SUBJECT subject);
	virtual void move();

	bool getErase() { return erase; }
};

