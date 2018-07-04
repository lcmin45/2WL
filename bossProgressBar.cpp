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

	//����ũ��� �̹����� ����ũ���!
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
	//�׷��ٶ� �ڿ� ���������� ���� �׸���
	IMAGEMANAGER->render("bossbackBar", CAMERAMANAGER->getCameraDC(),
		_bossRcProgress.left + _bossProgressBarBottom->getWidth() / 2,
		_y + _bossProgressBarBottom->getHeight() / 2, 0, 0,
		_bossProgressBarBottom->getWidth(), _bossProgressBarBottom->getHeight());

	//�տ� �������� ����ũ�� Ȥ�� ����ũ�Ⱑ ���ؾ��ϱ⶧���� ������ ũ�Ⱚ�� ����
	IMAGEMANAGER->render("bossfrontBar", CAMERAMANAGER->getCameraDC(),
		_bossRcProgress.left + _bossProgressBarBottom->getWidth() / 2,
		_y + _bossProgressBarBottom->getHeight() / 2, 0, 0,
		_width, _bossProgressBarBottom->getHeight());
}

void bossProgressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _bossProgressBarBottom->getWidth();
}
