#include "stdafx.h"
#include "progressBar.h"


progressBar::progressBar()
{
}


progressBar::~progressBar()
{
}

HRESULT progressBar::init(int x, int y, const char* frontImage, const char* backImage, int width, int height)
{
	_x = x;
	_y = y;

	_rcProgress = RectMake(x, y, width, height);

	char temp[20];
	sprintf_s(temp, "%s", frontImage);
	strcat_s(temp, ".bmp");
	_progressBarTop = IMAGEMANAGER->addImage(frontImage, temp, x, y, width, height, true, RGB(255, 0, 255));
	sprintf_s(temp, "%s", frontImage);
	strcat_s(temp, ".bmp");
	_progressBarBottom = IMAGEMANAGER->addImage(backImage, temp, x, y, width, height, true, RGB(255, 0, 255));

	//가로크기는 이미지의 가로크기로!
	_width = _progressBarTop->getWidth();

	return S_OK;
}

void progressBar::release()
{

}

void progressBar::update()
{
	_rcProgress = RectMakeCenter(_x, _y, _progressBarTop->getWidth(), _progressBarTop->getHeight());
}

void progressBar::render()
{
	//그려줄땐 뒤에 게이지부터 먼저 그린다
	IMAGEMANAGER->render("backBar", CAMERAMANAGER->getCameraDC(),
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_progressBarBottom->getWidth(), _progressBarBottom->getHeight());

	//앞에 게이지는 가로크기 혹은 세로크기가 변해야하기때문에 변수가 크기값에 들어간다
	IMAGEMANAGER->render("frontBar", CAMERAMANAGER->getCameraDC(), 
		_rcProgress.left + _progressBarBottom->getWidth() / 2,
		_y + _progressBarBottom->getHeight() / 2, 0, 0,
		_width, _progressBarBottom->getHeight());
}

void progressBar::setGauge(float currentGauge, float maxGauge)
{
	_width = (currentGauge / maxGauge) * _progressBarBottom->getWidth();
}