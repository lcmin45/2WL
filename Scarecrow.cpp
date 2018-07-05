#include "stdafx.h"
#include "Scarecrow.h"


Scarecrow::Scarecrow()
{
}


Scarecrow::~Scarecrow()
{
}

HRESULT Scarecrow::init(POINTFLOAT point, int index)
{
	//_image = IMAGEMANAGER->findImage("SummonMonster");
	_image = IMAGEMANAGER->findImage("Scarecrow");
	_scarecrowDirection = SCARECROW_STAND;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),
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
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _scarecrowMotion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
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
