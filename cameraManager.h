#pragma once
#include "singletonBase.h"

class cameraManager : public singletonBase<cameraManager>
{
private:
	image*	_camera;		// 카메라 화면이 담길 곳
	POINTFLOAT _cameraPos;	// 카메라 중점 좌표
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