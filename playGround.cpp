#include "stdafx.h"
#include "playGround.h"

playGround::playGround() {}
playGround::~playGround() {}

HRESULT playGround::init(void)
{
	gameNode::init(true);

	return S_OK;
}

void playGround::release(void)
{
	gameNode::release();
}

void playGround::update(void)
{
	gameNode::update();
}

void playGround::render(void)
{
	//흰색도화지 한 장 깔아둔다
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== 이 위로는 건드리지 말자 ==============

	//getMemDC() 대신에 CAMERAMANAGER->getCameraDC();

	//================이 밑으로도 건드리지 말자 =============
	CAMERAMANAGER->render(getHDC());
}