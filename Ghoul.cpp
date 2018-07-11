#include "stdafx.h"
#include "Ghoul.h"


Ghoul::Ghoul()
{
}


Ghoul::~Ghoul()
{
}

HRESULT Ghoul::init(POINTFLOAT point, int monsterRoomIndex)
{
	_Astar = new Astar;
	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	_Direction = RIGHT_STAND; 
	_attackRange = 80;
	_monsterHP = 100;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_timecnt = 32;
	_speed = 1.0F;
	_monsterIndex = monsterRoomIndex;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(),10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),	_image->getFrameHeight());
	_keyIndex = int(point.x + point.y+ monsterRoomIndex);

	sprintf_s(_motionName1, "GhoulMonsterSummon%d", _keyIndex);
	sprintf_s(_motionName2, "GhoulRightAttack%d", _keyIndex);
	sprintf_s(_motionName3, "GhoulLeftAttack%d", _keyIndex);
	sprintf_s(_motionName4, "GhoulRightHit%d", _keyIndex);
	sprintf_s(_motionName5, "GhoulLeftHit%d", _keyIndex);
	sprintf_s(_motionName6, "GhoulRightDie%d", _keyIndex);
	sprintf_s(_motionName7, "GhoulLeftDie%d", _keyIndex);

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

	int rightAttack[] = { 1 , 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, "Ghoul", rightAttack, 2, 8, false, rightStop, this);
	int leftAttack[] = { 11 , 12 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, "Ghoul", leftAttack, 2, 8, false, leftStop, this);

	int rightHit[] = { 20 ,9 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, "Ghoul", rightHit, 2, 3, false , rightStop, this);
	int leftHit[] = { 30 ,19 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, "Ghoul", leftHit, 2, 3, false, leftStop, this);

	int rightDie[] = { 21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName6, "Ghoul", rightDie, 9, 6, false, MonsterDie,this);
	int leftDie[] = { 31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName7, "Ghoul", leftDie, 9, 6, false, MonsterDie, this);

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
		SOUNDMANAGER->play("EnemySummon");
		_form = SUMMOM;
		getMotion()->start();
	}

	if (_form == BATTLE)
	{
		ghoulMove();
		Die();
		Test();
	}
}

void Ghoul::render()
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		if (_Astar->getTotalTile().size() != 0)
		{
			for (int i = 0; i < _Astar->getTotalTile().size(); ++i)
			{
				RectangleMakeCenter(getMemDC(), _Astar->getTotalTile()[i]->getCenter().x, _Astar->getTotalTile()[i]->getCenter().y, 32, 32);
			}
		}
	}	


	if (KEYMANAGER->isToggleKey(VK_F2))
	{
		if (_Astar->getOpen().size() != 0)
		{
			for (int i = 0; i < _Astar->getOpen().size(); ++i)
			{
				RectangleMakeCenter(getMemDC(), _Astar->getOpen()[i]->getCenter().x, _Astar->getOpen()[i]->getCenter().y, 32, 32);
			}
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F3))
	{
		if (_Astar->getClose().size() != 0)
		{
			for (int i = 0; i < _Astar->getClose().size(); ++i)
			{
				RectangleMakeCenter(getMemDC(), _Astar->getClose()[i]->getCenter().x, _Astar->getClose()[i]->getCenter().y, 32, 32);
			}
		}
	}

	if (KEYMANAGER->isToggleKey(VK_F4))
	{
		if (_Astar->getEndTile().size() != 0)
		{
			for (int i = 0; i < _Astar->getEndTile().size(); ++i)
			{
				RectangleMakeCenter(getMemDC(), _Astar->getEndTile()[i]->getCenter().x, _Astar->getEndTile()[i]->getCenter().y, 32, 32);
			}
		}
	}
	

	_image->aniRender(getMemDC(), _rc.left, _rc.top, _Motion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

}

