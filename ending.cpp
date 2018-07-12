#include "stdafx.h"
#include "ending.h"

ending::ending() {}
ending::~ending() {}

HRESULT ending::init()
{
	_image = IMAGEMANAGER->findImage("¿£µù");
	_BlackAalpha = 0;
	return S_OK;
}

void ending::release() {}

void ending::update()
{
	++_count;
	if (_count == 180) SOUNDMANAGER->play("StageVictory");
	if (_count % 5 == 0)_index++;
	if (_index > _image->getMaxFrameY())
	{
		_index = _image->getMaxFrameY();
		if(_count >= 300) _BlackAalpha += 5;
		if(_BlackAalpha >=255) SCENEMANAGER->changeScene("intro");
	}

}

void ending::render()
{
	_image->frameRender(getMemDC(), 120, 150, 0, _index);
}