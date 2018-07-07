#include "stdafx.h"
#include "iceBoss.h"


iceBoss::iceBoss()
{
}


iceBoss::~iceBoss()
{
}



void iceBoss::render()
{
	if (_iceBossDie == false)//보스가 죽지 않았을때
	{
		char str[256];

		_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _iceindex, 0);

		_iceHpBar->render();

		//보스 등장 할때 대사 띄워주기
		if (_iceDialogue == true)
		{
			IMAGEMANAGER->findImage("얼음대화")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font2, oldFont2;
			font2 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont2 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font2);
			sprintf_s(str, "그렇게 떨어봐야 이미 늦었다..그 자리에 그대로 얼려주마!!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont2);
			DeleteObject(font2);
		}
		//보스 죽었을때 대사 띄워주기
		if (_bossImg == IMAGEMANAGER->findImage("얼음죽음"))
		{
			IMAGEMANAGER->findImage("얼음대화")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font3, oldFont3;
			font3 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont3 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font3);
			sprintf_s(str, "제법인데. 쉽게 냉정을 잃지 않는군. 그럼 계속 얼어 있거라!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont3);
			DeleteObject(font3);
		}
	}
}

void iceBoss::update()
{
	if (_iceBossDie == false)//보스가 죽지 않았을때
	{
		//프래임 이미지 카운트
		_frameCount++;
		if (_frameCount % 10 == 0)
		{
			++_iceindex;
			//보스체력이 0보다 클때
			if (_iceCurrentHP > 0)
			{
				//소환 이미지지가 끝나면 등장 모션 띄우고 대화창 띄우기
				if (_bossImg == IMAGEMANAGER->findImage("얼음소환"))
				{
					if (_iceindex > _bossImg->getMaxFrameX())
					{
						_bossImg = IMAGEMANAGER->findImage("얼음등장");
						_iceindex = 0;
						_iceDialogue = true;
					}
				}

				//스페이스키를 눌러 대화창 넘어가기
				if (_iceDialogue == true)
				{
					if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
					{
						_iceMove = true;
						_iceDialogue = false;
					}
				}
				if (_bossImg == IMAGEMANAGER->findImage("얼음등장"))
				{
					if (_iceindex > _bossImg->getMaxFrameX())
					{
						_iceindex = 0;
					}
				}

				if (_bossImg == IMAGEMANAGER->findImage("얼음스킬") || _bossImg == IMAGEMANAGER->findImage("얼음스킬2"))
				{
					if (_iceindex > _bossImg->getMaxFrameX())
					{
						_iceindex = _bossImg->getMaxFrameX();
					}
				}
				_frameCount = 0;
			}
			//보스체력이 0 일때 죽는 모션
			else if (_iceCurrentHP <= 0)
			{
				_bossImg = IMAGEMANAGER->findImage("얼음죽음");
				_iceindex = 0;
				//만약 보스이미지가 죽는 모션이고 스페이스 키를 누르면 보스업데이트와 랜더를 그려주는 변수를 바꿔준다
				if (_bossImg == IMAGEMANAGER->findImage("얼음죽음") && KEYMANAGER->isOnceKeyDown(VK_SPACE))_iceBossDie = true;
			}
		}
		_bossRc = RectMakeCenter(_x, _y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	}
}


void iceBoss::iceMove()
{
	if (_iceMove == true)
	{
		++_bossMoveCount;
		if (_bossMoveCount < 100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
			}
		}
		else if (_bossMoveCount < 400 && _bossMoveCount >= 300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
				_x = WINSIZEX / 2;
				_y = WINSIZEY / 2 + 300;
			}
		}
		else if (_bossMoveCount < 700 && _bossMoveCount >= 600)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
				_x = WINSIZEX / 2;
				_y = WINSIZEY / 2 - 300;
			}
		}
		else if (_bossMoveCount < 1000 && _bossMoveCount >= 900)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
				_x = WINSIZEX / 2 - 300;
				_y = WINSIZEY / 2;
			}
		}
		else if (_bossMoveCount < 1300 && _bossMoveCount >= 1200)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
				_x = WINSIZEX / 2 + 300;
				_y = WINSIZEY / 2;
			}
		}
		else if (_bossMoveCount < 1600 && _bossMoveCount >= 1500)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
				_x = WINSIZEX / 2;
				_y = WINSIZEY / 2;
			}
		}

		else if (_bossMoveCount < 1900 && _bossMoveCount >= 1800)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("얼음등장");
				_woodindex = 0;
				_x = WINSIZEX / 2;
				_y = WINSIZEY / 2;
			}
		}
		else if (_bossMoveCount >= 1900)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossMoveCount = 0;
			}
		}
		///////스킬////////////
		else if ((_bossMoveCount >= 100 && _bossMoveCount < 300) || (_bossMoveCount >= 400 && _bossMoveCount < 600) || (_bossMoveCount < 900 && _bossMoveCount >= 700) ||
			(_bossMoveCount < 1200 && _bossMoveCount >= 1000) || (_bossMoveCount < 1500 && _bossMoveCount >= 1300))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("얼음스킬");
				_iceindex = 0;
			}
		}
		else if (_bossMoveCount < 1800 && _bossMoveCount >= 1600)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("얼음스킬2");
				_iceindex = 0;
			}
		}
	}
}

void iceBoss::iceSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("얼음스킬"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("얼음스킬2"))
	{
	}

}
