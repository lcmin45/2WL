#include "stdafx.h"
#include "tileObject.h"
#include "mapToolNode.h"

tileObject::tileObject() { }

tileObject::~tileObject() { }

HRESULT tileObject::init(int index)
{
	_img = IMAGEMANAGER->findImage("FRAME_OBJECT");
	int ani0[] = { 0, 1, 2, 3, 4, 5 };
	int ani1[] = { 6, 7, 8, 9, 10, 11 };
	int ani2[] = { 12, 13, 14, 15, 16, 17 };

	switch (index)
	{
	case 1:

		KEYANIMANAGER->addArrayFrameAnimation("ANI_FRAME_OBJECT_0", "FRAME_OBJECT", ani0, 6, 10, true);
		_animation = KEYANIMANAGER->findAnimation("ANI_FRAME_OBJECT_0");
		break;
	case 2:

		KEYANIMANAGER->addArrayFrameAnimation("ANI_FRAME_OBJECT_1", "FRAME_OBJECT", ani1, 6, 10, true);
		_animation = KEYANIMANAGER->findAnimation("ANI_FRAME_OBJECT_1");
		break;
	case 3:

		KEYANIMANAGER->addArrayFrameAnimation("ANI_FRAME_OBJECT_2", "FRAME_OBJECT", ani2, 6, 10, true);
		_animation = KEYANIMANAGER->findAnimation("ANI_FRAME_OBJECT_2");
		break;
	case 4:

		break;
	case 5:
		_img = IMAGEMANAGER->findImage("OBJECT_5");

		int ani4[] = { 0, 1, 2, 3, 4, 5 };
		KEYANIMANAGER->addArrayFrameAnimation("ANI_OBJECT_5", "OBJECT_5", ani4, 6, 10, true);
		_animation = KEYANIMANAGER->findAnimation("ANI_OBJECT_5");
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