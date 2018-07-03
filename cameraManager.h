#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image*	_camera;
	float	_x, _y;

public:
	cameraManager();
	~cameraManager();
	 
	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
	void render(image* img);

	HDC getCameraDC() { return _camera->getMemDC(); }
	void setCameraPoint(POINT point);
	POINT getCameraPoint() { return PointMake(_x, _y); }
	image* getCamera() { return _camera; }
};

