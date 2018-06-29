#include "stdafx.h"
#include "playGround.h"

playGround::playGround() {}
playGround::~playGround() {}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	SCENEMANAGER->addScene("inGame", new inGame);
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

	SCENEMANAGER->update();
}

void playGround::render(void)
{
	//흰색도화지 한 장 깔아둔다
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== 이 위로는 건드리지 말자 ==============

	SCENEMANAGER->render();

	//================이 밑으로도 건드리지 말자 =============
	CAMERAMANAGER->render(getHDC());
}