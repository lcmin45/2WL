#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcProgress;	//���α׷��� �� ��Ʈ
	int _x, _y;			//��ǥ~
	float _width;		//���α׷��� �� ����ũ��

	image* _progressBarTop;
	image* _progressBarBottom;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, const char* frontImage, const char* backImage, int width, int height);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }

};

