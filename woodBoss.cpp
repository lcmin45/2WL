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
	if (_woodBossDie == false)//보스가 죽지 않았을때
	{
		char str[256];

		_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _woodindex, 0);

		_woodHpBar->render();

		//보스 등장 할때 대사 띄워주기
		if (_woodDialogue == true)
		{
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
		//죽었을때 대사 띄어주기
		if (_bossImg == IMAGEMANAGER->findImage("나무죽음"))
		{
			IMAGEMANAGER->findImage("나무대화")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font3, oldFont3;
			font3 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont3 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font3);
			sprintf_s(str, "바위보다 강한 의지를 지녔군..잘 가길,고난의 땅을 건너야 할 테니!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont3);
			DeleteObject(font3);
		}
	}
}

void woodBoss::update()
{
	if (_woodBossDie == false)//보스가 죽지 않았을때
	{
		_woodHpBar->setGauge(_woodCurrentHP, _woodMaxHP);
		_woodHpBar->update();
		//프래임 이미지 카운트
		_frameCount++;
		if (_frameCount % 10 == 0)
		{
			++_woodindex;
			//보스체력이 0이 아닐때
			if (_woodCurrentHP > 0)
			{
				//소환 모션이 끝나면 등장모션과 대화창 띄우기 bgm실행
				if (_bossImg == IMAGEMANAGER->findImage("나무소환"))
				{
					if (_woodindex > _bossImg->getMaxFrameX())
					{
						_bossImg = IMAGEMANAGER->findImage("나무등장");
						_woodindex = 0;
						_woodDialogue = true;
						SOUNDMANAGER->singleChannelPlay("Boss");
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
				//만약 보스이미지가 죽는 모션이고 스페이스 키를 누르면 보스업데이트와 랜더를 그려주는 변수를 바꿔준다
				if (_bossImg == IMAGEMANAGER->findImage("나무죽음") && KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					_woodBossDie = true;
					SOUNDMANAGER->singleChannelPlay("Earth");
				}
			}
		}
		_bossRc = RectMakeCenter(_x, _y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());

	}
}


void woodBoss::woodMove()
{

	if (_woodMove == true)
	{
		++_bossMoveCount;

		if (_bossMoveCount < 100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				if (_x > _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("나무왼쪽");
				else if (_x < _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("나무오른쪽");
				_woodindex = 0;
				_angle = getAngle(_x, _y, _playerPosition.x, _playerPosition.y);
				_distance = getDistance(_x, _y, _playerPosition.x, _playerPosition.y);
				_skill = false;
			}
			if (_distance < 10)
			{
			}
			else
			{
				if ((_bossRc.left>4736) && (_bossRc.right<5920) && (_bossRc.top>64) && (_bossRc.bottom<640))
				{
					_x += cos(_angle) * _speed;
					_y += -sin(_angle) * _speed;
				}
			}
		}

		else if (_bossMoveCount >= 100 && _bossMoveCount < 200)
		{
			if (_isCheck)
			{
				_isCheck = false;
				if (_x < _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("나무스킬2오른쪽");
				else if (_x > _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("나무스킬2왼쪽");
				_woodindex = 0;
			}
		}

		else if (_bossMoveCount >= 200 && _bossMoveCount<260)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("나무점프");
				_woodindex = 0;
				_angle = getAngle(_x, _y, _playerPosition.x, _playerPosition.y);
				_distance = getDistance(_x, _y, _playerPosition.x, _playerPosition.y);
				_skill = false;
			}
			if (_distance < 10)
			{
			}
			else
			{
				_jump += 0.1f;
				_x += cos(_angle) * _speed;
				if (_y >_playerPosition.y)_y += -sin(_angle) * 13 + _jump;
				else if (_y < _playerPosition.y)
				{
					if (_bossMoveCount >= 200 && _bossMoveCount<220)_y -= 3;
					else _y += -sin(_angle) * _speed;
				}
			}
		}

		else if (_bossMoveCount >= 260 && _bossMoveCount < 460)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("나무스킬");
				_woodindex = 0;
			}
		}

		else if (_bossMoveCount >= 460 && _bossMoveCount<660)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("나무등장");
				_woodindex = 0;
				_skill = false;
			}
		}

		else if (_bossMoveCount >= 660)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossMoveCount = 0;
				_jump = 0.0f;
			}
		}
	}
}

void woodBoss::woodSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("나무스킬"))
	{
		if (_skill == false)
		{
			_ptM->fire("나무솟기", { _x, _y });
			_skill = true;
		}
	}

	else if (_bossImg == IMAGEMANAGER->findImage("나무스킬2왼쪽"))
	{
		if (_skill == false)
		{
			_ptM->fire("돌던지기", { _x, _y });
			_skill = true;
		}
	}

	else if (_bossImg == IMAGEMANAGER->findImage("나무스킬2오른쪽"))
	{
		if (_skill == false)
		{
			_ptM->fire("돌던지기", { _x, _y });
			_skill = true;
		}
	}
}
