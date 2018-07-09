#pragma once
#include "gameNode.h"

enum SUBJECT
{
	PLAYER, ENEMY
};

struct PARTICLE
{
	image* img;
	POINTFLOAT pt;
	RECT rc;
	int indexX;
	int indexY;
	float angle;
	float startTime;
};

class skill : public gameNode
{
protected:
	SUBJECT _subject;
	image* _img;
	RECT _rc;
	char _str[1024];
	POINTFLOAT _firePt;
	POINTFLOAT _pt;
	float _angle;
	float _speed;
	float _range;
	float _damage;
	float _coolTime;
	int _amount;
	int _frameIndex;
	float _startTime;

public:
	skill();
	~skill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//skillName : 1skill(불꽃타격, 바람베기, 흙주먹) 2skill(화염구, 맹렬회오리, 대지의방패),3skill(불타는올가미,사이클론부메랑,대지의고리)
	//개수, 시작좌표, 각도, 스피드, 사거리, 데미지
	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	//스킬 움직임
	virtual void move();

	//프레임 이미지
	virtual void frameCount();

	//충돌 판정용 사각형
	RECT getRect() { return _rc; }
	image* getImage() { return _img; }
	int getFrameIndex() { return _frameIndex; }
};