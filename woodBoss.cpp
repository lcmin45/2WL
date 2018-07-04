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
		////////��� �׷��ֱ�
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
}

void woodBoss::update()
{
	//������ �̹��� ī��Ʈ
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		++_woodindex;
		//����ü���� 0�� �ƴҶ�
		if (_woodCurrentHP > 0)
		{
			//��ȯ ����� ������ �����ǰ� ��ȭâ ����
			if (_bossImg == IMAGEMANAGER->findImage("������ȯ"))
			{
				if (_woodindex > _bossImg->getMaxFrameX())
				{
					_bossImg = IMAGEMANAGER->findImage("��������");
					_woodindex = 0;
					_woodDialogue = true;
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
		}
	}
	_bossRc = RectMakeCenter((int)_x, (int)_y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
}


void woodBoss::woodMove()
{
	if (_woodMove == true)
	{
		++_bossMoveCount;
		//�÷��̾� ��ǥ �޾ƿͼ� �¿�� �̵��ϱ�
		if (_bossMoveCount < 100)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("����������");
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

		//�÷��̾� ��ġ�� �����ϱ� 
		else if (_bossMoveCount < 700 && _bossMoveCount >= 600)
		{
			if (!_isCheck)
			{
				_isCheck = true;
				_bossImg = IMAGEMANAGER->findImage("��������");
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
				_bossImg = IMAGEMANAGER->findImage("��������");
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

		/////////////////��ų���/////////////////////
		else if (_bossMoveCount >= 100 && _bossMoveCount < 300)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("������ų2������");
				_woodindex = 0;
			}
		}
		else if (_bossMoveCount < 600 && _bossMoveCount >= 400)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("������ų2����");
				_woodindex = 0;
			}
		}
		else if (_bossMoveCount >= 700 && _bossMoveCount < 900)
		{
			if (_isCheck)
			{
				_isCheck = false;
				_bossImg = IMAGEMANAGER->findImage("������ų");
				_woodindex = 0;
			}
		}
	}
}

void woodBoss::woodSkill()
{
	if (_bossImg == IMAGEMANAGER->findImage("������ų"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("������ų2����"))
	{
	}

	else if (_bossImg == IMAGEMANAGER->findImage("������ų2������"))
	{
	}
}
