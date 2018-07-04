#include "stdafx.h"
#include "tileObject.h"
#include "mapToolNode.h"

tileObject::tileObject() { }

tileObject::~tileObject() { }

HRESULT tileObject::init(int index)
{
	switch (index)
	{
	case 1:
	{
		_img = IMAGEMANAGER->findImage("OBJECT_CANDLE");

		int candle[] = { 0, 1, 2, 3, 4, 5 };
		KEYANIMANAGER->addArrayFrameAnimation("CANDLE", "OBJECT_CANDLE", candle, 6, 10, true);
		_animation = KEYANIMANAGER->findAnimation("CANDLE");

	}
	break;
	case 2:
	{

	}
	break;
	case 3:
	{

	}
	break;
	case 4:
	{

	}
	break;
	case 5:
	{
		_img = IMAGEMANAGER->findImage("OBJECT_5");

		int ani[] = { 0, 1, 2, 3, 4, 5 };
		KEYANIMANAGER->addArrayFrameAnimation("ANI_OBJECT_5", "OBJECT_5", ani, 6, 10, true);
		_animation = KEYANIMANAGER->findAnimation("ANI_OBJECT_5");
	}
	break;
	}

	_animation->start();
	return S_OK;
}

void tileObject::release(void)
{

}

void tileObject::update(void)
{

}

void tileObject::render(void)
{
	_img->aniRender(getMemDC(), _tileCenterPoint.x - _renderPoint.x, _tileCenterPoint.y - _renderPoint.y, _animation);
}