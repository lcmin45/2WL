#pragma once
#include "skill.h"

struct METEOR
{
	image* img;
	image* img2;
	POINTFLOAT pt, pt2;
	RECT rc, rc2;
	int frameIndex, frameIndex2;
	float startTime;
};

class 메테오 : public skill
{
private:
	vector<METEOR*>				vMeteor;
	vector<METEOR*>::iterator	viMeteor;

	float _playTime;
public:
	메테오();
	~메테오();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	virtual void fire(const char * skillName, int amount, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	void createMeteor();
	void moveMeteor();


	vector<METEOR*>	getVMeteor() { return vMeteor; };
};

