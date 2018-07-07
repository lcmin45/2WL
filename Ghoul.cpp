#include "stdafx.h"
#include "Ghoul.h"


Ghoul::Ghoul()
{
}


Ghoul::~Ghoul()
{
}

HRESULT Ghoul::init(POINTFLOAT point,int index, int monsterRoomIndex)
{
	_Astar = new Astar;
	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	_Direction = RIGHT_STAND; 
	_attackRange = 64;
	_monsterHP = 100;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_timecnt = 32;
	_speed = 1.0F;
	_monsterIndex = monsterRoomIndex;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(),10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),	_image->getFrameHeight());

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
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, "Ghoul", rightAttack, 3,3, false, rightStop, this);
	int leftAttack[] = { 11 ,12, 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, "Ghoul", leftAttack, 3, 3, false, leftStop, this);

	int rightHit[] = { 20 ,9 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, "Ghoul", rightHit, 2, 3, false , rightStop, this);
	int leftHit[] = { 30 ,19 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, "Ghoul", leftHit, 2, 3, false, leftStop, this);

	int rightDie[] = { 21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightDie", "Ghoul", rightDie, 9, 6, false);
	int leftDie[] = { 31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftDie", "Ghoul", leftDie, 9, 6, false);

	_Motion = KEYANIMANAGER->findAnimation(_motionName1);

	return S_OK;
}

void Ghoul::release()
{
}

void Ghoul::update()
{
	_distance = getDistance(_position.x, _position.y, _playerPosition.x, _playerPosition.y);
	_angle = getAngle(_position.x, _position.y, _playerPosition.x, _playerPosition.y);

	if (_playerIndex == _monsterIndex && _form == CARD)
	{
		_form = SUMMOM;
		getMotion()->start();
	}

	if (_form == BATTLE)
	{
		ghoulMove();
		Test();
	}
}

void Ghoul::render()
{

	_image->aniRender(getMemDC(), _rc.left, _rc.top, _Motion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

}

void Ghoul::ghoulMove()
{

	if (_Direction == RIGHT_HIT || _Direction == LEFT_HIT ||
		_Direction == RIGHT_DIE || _Direction == LEFT_DIE) return;

	++_timecnt;

	_position.x = _bottomPosition.x;
	_position.y = _bottomPosition.y - _image->getFrameHeight() / 2;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),	_image->getFrameHeight());

	if (_attackRange  > _distance)
	{

		if (_bottomPosition.x < _playerPosition.x)
		{
			if (_Direction == RIGHT_MOVE || _Direction == RIGHT_STAND)
			{
				_Direction = RIGHT_ATTACK;
				_Motion = KEYANIMANAGER->findAnimation(_motionName2);
				_Motion->start();
			}
		}
		else if (_bottomPosition.x > _playerPosition.x)
		{

			if (_Direction == LEFT_MOVE || _Direction == LEFT_STAND)
			{
				_Direction = LEFT_ATTACK;
				_Motion = KEYANIMANAGER->findAnimation(_motionName3);
				_Motion->start();
			}
		}
	}
	else //에이스타 움직임
	{
		if (_timecnt % 33 == 0)
		{
			_endPosition = _Astar->readyPath(_bottomPosition);
			_timecnt = 0;
		}
		else
		{
			if (_endPosition.x > _bottomPosition.x) { _bottomPosition.x += (int)_speed; }
			if (_endPosition.x < _bottomPosition.x) { _bottomPosition.x -= (int)_speed; }
			if (_endPosition.y > _bottomPosition.y) { _bottomPosition.y += (int)_speed; }
			if (_endPosition.y < _bottomPosition.y) { _bottomPosition.y -= (int)_speed; }
		}


		if (_bottomPosition.x < _playerPosition.x)
		{
			if (_Direction == RIGHT_MOVE) return;
			_Direction = RIGHT_MOVE;
			_Motion = KEYANIMANAGER->findAnimation("GhoulRightMove");
			_Motion->start();

		}
		else if (_bottomPosition.x > _playerPosition.x)
		{
			if (_Direction == LEFT_MOVE) return;
			_Direction = LEFT_MOVE;
			_Motion = KEYANIMANAGER->findAnimation("GhoulLeftMove");
			_Motion->start();
		}
	}

}

void Ghoul::rightStop(void * obj)
{
	Ghoul* _MonsterGhoul = (Ghoul*)obj;

	_MonsterGhoul->setMonsterDirection(RIGHT_STAND);
	_MonsterGhoul->setMotion(KEYANIMANAGER->findAnimation("GhoulRightStand"));
	_MonsterGhoul->getMotion()->start();
}

void Ghoul::leftStop(void * obj)
{

	Ghoul* _MonsterGhoul = (Ghoul*)obj;

	_MonsterGhoul->setMonsterDirection(LEFT_STAND);
	_MonsterGhoul->setMotion(KEYANIMANAGER->findAnimation("GhoulLeftStand"));
	_MonsterGhoul->getMotion()->start();
}


void Ghoul::summonOn(void * obj)
{

	Ghoul* _MonsterGhoul = (Ghoul*)obj;

	_MonsterGhoul->setImage(IMAGEMANAGER->findImage("Ghoul"));
	_MonsterGhoul->setForm(BATTLE);
	_MonsterGhoul->setMonsterDirection(LEFT_STAND);
	_MonsterGhoul->setMotion(KEYANIMANAGER->findAnimation("GhoulLeftStand"));
	_MonsterGhoul->getMotion()->start();
}


void Ghoul::Test()
{

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_Direction == RIGHT_HIT  || _Direction ==LEFT_HIT) return;
		if (_Direction == RIGHT_MOVE || _Direction ==RIGHT_HIT || _Direction == RIGHT_STAND || _Direction == RIGHT_ATTACK)
		{
			_Direction = RIGHT_HIT;
			_Motion = KEYANIMANAGER->findAnimation(_motionName4);
			_Motion->start();
		}
		else if (_Direction == LEFT_MOVE || _Direction == LEFT_HIT || _Direction == LEFT_STAND || _Direction == LEFT_ATTACK)
		{
			_Direction = LEFT_HIT;
			_Motion = KEYANIMANAGER->findAnimation(_motionName5);
			_Motion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_Direction == RIGHT_DIE  || _Direction ==LEFT_DIE) return;
		if (_Direction == RIGHT_MOVE || _Direction ==RIGHT_HIT)
		{
			_Direction = RIGHT_DIE;
			_Motion = KEYANIMANAGER->findAnimation("GhoulRightDie");
			_Motion->start();
		}
		else if (_Direction == LEFT_MOVE || _Direction == LEFT_HIT)
		{
			_Direction = LEFT_DIE;
			_Motion = KEYANIMANAGER->findAnimation("GhoulLeftDie");
			_Motion->start();
		}
	}
}

