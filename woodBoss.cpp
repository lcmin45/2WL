#include "stdafx.h"
#include "woodBoss.h"


woodBoss::woodBoss()
{
}


woodBoss::~woodBoss()
{
}
 

void woodBoss::render()
{
	char str[256];

	_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _woodindex, 0);

	_woodHpBar->render();

	if (_woodDialogue == true)
	{
		////////대사 그려주기
		IMAGEMANAGER->findImage("나무대화")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

		SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
		SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

		HFONT font2, oldFont2;
		font2 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
		oldFont2 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font2);
		sprintf_s(str, "오면서 흙구덩이에는 안 빠졌기를 바란다...이제 내가 빠트릴 거니까!!");
		TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
		SelectObject(CAMERAMANAGER->getCameraDC(), oldFont2);
		DeleteObject(font2);
	}
}

void woodBoss::update()
{
	//프래임 이미지 카운트
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		++_woodindex;
		//보스체력이 0이 아닐때
		if (_woodCurrentHP > 0)
		{
			//소환 모션이 끝나면 등장모션과 대화창 띄우기
			if (_bossImg == IMAGEMANAGER->findImage("나무소환"))
			{
				if (_woodindex > _bossImg->getMaxFrameX())
				{
					_bossImg = IMAGEMANAGER->findImage("나무등장");
					_woodindex = 0;
					_woodDialogue = true;
				}
			}
			//스페이스키를 누르면 대화창 넘어가기
			if (_woodDialogue == true)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					_woodMove = true;
					_woodDialogue = false;
				}
			}

			if (_bossImg == IMAGEMANAGER->findImage("나무등장"))
			{
				if (_woodindex > _bossImg->getMaxFrameX())
				{
					_woodindex = 0;
				}
			}

			if (_bossImg == IMAGEMANAGER->findImage("나무오른쪽") || _bossImg == IMAGEMANAGER->findImage("나무왼쪽"))
			{
				if (_woodindex > _bossImg->getMaxFrameX())
				{
					_woodindex = 0;
				}
			}
			if (_bossImg == IMAGEMANAGER->findImage("나무점프") || _bossImg == IMAGEMANAGER->findImage("나무스킬") || _bossImg == IMAGEMANAGER->findImage("나무스킬2오른쪽") ||
				_bossImg == IMAGEMANAGER->findImage("나무스킬2왼쪽") || _bossImg == IMAGEMANAGER->findImage("나무죽음") || _bossImg == IMAGEMANAGER->findImage("나무오른쪽피격") || _bossImg == IMAGEMANAGER->findImage("왼쪽피격"))
			{
				if (_woodindex > _bossImg->getMaxFrameX())
				{
					_woodindex = _bossImg->getMaxFrameX();
				}
			}

			_frameCount = 0;
		}
		//보스 체력이 0일떄 죽는 모션
		else if (_woodCurrentHP <= 0)
		{
			_bossImg = IMAGEMANAGER->findImage("나무죽음");
			_woodindex = 0;
		}
	}
	_bossRc = RectMakeCenter((int)_x, (int)_y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
}


void woodBoss::woodMove()
{
	if (_woodMove == true)
	{
		++_bossMoveCount;
		//플레이어 좌표 받아와서 좌우로 이동하기
		if (_bossMoveCount < 100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("나무왼쪽");
				_woodindex = 0;
			}
			if (_player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 < _bossRc.left && _player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 > _bossRc.top)
			{
				_x -= 5;
				_y += 3;
			}
			if (_player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 < _bossRc.left && _player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 < _bossRc.top)
			{
				_x -= 5;
				_y -= 3;
			}
		}
		else if (_bossMoveCount < 400 && _bossMoveCount >= 300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("나무오른쪽");
				_woodindex = 0;
			}

			if (_player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 > _bossRc.left && _player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 > _bossRc.top)
			{
				_x += 5;
				_y += 3;
			}
			if (_player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 > _bossRc.left && _player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 < _bossRc.top)
			{
				_x += 5;
				_y -= 3;
			}
		}

		//플레이어 위치에 점프하기 
		else if (_bossMoveCount < 700 && _bossMoveCount >= 600)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("나무점프");
				_woodindex = 0;
			}
			if (_player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 > _bossRc.top && _player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 < _bossRc.left)
			{
				_x -= 5;
				_y += 3;
			}
			if (_player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 > _bossRc.top && _player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 > _bossRc.left)
			{
				_x += 5;
				_y += 3;
			}
			if (_player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 < _bossRc.top && _player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 < _bossRc.left)
			{
				_x -= 5;
				_y -= 3;
			}
			if (_player.getBody().top + (_player.getBody().bottom - _player.getBody().top) / 2 < _bossRc.top && _player.getBody().left + (_player.getBody().right - _player.getBody().left) / 2 > _bossRc.left)
			{
				_x += 5;
				_y -= 3;
			}
		}

		else if (_bossMoveCount >= 900 && _bossMoveCount < 1100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("나무등장");
				_woodindex = 0;
			}
		}

		else if (_bossMoveCount >= 1100)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossMoveCount = 0;
			}
		}

		/////////////////스킬모션/////////////////////
		else if (_bossMoveCount >= 100 && _bossMoveCount < 300)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("나무스킬2오른쪽");
				_woodindex = 0;
			}
		}
		else if (_bossMoveCount < 600 && _bossMoveCount >= 400)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("나무스킬2왼쪽");
				_woodindex = 0;
			}
		}
		else if (_bossMoveCount >= 700 && _bossMoveCount < 900)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("나무스킬");
				_woodindex = 0;
			}
		}
	}
}

void woodBoss::woodSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("나무스킬"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("나무스킬2왼쪽"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("나무스킬2오른쪽"))
	{
	}
}
