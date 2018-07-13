#include "stdafx.h"
#include "UI.h"
#include "player.h"
#include "projectileManager.h"

UI::UI() {}
UI::~UI() {}

HRESULT UI::init()
{
	//주인공 에너지 프로그레스 바
	_progressBar = new progressBar;
	_progressBar->init(100, 25, "playerFrontHp", 230, 25, "playerBackHp", 250, 25);
	_optionRC = RectMake(WINSIZEX - 75, 25, 50, 50);

	_option = new option;
	_option->init();

	return S_OK;
}

void UI::release() {}

void UI::update()
{
	if (_option->getIsView()) _option->update();
	if (_option->getIsView()) return;

	//주인공 체력 갱신
	_progressBar->update();
	_progressBar->setGauge(_player->getCurrentHp(), _player->getMaxHp());

	if (PtInRect(&_optionRC, getCameraPoint()))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) { _option->setIsView(true); }
	}
}

void UI::render()
{
	//각 UI를 그려준다
	_image = IMAGEMANAGER->findImage("mouse");
	_image->render(CAMERAMANAGER->getCameraDC(), _ptMouse.x - _image->getWidth() / 2, _ptMouse.y - _image->getHeight() / 2);
	_image = IMAGEMANAGER->findImage("playerIcon");
	_image->render(CAMERAMANAGER->getCameraDC(), 25, 25);
	_progressBar->render();
	_image = IMAGEMANAGER->findImage("playerCoin");
	_image->render(CAMERAMANAGER->getCameraDC(), 100, 65);
	_image = IMAGEMANAGER->findImage("optionIcon");
	_image->frameRender(CAMERAMANAGER->getCameraDC(), WINSIZEX - 75, 25);
	(PtInRect(&_optionRC, getCameraPoint())) ? _image->setFrameY(1) : _image->setFrameY(0);

	HFONT font, oldFont;
	RECT itemText;
	font = CreateFont(30, 0, 0, 0, 25, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("맑은 고딕"));
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

	//주인공이 아이템 줍기 가능 일 때
	if (_player->getCanTakeItem())
	{
		IMAGEMANAGER->findImage("buttonF")->render(getMemDC(), _player->getPosition().x - _image->getWidth() / 2, _player->getPosition().y - _image->getHeight() - 30);
	}

	//스킬셋 상태와 각 스킬 쿨타임 UI
	for (int i = 0; i < 4; i++)
	{
		IMAGEMANAGER->findImage((i == 0 ? "mouseL" : (i == 1 ? "buttonZ" : (i == 2 ? "buttonX" : "buttonC"))))->render(CAMERAMANAGER->getCameraDC(), 25 + i * 75, WINSIZEY - 125);
		char temp[50] = "UI";
		strcat_s(temp, _player->getSkillSet()->getSettingSkill()[i].name.c_str());
		IMAGEMANAGER->findImage(temp)->render(CAMERAMANAGER->getCameraDC(), 25 + i * 75, WINSIZEY - 75);

		if (_projectileManager->getCoolTime(_player->getSkillSet()->getSettingSkill()[i].name.c_str()) <= 0.0f) continue;

		HFONT font, oldFont;
		RECT itemText;
		
		font = CreateFont(30, 0, 0, 0, 30, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("@휴먼둥근헤드라인"));
		oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font);
		SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 0, 0));
		SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);
		char info[128];
		sprintf_s(info, "%.1f", _projectileManager->getCoolTime(_player->getSkillSet()->getSettingSkill()[i].name.c_str()));
		itemText = RectMake(25 + i * 75, WINSIZEY - 75, 50, 50);
		DrawText(CAMERAMANAGER->getCameraDC(), TEXT(info), strlen(info), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
		DeleteObject(font);
	}

	_option->render();

	_player->getSkillSet()->render();
}