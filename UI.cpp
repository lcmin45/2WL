#include "stdafx.h"
#include "UI.h"
#include "player.h"

UI::UI() {}
UI::~UI() {}

HRESULT UI::init()
{
	_progressBar = new progressBar;
	_progressBar->init(100, 25, "playerFrontHp", 230, 25, "playerBackHp", 250, 25);

	return S_OK;
}

void UI::release() {}

void UI::update()
{
	_progressBar->update();
	_progressBar->setGauge(_player->getCurrentHp(), _player->getMaxHp());
}

void UI::render()
{
	_image = IMAGEMANAGER->findImage("mouse");
	_image->render(CAMERAMANAGER->getCameraDC(), _ptMouse.x - _image->getWidth() / 2, _ptMouse.y - _image->getHeight() / 2);
	_image = IMAGEMANAGER->findImage("playerIcon");
	_image->render(CAMERAMANAGER->getCameraDC(), 25, 25);
	_progressBar->render();
	_image = IMAGEMANAGER->findImage("playerCoin");
	_image->render(CAMERAMANAGER->getCameraDC(), 100, 65);

	HFONT font, oldFont;
	RECT itemText;
	font = CreateFont(30, 0, 0, 0, 25, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("¸¼Àº °íµñ"));
	oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font);
	SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
	SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);
	char info[128];
	sprintf_s(info, "%d / %d", int(_player->getCurrentHp()), int(_player->getMaxHp()));
	itemText = RectMakeCenter(290, 30, 250, 25);
	DrawText(CAMERAMANAGER->getCameraDC(), TEXT(info), strlen(info), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	sprintf_s(info, "%d", _player->getCoin());
	itemText = RectMakeCenter(160, 77, 50, 25);
	DrawText(CAMERAMANAGER->getCameraDC(), TEXT(info), strlen(info), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
	DeleteObject(font);

	if (_player->getCanTakeItem())
	{
		_image = IMAGEMANAGER->findImage("buttonF");
		_image->render(getMemDC(), _player->getPosition().x - _image->getWidth() / 2, _player->getPosition().y - _image->getHeight() - 30);
	}

	_player->getSkillSet()->render();
}