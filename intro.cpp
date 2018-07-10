#include "stdafx.h"
#include "intro.h"

intro::intro() {}
intro::~intro() {}

HRESULT intro::init()
{
	_GameStart	= IMAGEMANAGER->findImage("GameStart");
	_Load		= IMAGEMANAGER->findImage("Load");
	_MapTool	= IMAGEMANAGER->findImage("MapTool");
	_Setting	= IMAGEMANAGER->findImage("Setting");
	_EXIT		= IMAGEMANAGER->findImage("EXIT");

	_rc[0] = RectMake(WINSIZEX / 2 - 160, WINSIZEY / 2 + 50, _GameStart->getFrameWidth(), _GameStart->getFrameHeight());
	_rc[1] = RectMake(WINSIZEX / 2 - 90, WINSIZEY / 2 + 115, _Load->getFrameWidth(), _Load->getFrameHeight());
	_rc[2] = RectMake(WINSIZEX / 2 - 140, WINSIZEY / 2 + 180, _MapTool->getFrameWidth(), _MapTool->getFrameHeight());
	_rc[3] = RectMake(WINSIZEX / 2 - 130, WINSIZEY / 2 + 245, _Setting->getFrameWidth(), _Setting->getFrameHeight());
	_rc[4] = RectMake(WINSIZEX / 2 - 75, WINSIZEY / 2 + 310, _EXIT->getFrameWidth(), _EXIT->getFrameHeight());

	_soundCheck = 0;

	SOUNDMANAGER->singleChannelPlay("TitleScreen");

	return S_OK;
}

void intro::release() {}

void intro::update()
{
	if (_introStart == 1) { _setScene = 1; _introStart = 2; }

	if (_setScene == 0)
	{
		++_timer;
		if (_timer % 18 == 0)
		{
			_timer = 0;
			_buttonAlpha = (_buttonAlpha == 255) ? 0 : 255;
		}

	}
	else if (_setScene == 1)
	{
		_buttonAlpha = 0;
		if (_titleY > -100)	{--_titleY;	}
		else (_sceneAlpha >= 255) ? _setScene = 2 : _sceneAlpha += 5;
	}
	else if (_setScene == 2)
	{
		_GameStart->setFrameY(0);
		_Load->setFrameY(0);
		_MapTool->setFrameY(0);
		_Setting->setFrameY(0);
		_EXIT->setFrameY(0);

		if (_soundCheck == 1)
		{
			SOUNDMANAGER->play("MenuMove", _effectSound);
			_soundCheck = 2;
		}


		if (PtInRect(&_rc[0], _ptMouse))
		{
			if (_soundCheck == 0)_soundCheck = 1;
			_GameStart->setFrameY(1);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->singleChannelPlay("Earth");
				SOUNDMANAGER->play("MenuOpen", _effectSound);
				SCENEMANAGER->changeScene("inGame");
			}
		}
		else if (PtInRect(&_rc[1], _ptMouse))
		{
			if (_soundCheck == 0)_soundCheck = 1;
			_Load->setFrameY(1);

			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("MenuOpen", _effectSound);

			}
		}
		else if (PtInRect(&_rc[2], _ptMouse))
		{
			if (_soundCheck == 0)_soundCheck = 1;
			_MapTool->setFrameY(1);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->singleChannelPlay("MapTool");
				SOUNDMANAGER->play("MenuOpen", _effectSound);
				SCENEMANAGER->changeScene("mapTool");
			}
		}
		else if (PtInRect(&_rc[3], _ptMouse))
		{
			if (_soundCheck == 0)_soundCheck = 1;
			_Setting->setFrameY(1);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("MenuOpen", _effectSound);
			}
		}
		else if (PtInRect(&_rc[4], _ptMouse))
		{
			if (_soundCheck == 0)_soundCheck = 1;
			_EXIT->setFrameY(1);
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SOUNDMANAGER->play("MenuOpen", _effectSound);
				PostQuitMessage(777);
			}
		}
		else _soundCheck = 0;
	}
}

void intro::render()
{
	IMAGEMANAGER->findImage("TitleScreen")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->findImage("TitleLogo")->render(getMemDC(), 0, _titleY);
	IMAGEMANAGER->findImage("PRESS ANY BUTTON")->alphaRender(getMemDC(), WINSIZEX / 2 - 150, WINSIZEY / 2 + 200, _buttonAlpha);

	_GameStart->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 160, WINSIZEY / 2 + 50, _sceneAlpha);
	_Load->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 90, WINSIZEY / 2 + 115, _sceneAlpha);
	_MapTool->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 140, WINSIZEY / 2 + 180, _sceneAlpha);
	_Setting->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 130, WINSIZEY / 2 + 245, _sceneAlpha);
	_EXIT->alphaFrameRender(getMemDC(), WINSIZEX / 2 - 75, WINSIZEY / 2 + 310, _sceneAlpha);
	
}