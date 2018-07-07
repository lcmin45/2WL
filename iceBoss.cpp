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
	if (_iceBossDie == false)//������ ���� �ʾ�����
	{
		char str[256];

		_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _iceindex, 0);

		_iceHpBar->render();

		//���� ���� �Ҷ� ��� ����ֱ�
		if (_iceDialogue == true)
		{
			IMAGEMANAGER->findImage("������ȭ")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font2, oldFont2;
			font2 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont2 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font2);
			sprintf_s(str, "�׷��� ������� �̹� �ʾ���..�� �ڸ��� �״�� ����ָ�!!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont2);
			DeleteObject(font2);
		}
		//���� �׾����� ��� ����ֱ�
		if (_bossImg == IMAGEMANAGER->findImage("��������"))
		{
			IMAGEMANAGER->findImage("������ȭ")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font3, oldFont3;
			font3 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont3 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font3);
			sprintf_s(str, "�����ε�. ���� ������ ���� �ʴ±�. �׷� ��� ��� �ְŶ�!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont3);
			DeleteObject(font3);
		}
	}
}

void iceBoss::update()
{
	if (_iceBossDie == false)//������ ���� �ʾ�����
	{
		//������ �̹��� ī��Ʈ
		_frameCount++;
		if (_frameCount % 10 == 0)
		{
			++_iceindex;
			//����ü���� 0���� Ŭ��
			if (_iceCurrentHP > 0)
			{
				//��ȯ �̹������� ������ ���� ��� ���� ��ȭâ ����
				if (_bossImg == IMAGEMANAGER->findImage("������ȯ"))
				{
					if (_iceindex > _bossImg->getMaxFrameX())
					{
						_bossImg = IMAGEMANAGER->findImage("��������");
						_iceindex = 0;
						_iceDialogue = true;
					}
				}

				//�����̽�Ű�� ���� ��ȭâ �Ѿ��
				if (_iceDialogue == true)
				{
					if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
					{
						_iceMove = true;
						_iceDialogue = false;
					}
				}
				if (_bossImg == IMAGEMANAGER->findImage("��������"))
				{
					if (_iceindex > _bossImg->getMaxFrameX())
					{
						_iceindex = 0;
					}
				}

				if (_bossImg == IMAGEMANAGER->findImage("������ų") || _bossImg == IMAGEMANAGER->findImage("������ų2"))
				{
					if (_iceindex > _bossImg->getMaxFrameX())
					{
						_iceindex = _bossImg->getMaxFrameX();
					}
				}
				_frameCount = 0;
			}
			//����ü���� 0 �϶� �״� ���
			else if (_iceCurrentHP <= 0)
			{
				_bossImg = IMAGEMANAGER->findImage("��������");
				_iceindex = 0;
				//���� �����̹����� �״� ����̰� �����̽� Ű�� ������ ����������Ʈ�� ������ �׷��ִ� ������ �ٲ��ش�
				if (_bossImg == IMAGEMANAGER->findImage("��������") && KEYMANAGER->isOnceKeyDown(VK_SPACE))_iceBossDie = true;
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
				_bossImg = IMAGEMANAGER->findImage("��������");
				_woodindex = 0;
			}
		}
		else if (_bossMoveCount < 400 && _bossMoveCount >= 300)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("��������");
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
		///////��ų////////////
		else if ((_bossMoveCount >= 100 && _bossMoveCount < 300) || (_bossMoveCount >= 400 && _bossMoveCount < 600) || (_bossMoveCount < 900 && _bossMoveCount >= 700) ||
			(_bossMoveCount < 1200 && _bossMoveCount >= 1000) || (_bossMoveCount < 1500 && _bossMoveCount >= 1300))
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("������ų");
				_iceindex = 0;
			}
		}
		else if (_bossMoveCount < 1800 && _bossMoveCount >= 1600)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("������ų2");
				_iceindex = 0;
			}
		}
	}
}

void iceBoss::iceSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("������ų"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("������ų2"))
	{
	}

}
