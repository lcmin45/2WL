#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcFront;	//���α׷��� �� ��Ʈ
	RECT _rcBack;	//���α׷��� �� ��Ʈ
	int _x, _y;			//��ǥ~
	int _gap;
	float _width;		//���α׷��� �� ����ũ��
	const char* _frontImage;
	const char* _backImage;

	image* _progressBarFront;
	image* _progressBarBack;

public:
	progressBar();
	~progressBar();

	HRESULT init(int x, int y, const char* frontImage, int frontWidth, int frontHeight, const char* backImage, int backWidth, int backHeight);
	void release();
	void update();
	void render();

	void setGauge(float currentGauge, float maxGauge);

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
};