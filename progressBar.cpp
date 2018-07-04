#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, const char* frontImage, int frontWidth, int frontHeight, const char* backImage, int backWidth, int backHeight)
{
	_x = x;
	_y = y;
	_gap = (backWidth - frontWidth) / 2;
	_frontImage = frontImage;
	_backImage = backImage;

	_rcFront = RectMakeCenter(x + _gap, y, frontWidth, frontHeight);
	_rcBack = RectMakeCenter(x, y, backWidth, backHeight);

	_progressBarFront = IMAGEMANAGER->findImage(_frontImage);
	_progressBarBack = IMAGEMANAGER->findImage(_backImage);

	//����ũ��� �̹����� ����ũ���!
	_width = _progressBarFront->getWidth();

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcFront = RectMakeCenter(_x + _gap, _y, _progressBarFront->getWidth(), _progressBarFront->getHeight());
}

void progressBar::render()
{
	//�׷��ٶ� �ڿ� ���������� ���� �׸���
	IMAGEMANAGER->render(_backImage, CAMERAMANAGER->getCameraDC(), _rcBack.left + _progressBarBack->getWidth() / 2, _y + _progressBarBack->getHeight() / 2, 0, 0, _progressBarBack->getWidth(), _progressBarBack->getHeight());

	//�տ� �������� ����ũ�� Ȥ�� ����ũ�Ⱑ ���ؾ��ϱ⶧���� ������ ũ�Ⱚ�� ����
	IMAGEMANAGER->render(_frontImage, CAMERAMANAGER->getCameraDC(), _rcFront.left + _progressBarFront->getWidth() / 2, _y + _progressBarFront->getHeight() / 2, 0, 0, _width, _progressBarFront->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarFront->getWidth();
}