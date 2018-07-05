#include "stdafx.h"
#include "Ghoul.h"
#include "player.h"


Ghoul::Ghoul()
{
}


Ghoul::~Ghoul()
{
}

HRESULT Ghoul::init(POINTFLOAT point,int index)
{
	_Astar = new Astar;

	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	_ghoulDirection = GHOUL_RIGHT_STAND; 
	_attackRange = 30;
	_monsterHP = 100;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_speed = 4.0F;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(),10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),
		_image->getFrameHeight());

	sprintf_s(_motionName1, "GhoulMonsterSummon%d", index);
	sprintf_s(_motionName2, "GhoulRightAttack%d", index);
	sprintf_s(_motionName3, "GhoulLeftAttack%d", index);
	sprintf_s(_motionName4, "GhoulRightHit%d", index);
	sprintf_s(_motionName5, "GhoulLeftHit%d", index);

	int Summon[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName1, "SummonMonster", Summon, 29, 10, false, summonOn, this);

	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightStand", "Ghoul", rightStand, 1, 1, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftStand", "Ghoul", leftStand, 1, 1, false);

	int rightMove[] = { 3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightMove", "Ghoul", rightMove, 6, 3, true);
	int leftMove[] = { 13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftMove", "Ghoul", leftMove, 6, 3, true);

	int rightAttack[] = { 1 ,2, 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, "Ghoul", rightAttack, 3, 1, false, rightStop, this);
	int leftAttack[] = { 11 ,12, 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, "Ghoul", leftAttack, 3, 1, false, leftStop, this);

	int rightHit[] = { 20 ,9 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, "Ghoul", rightHit, 2, 3, false , rightStop, this);
	int leftHit[] = { 30 ,19 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, "Ghoul", leftHit, 2, 3, false, leftStop, this);

	int rightDie[] = { 21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightDie", "Ghoul", rightDie, 9, 6, false);
	int leftDie[] = { 31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftDie", "Ghoul", leftDie, 9, 6, false);

	_ghoulMotion = KEYANIMANAGER->findAnimation(_motionName1);


	//=====================================테스트용=======================
	PX = WINSIZEX / 2 + 200;
	PY = WINSIZEY / 2 + 200;
	PRC = RectMakeCenter(PX, PY, 30, 30);
	//=====================================테스트용=======================
	return S_OK;
}

void Ghoul::release()
{
}

void Ghoul::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		PX += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		PX -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		PY -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		PY += 5;
	}
	PRC = RectMakeCenter(PX, PY, 30, 30);


	if (getDistance(_position.x, _position.y, PX, PY) < 100 && _form == CARD)
	{
		_form = SUMMOM;
		getGhoulMotion()->start();
	}

	if (_form == BATTLE)
	{
		ghoulMove();
		Test();
	}
}

void Ghoul::render()
{

	Rectangle(getMemDC(), PRC.left, PRC.top, PRC.right, PRC.bottom);
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _ghoulMotion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void Ghoul::ghoulMove()
{

	if (_ghoulDirection == GHOUL_RIGHT_HIT || _ghoulDirection == GHOUL_LEFT_HIT ||
		_ghoulDirection == GHOUL_RIGHT_DIE || _ghoulDirection == GHOUL_LEFT_DIE) return;

	++_timecnt;

	_angle = getAngle(_position.x, _position.y, PX, PY);
	_bottomPosition.x = _position.x;
	_bottomPosition.y = _position.y + _image->getFrameHeight() / 2;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),
		_image->getFrameHeight());

	if (_attackRange  > getDistance(_position.x, _position.y, PX, PY))
	{

		if (_position.x < PX)
		{
			if (_ghoulDirection == GHOUL_RIGHT_MOVE || _ghoulDirection == GHOUL_RIGHT_STAND)
			{
				_ghoulDirection = GHOUL_RIGHT_ATTACK;
				_ghoulMotion = KEYANIMANAGER->findAnimation(_motionName2);
				_ghoulMotion->start();
			}
		}
		else if (_position.x > PX)
		{

			if (_ghoulDirection == GHOUL_LEFT_MOVE || _ghoulDirection == GHOUL_LEFT_STAND)
			{
				_ghoulDirection = GHOUL_LEFT_ATTACK;
				_ghoulMotion = KEYANIMANAGER->findAnimation(_motionName3);
				_ghoulMotion->start();
			}
		}
	}
	//=====================================테스트용=======================
	else //맵 완성 되면 에이스타로 움직이기!
	{		
		//if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			
			if (_timecnt % (TILESIZE / (int)_speed) == 0)
			{
				//_Astar->readyPath(_Zrc);
				//pathFinder(_currentTile);
				_timecnt = 0;
			}
			//if (_Astar->getEndPosition().x > _position.x) { _dir = DIR_RIGHT; }
			//else if (_Astar->getEndPosition().x < _position.x) { _dir = DIR_LEFT; }
			//else if (_Astar->getEndPosition().y > _position.y) { _dir = DIR_DOWN; }
			//else if (_Astar->getEndPosition().y < _position.y) { _dir = DIR_UP; }

			if (PX > _position.x) { _dir = DIR_RIGHT; }
			else if (PX < _position.x) { _dir = DIR_LEFT; }
			else if (PY > _position.y) { _dir = DIR_DOWN; }
			else if (PY < _position.y) { _dir = DIR_UP; }

			switch (_dir)
			{
			case DIR_LEFT:
				_position.x -= _speed;
				break;
			case DIR_UP:
				_position.y -= _speed;
				break;
			case DIR_RIGHT:
				_position.x += _speed;
				break;
			case DIR_DOWN:
				_position.y += _speed;
				break;
			}

		}


		if (_position.x < PX)
		{
			if (_ghoulDirection == GHOUL_RIGHT_MOVE) return;
			_ghoulDirection = GHOUL_RIGHT_MOVE;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightMove");
			_ghoulMotion->start();

		}
		else if (_position.x > PX)
		{
			if (_ghoulDirection == GHOUL_LEFT_MOVE) return;
			_ghoulDirection = GHOUL_LEFT_MOVE;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulLeftMove");
			_ghoulMotion->start();
		}
	}
	//=====================================테스트용=======================

}

