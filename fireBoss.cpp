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
	if (_fireBossDie == false)//������ ��� ������
	{
		char str[256];

		_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _fireindex, 0);

		_fireHpBar->render();

		//���� ���� �Ҷ� ��� ����ֱ�
		if (_fireDialogue == true)
		{
			IMAGEMANAGER->findImage("�Ҵ�ȭ")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font2, oldFont2;
			font2 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont2 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font2);
			sprintf_s(str, "���� ���� �ȴ�������? �׷� ���� ���� ��������!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont2);
			DeleteObject(font2);
		}
		//���� ������ ��� ����ֱ�
		if (_bossImg == IMAGEMANAGER->findImage("������"))
		{
			IMAGEMANAGER->findImage("�Ҵ�ȭ")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font3, oldFont3;
			font3 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont3 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font3);
			sprintf_s(str, "�̹��� ���� ����� �پ���! ������ũ�� ���� �ֱ� �ٶ���!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont3);
			DeleteObject(font3);
		}
	}
}

void fireBoss::update()
{
	if (_fireBossDie == false)//������ ���������
	{
		_fireHpBar->setGauge(_fireCurrentHP, _fireMaxHP);
		_fireHpBar->update();
		//������ �̹��� ī��Ʈ
		_frameCount++;
		if (_frameCount % 10 == 0)
		{
			++_fireindex;
			//���� ü���� 0���� Ŭ��
			if (_fireCurrentHP > 0)
			{
				//��ȯ ����� ������ ���� ��Ƕ��� ��ȭâ ���� bgm����
				if (_bossImg == IMAGEMANAGER->findImage("�Ҽ�ȯ"))
				{
					if (_fireindex > _bossImg->getMaxFrameX())
					{
						_bossImg = IMAGEMANAGER->findImage("�ҵ���");
						_fireindex = 0;
						_fireDialogue = true;
						SOUNDMANAGER->singleChannelPlay("Boss");
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

				if (_bossImg == IMAGEMANAGER->findImage("�ҵ���"))
				{
					if (_fireindex > _bossImg->getMaxFrameX())
					{
						_fireindex = 0;
					}
				}
				if (_bossImg == IMAGEMANAGER->findImage("�ҽ�ų������") || _bossImg == IMAGEMANAGER->findImage("�ҽ�ų����")
					|| _bossImg == IMAGEMANAGER->findImage("�ҽ�ų2") || _bossImg == IMAGEMANAGER->findImage("�ҿ�����") || _bossImg == IMAGEMANAGER->findImage("�ҿ���"))
				{
					if (_fireindex > _bossImg->getMaxFrameX())
					{
						_fireindex = _bossImg->getMaxFrameX();
					}
				}
				_frameCount = 0;
			}
			//���� ü���� 0�϶� �״� ���
			else if (_fireCurrentHP <= 0)
			{
				_bossImg = IMAGEMANAGER->findImage("������");
				_fireindex = 0;
				//���� �����̹����� �״� ����̰� �����̽� Ű�� ������ ����������Ʈ�� ������ �׷��ִ� ������ �ٲ��ش�
				if (_bossImg == IMAGEMANAGER->findImage("������") && KEYMANAGER->isOnceKeyDown(VK_SPACE))
				{
					_fireBossDie = true;
					SOUNDMANAGER->singleChannelPlay("Earth");
				}
			}
		}
		_bossRc = RectMakeCenter(_x, _y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	}
}


void fireBoss::fireMove()
{
	if (_fireMove == true)
	{
		++_bossMoveCount;
		//�밢�� �̵�
		if (_bossMoveCount < 100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҿ���");
				_fireindex = 0;
				_skill = false;
			}
			_x -= 4;
			_y += 3;
		}
		else if (_bossMoveCount < 500 && _bossMoveCount >= 300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҿ�����");
				_fireindex = 0;
				_skill = false;
			}
			_x += 4;
			_y -= 2;
		}
		//�߾����� �̵�
		else if (_bossMoveCount < 800 && _bossMoveCount >= 700)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҿ���");
				_fireindex = 0;
				_skill = false;
			}
			_x -= 4;
			_y += 2;
		}

		else if (_bossMoveCount < 1100 && _bossMoveCount >= 1000)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҿ���");
				_fireindex = 0;
				_skill = false;
			}
			_x -= 4;
			_y -= 3;
		}
		else if (_bossMoveCount < 1500 && _bossMoveCount >= 1300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҿ�����");
				_fireindex = 0;
				_skill = false;
			}
			_x += 4;
			_y += 2;
		}
		//�߾����� �̵�
		else if (_bossMoveCount < 1800 && _bossMoveCount >= 1700)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҿ���");
				_fireindex = 0;
				_skill = false;
			}
			_x -= 4;
			_y -= 2;
		}
		else if (_bossMoveCount < 2200 && _bossMoveCount >= 2000)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("�ҵ���");
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

		//////////////////////��ų ���////////////////
		else if ((_bossMoveCount < 300 && _bossMoveCount >= 100) || (_bossMoveCount < 1300 && _bossMoveCount >= 1100))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("�ҽ�ų������");
				_fireindex = 0;
			}
		}
		else if ((_bossMoveCount < 700 && _bossMoveCount >= 500) || (_bossMoveCount < 1700 && _bossMoveCount >= 1500))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("�ҽ�ų����");
				_fireindex = 0;
			}
		}
		else if ((_bossMoveCount < 1000 && _bossMoveCount >= 800) || (_bossMoveCount < 2000 && _bossMoveCount >= 1800))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("�ҽ�ų2");
				_fireindex = 0;
			}
		}
	}
}

void fireBoss::fireSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("�ҽ�ų����"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("�ҽ�ų������"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("�ҽ�ų2"))
	{
	}

}
