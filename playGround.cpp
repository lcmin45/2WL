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
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============

	IMAGEMANAGER->findImage("bg")->render(CAMERAMANAGER->getCameraDC(), 0, 0);
	SCENEMANAGER->render();

	//================�� �����ε� �ǵ帮�� ���� =============
	CAMERAMANAGER->render(getHDC());
}