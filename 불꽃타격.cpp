#include "stdafx.h"
#include "�Ҳ�Ÿ��.h"


�Ҳ�Ÿ��::�Ҳ�Ÿ��()
{
}


�Ҳ�Ÿ��::~�Ҳ�Ÿ��()
{
}

HRESULT �Ҳ�Ÿ��::init()
{
	return S_OK;
}

void �Ҳ�Ÿ��::release()
{
}

void �Ҳ�Ÿ��::update()
{
	if (_img)
	{
		move();
		frameCount();
	}
}

void �Ҳ�Ÿ��::render()
{
	if(_img)_img->frameRender(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top);
}

void �Ҳ�Ÿ��::move()
{
	
}

void �Ҳ�Ÿ��::frameCount()
{
	_img->setFrameX(_frameIndex);
	_frameIndex++;

	if (_frameIndex > _img->getMaxFrameX()) _img = NULL;
}