void Ghoul::ghoulMove()
{
	_position.x = _bottomPosition.x;
	_position.y = _bottomPosition.y - _image->getFrameHeight() / 2;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(), _image->getFrameHeight());

	if (_form == DIE) return;
	if (_Direction == RIGHT_HIT || _Direction == LEFT_HIT ||
		_Direction == RIGHT_DIE || _Direction == LEFT_DIE ||
		_Direction == RIGHT_ATTACK || _Direction == LEFT_ATTACK) return;

	++_timecnt;



	if (_attackReady == false)
	{
		if (_attackCount >= 100)
		{
			_attackReady = true;
			_attackCount = 0;
		}
		else ++_attackCount;
	}

	if (_attackRange  > _distance )
	{
		if (!_attackReady) return;
		if (_bottomPosition.x < _playerPosition.x)
		{
			if (_Direction == RIGHT_MOVE || _Direction == RIGHT_STAND)
			{
				_Direction = RIGHT_ATTACK;
				_Motion = KEYANIMANAGER->findAnimation(_motionName2);
				_Motion->start();
				_PM->fire("GhoulBullet", _position);
				SOUNDMANAGER->play("GhoulAttack");
				_attackReady = false;
			}
		}
		else if (_bottomPosition.x > _playerPosition.x)
		{

			if (_Direction == LEFT_MOVE || _Direction == LEFT_STAND)
			{
				_Direction = LEFT_ATTACK;
				_Motion = KEYANIMANAGER->findAnimation(_motionName3);
				_Motion->start();
				_PM->fire("GhoulBullet", _position);
				SOUNDMANAGER->play("GhoulAttack");
				_attackReady = false;
			}
		}
	}
	else //에이스타 움직임
	{
		//_endPosition = _Astar->readyPath(_bottomPosition, _monsterIndex);
		if (_timecnt % 33 == 0)
		{
			_endPosition = _Astar->readyPath(_bottomPosition, _monsterIndex);
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
	if (_MonsterGhoul->getForm() == DIE) return;
	_MonsterGhoul->setMonsterDirection(RIGHT_STAND);
	_MonsterGhoul->setMotion(KEYANIMANAGER->findAnimation("GhoulRightStand"));
	_MonsterGhoul->getMotion()->start();
}

void Ghoul::leftStop(void * obj)
{

	Ghoul* _MonsterGhoul = (Ghoul*)obj;
	if (_MonsterGhoul->getForm() == DIE) return;
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

void Ghoul::MonsterDie(void * obj)
{
	Ghoul* _MonsterGhoul = (Ghoul*)obj;
	_MonsterGhoul->_isDie = true;
}


void Ghoul::Test()
{

	if (KEYMANAGER->isOnceKeyDown('O')) _monsterHP = 0;
}

void Ghoul::HitMotion()
{
	
		if (_form == DIE) return;
		if (_Direction == RIGHT_HIT || _Direction == LEFT_HIT) return;
		if (_Direction == RIGHT_MOVE || _Direction == RIGHT_STAND || _Direction == RIGHT_ATTACK)
		{
			SOUNDMANAGER->play("EnemyHurt");
			_Direction = RIGHT_HIT;
			_Motion = KEYANIMANAGER->findAnimation(_motionName4);
			_Motion->start();
		}
		else if (_Direction == LEFT_MOVE || _Direction == LEFT_STAND || _Direction == LEFT_ATTACK)
		{
			SOUNDMANAGER->play("EnemyHurt");
			_Direction = LEFT_HIT;
			_Motion = KEYANIMANAGER->findAnimation(_motionName5);
			_Motion->start();
		}
}

void Ghoul::Die()
{
	if (_monsterHP <= 0)
	{
		if (_form == DIE) return;
		if (_Direction == RIGHT_MOVE || _Direction == RIGHT_HIT || _Direction == RIGHT_STAND)
		{
			SOUNDMANAGER->play("GhoulDie" );
			_Direction = RIGHT_DIE;
			_form = DIE;
			_Motion = KEYANIMANAGER->findAnimation(_motionName6);
			_Motion->start();
		}
		else if (_Direction == LEFT_MOVE || _Direction == LEFT_HIT || _Direction == LEFT_STAND)
		{
			SOUNDMANAGER->play("GhoulDie" );
			_Direction = LEFT_DIE;
			_form = DIE;
			_Motion = KEYANIMANAGER->findAnimation(_motionName7);
			_Motion->start();
		}
	}
}

