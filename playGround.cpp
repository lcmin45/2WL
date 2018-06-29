#include "stdafx.h"
#include "playGround.h"

playGround::playGround() {}
playGround::~playGround() {}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	IMAGEMANAGER->addImage("bg", "image/bg.bmp", WINSIZEX, WINSIZEY, false, RGB(0, 0, 0));
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
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== 이 위로는 건드리지 말자 ==============

	IMAGEMANAGER->findImage("bg")->render(CAMERAMANAGER->getCameraDC(), 0, 0);
	SCENEMANAGER->render();

	//================이 밑으로도 건드리지 말자 =============
	CAMERAMANAGER->render(getHDC());
}