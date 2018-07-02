#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image * _camera;
	float _x, _y;
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void keyProcess();
	void changePos(float x, float y);

	HDC getCameraDC() { return _camera->getMemDC(); }

	cameraManager();
	~cameraManager();
};