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

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		SCENEMANAGER->changeScene("mapTool");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		SCENEMANAGER->changeScene("inGame");
	}

	SCENEMANAGER->update();
}

void playGround::render(void)
{
	//흰색도화지 한 장 깔아둔다
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, WHITENESS);
	//============== 이 위로는 건드리지 말자 ==============

	SCENEMANAGER->render();
	//getMemDC() 대신 CAMERAMANAGER->getCameraDC()

	//================이 밑으로도 건드리지 말자 =============
	CAMERAMANAGER->render(getHDC());
}