#pragma once
#include "gameNode.h"

class bossProgressBar : public gameNode
{
private:
	RECT _bossRcProgress;	//프로그레스 바 렉트
	int _x, _y;			//좌표~
	float _width;		//프로그레스 바 가로크기

	image* _bossProgressBarTop;
	image* _bossProgressBarBottom;

public:
	bossProgressBar();
	~bossProgressBar();

	HRESULT init(int x, int y, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

};

