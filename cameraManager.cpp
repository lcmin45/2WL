#include "stdafx.h"
#include "cameraManager.h"

HRESULT cameraManager::init()
{
	_camera = IMAGEMANAGER->addImage("camera", BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	return S_OK;
}

void cameraManager::release() {}

void cameraManager::update()
{
	//keyProcess();
}

void cameraManager::render(HDC hdc)
{
	_camera->render(hdc, 0, 0, _x - WINSIZEX / 2, _y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}

void cameraManager::keyProcess()
{
	if (KEYMANAGER->isStayKeyDown('W'))
	{
		if (_y - WINSIZEY / 2 > 0) _y -= 10;
	}
	if (KEYMANAGER->isStayKeyDown('S'))
	{
		if (_y + WINSIZEY / 2 < BACKGROUND_HEIGHT) _y += 10;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		if (_x - WINSIZEX / 2 > 0) _x -= 10;
	}
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		if (_x + WINSIZEX / 2 < BACKGROUND_WIDTH) _x += 10;
	}
}

void cameraManager::changePos(float x, float y)
{
	if (x - WINSIZEX / 2 > 0 && x + WINSIZEX / 2 < BACKGROUND_WIDTH) _x = x;
	else if (x - WINSIZEX / 2 <= 0) _x = WINSIZEX / 2;
	else if (x + WINSIZEX / 2 >= BACKGROUND_WIDTH) _x = BACKGROUND_WIDTH - WINSIZEX / 2;
	if (y - WINSIZEY / 2 > 0 && y + WINSIZEY / 2 < BACKGROUND_HEIGHT) _y = y;
	else if (y - WINSIZEY / 2 <= 0) _y = WINSIZEY / 2;
	else if (y + WINSIZEY / 2 >= BACKGROUND_HEIGHT) _y = BACKGROUND_HEIGHT - WINSIZEY / 2;
}

cameraManager::cameraManager() {}
cameraManager::~cameraManager() {}