#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image * _camera;
	float _x, _y;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void keyProcess();
	void changePos(float x, float y);

	HDC getCameraDC() { return _camera->getMemDC(); }
	POINTFLOAT getXy() { return { _x, _y }; }

	cameraManager();
	~cameraManager();
};