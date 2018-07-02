#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager() { }

cameraManager::~cameraManager() { }

HRESULT cameraManager::init(void)
{
	_camera = IMAGEMANAGER->addImage("camera", WINSIZEX, WINSIZEY);

	_x = WINSIZEX / 2.0f;
	_y = WINSIZEY / 2.0f;

	return S_OK;
}

void cameraManager::release(void)
{

}

void cameraManager::update(void)
{
}

void cameraManager::render()
{
	
}

void cameraManager::render(image* img)
{
	GdiTransparentBlt(img->getMemDC(), _x - WINSIZEX / 2, _y - WINSIZEY / 2, WINSIZEX, WINSIZEY,
		_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(0, 0, 0));
}

void cameraManager::setCameraPoint(POINT point)
{ 
	_x = point.x; 
	_y = point.y; 

	if (_x <= WINSIZEX / 2) _x = WINSIZEX / 2;
	if (_x >= TOTALSIZEX - WINSIZEX / 2) _x = TOTALSIZEX - WINSIZEX / 2;
	if (_y <= WINSIZEY / 2) _y = WINSIZEY / 2;
	if (_y >= TOTALSIZEY - WINSIZEY / 2) _y = TOTALSIZEY - WINSIZEY / 2;
}