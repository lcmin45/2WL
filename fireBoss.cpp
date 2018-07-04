#include "stdafx.h"
#include "fireBoss.h"


fireBoss::fireBoss()
{
} 


fireBoss::~fireBoss()
{
}


void fireBoss::render()
{
	char str[256];

	_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _fireindex, 0);

	_fireHpBar->render();

	if (_fireDialogue == true)
	{
		////////대사 그려주기
		IMAGEMANAGER->findImage("불대화")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

		SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
		SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

		HFONT font2, oldFont2;
		font2 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
		oldFont2 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font2);
		sprintf_s(str, "아직 몸이 안덥혀졌나? 그럼 내가 열을 선사하지!");
		TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
		SelectObject(CAMERAMANAGER->getCameraDC(), oldFont2);
		DeleteObject(font2);
	}
}

void fireBoss::update()
{
	//프래임 이미지 카운트
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		++_fireindex;
		//보스 체력이 0보다 클때
		if (_fireCurrentHP > 0)
		{
			//소환 모션이 끝나면 등장 모션띄우고 대화창 띄우기
			if (_bossImg == IMAGEMANAGER->findImage("불소환"))
			{
				if (_fireindex > _bossImg->getMaxFrameX())
				{
					_bossImg = IMAGEMANAGER->findImage("불등장");
					_fireindex = 0;
					_fireDialogue = true;
				}
			}

			if (_fireDialogue == true)
			{
				if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					_fireMove = true;
					_fireDialogue = false;
				}
			}

			if (_bossImg == IMAGEMANAGER->findImage("불등장"))
			{
				if (_fireindex > _bossImg->getMaxFrameX())
				{
					_fireindex = 0;
				}
			}
			if (_bossImg == IMAGEMANAGER->findImage("불스킬오른쪽") || _bossImg == IMAGEMANAGER->findImage("불스킬왼쪽")
				|| _bossImg == IMAGEMANAGER->findImage("불스킬2") || _bossImg == IMAGEMANAGER->findImage("불오른쪽") || _bossImg == IMAGEMANAGER->findImage("불왼쪽"))
			{
				if (_fireindex > _bossImg->getMaxFrameX())
				{
					_fireindex = _bossImg->getMaxFrameX();
				}
			}
			_frameCount = 0;
		}
		//보스 체력이 0일때 죽는 모션
		else if (_fireCurrentHP <= 0)
		{
			_bossImg = IMAGEMANAGER->findImage("불죽음");
			_fireindex = 0;
		}
	}
	_bossRc = RectMakeCenter(_x, _y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
}


void fireBoss::fireMove()
{
	if (_fireMove == true)
	{
		++_bossMoveCount;
		//대각선 이동
		if (_bossMoveCount < 100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불왼쪽");
				_fireindex = 0;
			}
			_x -= 4;
			_y += 3;
		}
		else if (_bossMoveCount < 500 && _bossMoveCount >= 300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불오른쪽");
				_fireindex = 0;
			}
			_x += 4;
			_y -= 3;
		}
		//중앙으로 순간이동
		else if (_bossMoveCount < 800 && _bossMoveCount >= 700)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불왼쪽");
				_fireindex = 0;
			}
			_x -= 4;
			_y += 3;
		}

		else if (_bossMoveCount < 1100 && _bossMoveCount >= 1000)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불왼쪽");
				_fireindex = 0;
			}
			_x -= 4;
			_y -= 3;
		}
		else if (_bossMoveCount < 1500 && _bossMoveCount >= 1300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불오른쪽");
				_fireindex = 0;
			}
			_x += 4;
			_y += 3;
		}
		//중앙으로 순간이동
		else if (_bossMoveCount < 1800 && _bossMoveCount >= 1700)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불왼쪽");
				_fireindex = 0;
			}
			_x -= 4;
			_y -= 3;
		}
		else if (_bossMoveCount < 2200 && _bossMoveCount >= 2000)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("불등장");
				_woodindex = 0;
			}
		}


		else if (_bossMoveCount >= 2200)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossMoveCount = 0;
			}
		}

		//////////////////////스킬 사용////////////////
		else if ((_bossMoveCount < 300 && _bossMoveCount >= 100) || (_bossMoveCount < 1300 && _bossMoveCount >= 1100))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("불스킬오른쪽");
				_fireindex = 0;
			}
		}
		else if ((_bossMoveCount < 700 && _bossMoveCount >= 500) || (_bossMoveCount < 1700 && _bossMoveCount >= 1500))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("불스킬왼쪽");
				_fireindex = 0;
			}
		}
		else if ((_bossMoveCount < 1000 && _bossMoveCount >= 800) || (_bossMoveCount < 2000 && _bossMoveCount >= 1800))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("불스킬2");
				_fireindex = 0;
			}
		}

	}
}

void fireBoss::fireSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("불스킬왼쪽"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("불스킬오른쪽"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("불스킬2"))
	{
	}

}
