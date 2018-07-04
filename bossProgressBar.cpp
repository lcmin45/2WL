#include "stdafx.h"
#include "bossProgressBar.h"


bossProgressBar::bossProgressBar()
{
}


bossProgressBar::~bossProgressBar()
{
}


HRESULT bossProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;

	_bossRcProgress = RectMake(x, y, width, height);

	_bossProgressBarTop = IMAGEMANAGER->addImage("bossfrontBar", "image/boss/bossHpBarTop.bmp", x, y, width, height, true, RGB(255, 0, 255));
	_bossProgressBarBottom = IMAGEMANAGER->addImage("bossbackBar", "image/boss/bossHpBarBottom.bmp", x, y, width, height, true, RGB(255, 0, 255));

	//가로크기는 이미지의 가로크기로!
	_width = _bossProgressBarTop->getWidth();

	return S_OK;
}

void bossProgressBar::release()
{
}

void bossProgressBar::update()
{
	_bossRcProgress = RectMakeCenter(_x, _y, _bossProgressBarTop->getWidth(), _bossProgressBarTop->getHeight());
}

void bossProgressBar::render()
{
	//그려줄땐 뒤에 게이지부터 먼저 그린다
	IMAGEMANAGER->render("bossbackBar", CAMERAMANAGER->getCameraDC(),
		_bossRcProgress.left + _bossProgressBarBottom->getWidth() / 2,
		_y + _bossProgressBarBottom->getHeight() / 2, 0, 0,
		_bossProgressBarBottom->getWidth(), _bossProgressBarBottom->getHeight());

	//앞에 게이지는 가로크기 혹은 세로크기가 변해야하기때문에 변수가 크기값에 들어간다
	IMAGEMANAGER->render("bossfrontBar", CAMERAMANAGER->getCameraDC(),
		_bossRcProgress.left + _bossProgressBarBottom->getWidth() / 2,
		_y + _bossProgressBarBottom->getHeight() / 2, 0, 0,
		_width, _bossProgressBarBottom->getHeight());
}

void bossProgressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _bossProgressBarBottom->getWidth();
}
