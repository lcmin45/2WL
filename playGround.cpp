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
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, WHITENESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============

	SCENEMANAGER->render();
	//getMemDC() ��� CAMERAMANAGER->getCameraDC()

	//================�� �����ε� �ǵ帮�� ���� =============
	CAMERAMANAGER->render(getHDC());
}