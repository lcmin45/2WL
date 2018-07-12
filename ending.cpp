#include "stdafx.h"
#include "ending.h"

ending::ending() {}
ending::~ending() {}

HRESULT ending::init()
{
	_image = IMAGEMANAGER->findImage("¿£µù");
	return S_OK;
}

void ending::release() {}

void ending::update()
{
	++_count;
	if (_count % 10 == 0)_index++;
	if (_index > _image->getMaxFrameY())
	{
		_index = _image->getMaxFrameY();
	}

}

void ending::render()
{
	_image->frameRender(getMemDC(), 120, 150, 0, _index);
}