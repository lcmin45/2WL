#include "stdafx.h"
#include "ºÒ²ÉÅ¸°Ý.h"


ºÒ²ÉÅ¸°Ý::ºÒ²ÉÅ¸°Ý()
{
}


ºÒ²ÉÅ¸°Ý::~ºÒ²ÉÅ¸°Ý()
{
}

HRESULT ºÒ²ÉÅ¸°Ý::init()
{
	return S_OK;
}

void ºÒ²ÉÅ¸°Ý::release()
{
}

void ºÒ²ÉÅ¸°Ý::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void ºÒ²ÉÅ¸°Ý::render()
{
	if(_img)_img->frameRender(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
}

void ºÒ²ÉÅ¸°Ý::move()
{
	
}

void ºÒ²ÉÅ¸°Ý::frameCount()
{
	_img->setFrameX(_frameIndex);
	_frameIndex++;

	if (_frameIndex > _img->getMaxFrameX()) _img = NULL;
}



