#include "stdafx.h"
#include "skillSet.h"

skillSet::skillSet() {}
skillSet::~skillSet() {}

HRESULT skillSet::init()
{
	_image = IMAGEMANAGER->findImage("skillSet");

	const char* tempSkillName[7] = { "바람베기", "화염구", "불타는올가미", "맹렬회오리", "흙주먹", "불꽃타격", "사이클론부메랑" };
	const char* tempSkillInfo[7] = { "바람베기", "화염구", "불타는올가미", "맹렬회오리", "흙주먹", "불꽃타격", "사이클론부메랑" };
	SET_TYPE tempSetType[7] = { NORMAL, ACTIVE_SKILL, ACTIVE_SKILL, ACTIVE_SKILL, NORMAL, NORMAL, ACTIVE_SKILL};

	for (int i = 0; i < 7; i++)
	{
		_skillSet[i].name = tempSkillName[i];
		_skillSet[i].info = tempSkillInfo[i];
		_skillSet[i].type = tempSetType[i];
	}

	_skillSetRect = RectMakeCenter(WINSIZEX * 4 / 5, WINSIZEY / 2, 400, 560);

	_selectedSkillIndex = -1;

	_isOpen = false;

	return S_OK;
}

void skillSet::release() {}

void skillSet::update()
{
	keyProcess();
}

void skillSet::render()
{
	if (_isOpen)
	{
		IMAGEMANAGER->findImage("skillSet")->alphaRender(CAMERAMANAGER->getCameraDC(), _skillSetRect.left, _skillSetRect.top, 200);

		for (int i = 0; i < 7; i++)
		{
			if (_selectedSkillIndex == i) _sampleRect[_selectedSkillIndex] = RectMakeCenter(_ptMouse.x + 12, _ptMouse.y + 12, 50, 50);
			else
			{
				switch (i)
				{
				case 0:
					_sampleRect[i] = RectMakeCenter(_skillSetRect.left + 97, _skillSetRect.top + 125, 50, 50);
					break;
				case 1: case 2: case 3:
					_sampleRect[i] = RectMakeCenter(_skillSetRect.left + 187 + (i - 1) * 65, _skillSetRect.top + 125, 50, 50);
					break;
				case 4: case 5:
					_sampleRect[i] = RectMakeCenter(_skillSetRect.left + 97 + (i - 4) * 77, _skillSetRect.top + 275, 50, 50);
					break;
				case 6:
					_sampleRect[i] = RectMakeCenter(_skillSetRect.left + 286, _skillSetRect.top + 275, 50, 50);
					break;
				}
			}
			char temp[50] = "UI";
			strcat_s(temp, _skillSet[i].name);

			IMAGEMANAGER->findImage(temp)->render(CAMERAMANAGER->getCameraDC(), _sampleRect[i].left, _sampleRect[i].top);

			if (_selectedSkillIndex != -1) continue;

			if (PtInRect(&_sampleRect[i], _ptMouse))
			{
				HFONT font, oldFont;
				RECT skillText;
				font = CreateFont(25, 0, 0, 0, 25, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("맑은 고딕"));
				oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font);
				SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
				SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);
				skillText = RectMakeCenter(_skillSetRect.left + 200, _skillSetRect.top + 425, 400, 50);
				DrawText(CAMERAMANAGER->getCameraDC(), TEXT(_skillSet[i].name), strlen(_skillSet[i].name), &skillText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				skillText = RectMakeCenter(_skillSetRect.left + 200, _skillSetRect.top + 475, 400, 50);
				DrawText(CAMERAMANAGER->getCameraDC(), TEXT(_skillSet[i].info), strlen(_skillSet[i].info), &skillText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
				DeleteObject(font);
			}
		}
	}
}

void skillSet::keyProcess()
{
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_isOpen = (_isOpen ? false : true);
	}

	if (_isOpen)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < 7; i++)
			{
				if (PtInRect(&_sampleRect[i], _ptMouse) && _selectedSkillIndex == -1)
				{
					_selectedSkillIndex = i; //선택한 아이템 인덱스
				}
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			for (int i = 0; i < 7; i++)
			{
				if (PtInRect(&_sampleRect[i], _ptMouse))
				{
					if (_selectedSkillIndex != -1) //스킬 교체
					{
						changeSkillKeySet(_selectedSkillIndex, i);
					}
				}
			}

			_selectedSkillIndex = -1; //선택 취소 시 인덱스 -1으로 초기화
		}
	}
}

void skillSet::changeSkillKeySet(int click, int change)
{
	if (click == change) return;

	if (_skillSet[click].type == _skillSet[change].type)
	{
		tagSkillSet temp = _skillSet[click];
		_skillSet[click] = _skillSet[change];
		_skillSet[change] = temp;
	}
}