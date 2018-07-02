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
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============
	   
	SCENEMANAGER->render();
	//getMemDC() ��� CAMERAMANAGER->getCameraDC()
	TIMEMANAGER->render(CAMERAMANAGER->getCameraDC());
	//================�� �����ε� �ǵ帮�� ���� =============
	CAMERAMANAGER->render(this->getBackBuffer());
	this->getBackBuffer()->render(getHDC(), 0, 0, CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 2, CAMERAMANAGER->getCameraPoint().y - WINSIZEY / 2, WINSIZEX, WINSIZEY);
}