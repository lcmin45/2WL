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
	if (_woodBossDie == false)//������ ���� �ʾ�����
	{
		char str[256];

		_bossImg->frameRender(getMemDC(), _bossRc.left, _bossRc.top, _woodindex, 0);

		_woodHpBar->render();

		//���� ���� �Ҷ� ��� ����ֱ�
		if (_woodDialogue == true)
		{
			IMAGEMANAGER->findImage("������ȭ")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font2, oldFont2;
			font2 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont2 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font2);
			sprintf_s(str, "���鼭 �뱸���̿��� �� �����⸦ �ٶ���...���� ���� ��Ʈ�� �Ŵϱ�!!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont2);
			DeleteObject(font2);
		}
		//�׾����� ��� ����ֱ�
		if (_bossImg == IMAGEMANAGER->findImage("��������"))
		{
			IMAGEMANAGER->findImage("������ȭ")->render(CAMERAMANAGER->getCameraDC(), 200, 600);

			SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(255, 255, 255));
			SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);

			HFONT font3, oldFont3;
			font3 = CreateFont(20, 0, 0, 0, 1300, false, false, false, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Times New Roman"));
			oldFont3 = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font3);
			sprintf_s(str, "�������� ���� ������ ���決..�� ����,���� ���� �ǳʾ� �� �״�!");
			TextOut(CAMERAMANAGER->getCameraDC(), 360, 670, str, strlen(str));
			SelectObject(CAMERAMANAGER->getCameraDC(), oldFont3);
			DeleteObject(font3);
		}
	}
}

void woodBoss::update()
{
	if (_woodBossDie == false)//������ ���� �ʾ�����
	{
		_woodHpBar->setGauge(_woodCurrentHP, _woodMaxHP);
		_woodHpBar->update();
		//������ �̹��� ī��Ʈ
		_frameCount++;
		if (_frameCount % 10 == 0)
		{
			++_woodindex;
			//����ü���� 0�� �ƴҶ�
			if (_woodCurrentHP > 0)
			{
				//��ȯ ����� ������ �����ǰ� ��ȭâ ���� bgm����
				if (_bossImg == IMAGEMANAGER->findImage("������ȯ"))
				{
					if (_woodindex > _bossImg->getMaxFrameX())
					{
						_bossImg = IMAGEMANAGER->findImage("��������");
						_woodindex = 0;
						_woodDialogue = true;
						SOUNDMANAGER->singleChannelPlay("Boss");
					}
				}
				//�����̽�Ű�� ������ ��ȭâ �Ѿ��
				if (_woodDialogue == true)
				{
					if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
					{
						_woodMove = true;
						_woodDialogue = false;
					}
				}

				if (_bossImg == IMAGEMANAGER->findImage("��������"))
				{
					if (_woodindex > _bossImg->getMaxFrameX())
					{
						_woodindex = 0;
					}
				}

				if (_bossImg == IMAGEMANAGER->findImage("����������") || _bossImg == IMAGEMANAGER->findImage("��������"))
				{
					if (_woodindex > _bossImg->getMaxFrameX())
					{
						_woodindex = 0;
					}
				}
				if (_bossImg == IMAGEMANAGER->findImage("��������") || _bossImg == IMAGEMANAGER->findImage("������ų") || _bossImg == IMAGEMANAGER->findImage("������ų2������") ||
					_bossImg == IMAGEMANAGER->findImage("������ų2����") || _bossImg == IMAGEMANAGER->findImage("��������") || _bossImg == IMAGEMANAGER->findImage("�����������ǰ�") || _bossImg == IMAGEMANAGER->findImage("�����ǰ�"))
				{
					if (_woodindex > _bossImg->getMaxFrameX())
					{
						_woodindex = _bossImg->getMaxFrameX();
					}
				}

				_frameCount = 0;
			}
			//���� ü���� 0�ϋ� �״� ���
			else if (_woodCurrentHP <= 0)
			{
				_bossImg = IMAGEMANAGER->findImage("��������");
				_woodindex = 0;
				//���� �����̹����� �״� ����̰� �����̽� Ű�� ������ ����������Ʈ�� ������ �׷��ִ� ������ �ٲ��ش�
				if (_bossImg == IMAGEMANAGER->findImage("��������") && KEYMANAGER->isOnceKeyDown(VK_SPACE))
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
				if (_x > _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("��������");
				else if (_x < _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("����������");
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
				if (_x < _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("������ų2������");
				else if (_x > _playerPosition.x)_bossImg = IMAGEMANAGER->findImage("������ų2����");
				_woodindex = 0;
			}
		}

		else if (_bossMoveCount >= 200 && _bossMoveCount<260)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("������ų");
				_woodindex = 0;
			}
		}

		else if (_bossMoveCount >= 460 && _bossMoveCount<660)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("��������");
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
	if (_bossImg == IMAGEMANAGER->findImage("������ų"))
	{
		if (_skill == false)
		{
			_ptM->fire("�����ڱ�", { _x, _y });
			_skill = true;
		}
	}

	else if (_bossImg == IMAGEMANAGER->findImage("������ų2����"))
	{
		if (_skill == false)
		{
			_ptM->fire("��������", { _x, _y });
			_skill = true;
		}
	}

	else if (_bossImg == IMAGEMANAGER->findImage("������ų2������"))
	{
		if (_skill == false)
		{
			_ptM->fire("��������", { _x, _y });
			_skill = true;
		}
	}
}