void Ghoul::rightStop(void * obj)
{
	Ghoul* _MonsterGhoul = (Ghoul*)obj;

	_MonsterGhoul->setGhoulDirection(GHOUL_RIGHT_STAND);
	_MonsterGhoul->setGhoulMotion(KEYANIMANAGER->findAnimation("GhoulRightStand"));
	_MonsterGhoul->getGhoulMotion()->start();
}

void Ghoul::leftStop(void * obj)
{

	Ghoul* _MonsterGhoul = (Ghoul*)obj;

	_MonsterGhoul->setGhoulDirection(GHOUL_LEFT_STAND);
	_MonsterGhoul->setGhoulMotion(KEYANIMANAGER->findAnimation("GhoulLeftStand"));
	_MonsterGhoul->getGhoulMotion()->start();
}


void Ghoul::summonOn(void * obj)
{

	Ghoul* _MonsterGhoul = (Ghoul*)obj;

	_MonsterGhoul->setImage(IMAGEMANAGER->findImage("Ghoul"));
	_MonsterGhoul->setForm(BATTLE);
	_MonsterGhoul->setGhoulDirection(GHOUL_LEFT_STAND);
	_MonsterGhoul->setGhoulMotion(KEYANIMANAGER->findAnimation("GhoulLeftStand"));
	_MonsterGhoul->getGhoulMotion()->start();
}


//=====================================테스트용=======================
void Ghoul::Test()
{

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_ghoulDirection == GHOUL_RIGHT_HIT || _ghoulDirection == GHOUL_LEFT_HIT) return;
		if (_ghoulDirection == GHOUL_RIGHT_MOVE || _ghoulDirection == GHOUL_RIGHT_HIT || _ghoulDirection == GHOUL_RIGHT_STAND || _ghoulDirection == GHOUL_RIGHT_ATTACK)
		{
			_ghoulDirection = GHOUL_RIGHT_HIT;
			_ghoulMotion = KEYANIMANAGER->findAnimation(_motionName4);
			_ghoulMotion->start();
		}
		else if (_ghoulDirection == GHOUL_LEFT_MOVE || _ghoulDirection == GHOUL_LEFT_HIT || _ghoulDirection == GHOUL_LEFT_STAND || _ghoulDirection == GHOUL_LEFT_ATTACK)
		{
			_ghoulDirection = GHOUL_LEFT_HIT;
			_ghoulMotion = KEYANIMANAGER->findAnimation(_motionName5);
			_ghoulMotion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_ghoulDirection == GHOUL_RIGHT_DIE || _ghoulDirection == GHOUL_LEFT_DIE) return;
		if (_ghoulDirection == GHOUL_RIGHT_MOVE || _ghoulDirection == GHOUL_RIGHT_HIT)
		{
			_ghoulDirection = GHOUL_RIGHT_DIE;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightDie");
			_ghoulMotion->start();
		}
		else if (_ghoulDirection == GHOUL_LEFT_MOVE || _ghoulDirection == GHOUL_LEFT_HIT)
		{
			_ghoulDirection = GHOUL_LEFT_DIE;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulLeftDie");
			_ghoulMotion->start();
		}
	}
}
