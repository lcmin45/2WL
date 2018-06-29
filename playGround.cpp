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
	//�����ȭ�� �� �� ��Ƶд�
	PatBlt(CAMERAMANAGER->getCameraDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	//============== �� ���δ� �ǵ帮�� ���� ==============

	//getMemDC() ��ſ� CAMERAMANAGER->getCameraDC();

	//================�� �����ε� �ǵ帮�� ���� =============
	CAMERAMANAGER->render(getHDC());
}