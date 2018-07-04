#include "stdafx.h"
#include "cameraManager.h"


cameraManager::cameraManager() { }

cameraManager::~cameraManager() { }

HRESULT cameraManager::init(void)
{
	_camera = IMAGEMANAGER->addImage("camera", WINSIZEX, WINSIZEY);

	_cameraPos.x = WINSIZEX / 2.0f;
	_cameraPos.y = WINSIZEY / 2.0f;

	return S_OK;
}

void cameraManager::release(void)
{

}

void cameraManager::update(void)
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_cameraPos.x += 0.5f;
	}
}

void cameraManager::render()
{

}

void cameraManager::render(image* img)
{
	GdiTransparentBlt(img->getMemDC(), _cameraPos.x - WINSIZEX / 2, _cameraPos.y - WINSIZEY / 2, WINSIZEX, WINSIZEY,
		_camera->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, RGB(0, 0, 0));
}

void cameraManager::setCameraPoint(POINTFLOAT point)
{
	_cameraPos.x = point.x;
	_cameraPos.y = point.y;

	if (_cameraPos.x <= WINSIZEX / 2) _cameraPos.x = WINSIZEX / 2;
	if (_cameraPos.x >= TOTALSIZEX - WINSIZEX / 2) _cameraPos.x = TOTALSIZEX - WINSIZEX / 2;
	if (_cameraPos.y <= WINSIZEY / 2) _cameraPos.y = WINSIZEY / 2;
	if (_cameraPos.y >= TOTALSIZEY - WINSIZEY / 2) _cameraPos.y = TOTALSIZEY - WINSIZEY / 2;
}