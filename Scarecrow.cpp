#include "stdafx.h"
#include "Scarecrow.h"


Scarecrow::Scarecrow()
{
}


Scarecrow::~Scarecrow()
{
}

HRESULT Scarecrow::init(POINTFLOAT point)
{
	_image = IMAGEMANAGER->addFrameImage("Scarecrow", "image/monster/Scarecrow.bmp", 0, 0, 80, 60,2,1, true, RGB(255, 0, 255));
	_scarecrowDirection = SCARECROW_STAND;
	_x = point.x;
	_y = point.y;

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());




	int Stand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("ScarecrowStand", "Scarecrow", Stand, 1, 1, false);

	int Hit[] = { 1, 0 };
	KEYANIMANAGER->addArrayFrameAnimation("ScarecrowHit", "Scarecrow", Hit, 2, 5, false);

	_scarecrowMotion = KEYANIMANAGER->findAnimation("ScarecrowStand");

	return S_OK;
}

void Scarecrow::release()
{
}

void Scarecrow::update()
{
	Test();
	KEYANIMANAGER->update();
}

void Scarecrow::render()
{
	_image->aniRender(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top, _scarecrowMotion);
}

void Scarecrow::Test()
{
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{

		_scarecrowDirection = SCARECROW_HIT;
		_scarecrowMotion = KEYANIMANAGER->findAnimation("ScarecrowHit");
		_scarecrowMotion->start();
	}

}
