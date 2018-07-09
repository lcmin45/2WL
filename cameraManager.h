#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image*	_camera;
	POINTFLOAT _cameraPos;
public:
	cameraManager();
	~cameraManager();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render();
	void render(image* img);

	HDC getCameraDC() { return _camera->getMemDC(); }
	void setCameraPoint(POINTFLOAT point);
	POINTFLOAT getCameraPoint() { return _cameraPos; }
	image* getCamera() { return _camera; }
};