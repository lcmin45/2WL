#pragma once
#include "gameNode.h"

class progressBar : public gameNode
{
private:
	RECT _rcFront;	//프로그레스 바 렉트
	RECT _rcBack;	//프로그레스 바 렉트
	int _x, _y;			//좌표~
	int _gap;
	float _width;		//프로그레스 바 가로크기
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