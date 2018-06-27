#pragma once
#include "gameNode.h"

class skill : public gameNode
{
private:
	image* img;
	RECT _rc;
	const char* str[1024];
	float _x, _y;
	float _speed;
	float _range;
	float _damage;
	int _frameIndex;

public:
	skill();
	~skill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//skillName
	//불꽃타격, 바람베기, 흙주먹
	//화염돌격, 공중폭발, 가시길
	//화염구, 맹렬회오리, 대지의방패
	//불타는올가미,사이클론부메랑,대지의고리
	void fire(char* skillName, float x, float y, float speed, float range, float damage);
	void move();
};