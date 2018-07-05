#pragma once
#include "gameNode.h"

class bossProgressBar : public gameNode
{
private:
	RECT _bossRcProgress;	//���α׷��� �� ��Ʈ
	int _x, _y;			//��ǥ~
	float _width;		//���α׷��� �� ����ũ��

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

