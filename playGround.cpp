#include "stdafx.h"
#include "playGround.h"

playGround::playGround() {}
playGround::~playGround() {}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("inGame", new inGame);
	SCENEMANAGER->addScene("mapTool", new mapTool);
	SCENEMANAGER->changeScene("inGame");

	return S_OK;
}

void playGround::release(void)
{
	gameNode::release();
}

void playGround::update(void)
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown(VK_F5))
	{
		SCENEMANAGER->changeScene("mapTool");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F6))
	{
		SCENEMANAGER->changeScene("inGame");
	}

	SCENEMANAGER->update();
}

void playGround::render(void)
{
	//흰색도화지 한 장 깔아둔다
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== 이 위로는 건드리지 말자 ==============
	   
	SCENEMANAGER->render();
	//getMemDC() 대신 CAMERAMANAGER->getCameraDC()
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//================이 밑으로도 건드리지 말자 =============
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}