#include "stdafx.h"
#include "Rogue.h"


Rogue::Rogue()
{
}


Rogue::~Rogue()
{ 
}

HRESULT Rogue::init(const char * imgName, POINTFLOAT point, int monsterRoomIndex, int key)
{
	_Astar = new Astar;
	sprintf_s(str, "%s", imgName);
	sprintf_s(str2, "%sBullet", imgName);
	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	_Direction = RIGHT_STAND;
	_attackRange = 320;
	_monsterHP = 250;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_timecnt = 32;
	_speed = 1.0F;
	_monsterIndex = monsterRoomIndex;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),	_image->getFrameHeight());
	_keyIndex = int(point.x + point.y + monsterRoomIndex+ key);

	sprintf_s(_motionName1, "RogueMonsterSummon%d", _keyIndex);
	sprintf_s(_motionName2, "RogueRightAttack%d", _keyIndex);
	sprintf_s(_motionName3, "RogueLeftAttack%d", _keyIndex);
	sprintf_s(_motionName4, "RogueRightHit%d", _keyIndex);
	sprintf_s(_motionName5, "RogueLeftHit%d", _keyIndex);
	sprintf_s(_motionName6, "RogueRightDie%d", _keyIndex);
	sprintf_s(_motionName7, "RogueLeftDie%d", _keyIndex);

	int Summon[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName1, "SummonMonster", Summon, 29, 25, false, summonOn, this);


	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightStand", str, rightStand, 1, 1, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftStand", str, leftStand, 1, 1, false);

	int rightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightMove", str, rightMove, 5, 3, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftMove", str, leftMove, 5, 3, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, str, rightAttack, 2, 8, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, str, leftAttack, 2, 8, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, str, rightHit, 2, 3, false, rightStop, this);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, str, leftHit, 2, 3, false, leftStop, this);


	int rightDie[] = { 20,21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName6, str, rightDie, 7, 6, false, MonsterDie,this);
	int leftDie[] = { 30,31,32,33,34,35,36};
	KEYANIMANAGER->addArrayFrameAnimation(_motionName7, str, leftDie, 7, 6, false,MonsterDie,this);

	_Motion = KEYANIMANAGER->findAnimation(_motionName1);

	return S_OK;
}

void Rogue::release()
{
}

void Rogue::update()
{
	_distance = getDistance(_position.x, _position.y, _playerPosition.x, _playerPosition.y);
	_angle = getAngle(_position.x, _position.y, _playerPosition.x, _playerPosition.y);

	if (_playerIndex == _monsterIndex && _form == CARD)
	{
		SOUNDMANAGER->play("EnemySummon" );
		_form = SUMMOM;
		getMotion()->start();
	}

	if (_form == BATTLE)
	{
		RogueMove();
		Die();
		Test();
	}
}

void Rogue::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _Motion);
}

void Rogue::RogueMove()
{
	_position.x = _bottomPosition.x;
	_position.y = _bottomPosition.y - _image->getFrameHeight() / 2;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(), _image->getFrameHeight());


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

	if (_attackRange  > _distance)
	{
		if (!_attackReady) return;
		if (_position.x < _playerPosition.x)
		{
			if (_Direction == RIGHT_MOVE || _Direction == RIGHT_STAND)
			{
				_Direction = RIGHT_ATTACK;
				_Motion = KEYANIMANAGER->findAnimation(_motionName2);
				_Motion->start();
				_PM->fire(str2, _position);
				SOUNDMANAGER->play("RogueAttack" );
				_attackReady = false;
			}
		}
		else if (_position.x > _playerPosition.x)
		{

			if (_Direction == LEFT_MOVE || _Direction == LEFT_STAND)
			{
				_Direction = LEFT_ATTACK;
				_Motion = KEYANIMANAGER->findAnimation(_motionName3);
				_Motion->start();
				_PM->fire(str2, _position);
				SOUNDMANAGER->play("RogueAttack" );
				_attackReady = false;
			}
		}
	}
	else  //에이스타 움직임
	{

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



		if (_position.x < _playerPosition.x)
		{
			if (_Direction == RIGHT_MOVE) return;
			_Direction = RIGHT_MOVE;
			_Motion = KEYANIMANAGER->findAnimation("RogueRightMove");
			_Motion->start();

		}
		else if (_position.x > _playerPosition.x)
		{
			if (_Direction == LEFT_MOVE) return;
			_Direction = LEFT_MOVE;
			_Motion = KEYANIMANAGER->findAnimation("RogueLeftMove");
			_Motion->start();
		}
	}



}

void Rogue::rightStop(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;
	if (_MonsterRogue->getForm() == DIE) return;
	_MonsterRogue->setMonsterDirection(RIGHT_STAND);
	_MonsterRogue->setMotion(KEYANIMANAGER->findAnimation("RogueRightStand"));
	_MonsterRogue->getMotion()->start();
}

void Rogue::leftStop(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;
	if (_MonsterRogue->getForm() == DIE) return;
	_MonsterRogue->setMonsterDirection(LEFT_STAND);
	_MonsterRogue->setMotion(KEYANIMANAGER->findAnimation("RogueLeftStand"));
	_MonsterRogue->getMotion()->start();
}


void Rogue::summonOn(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;

	_MonsterRogue->setImage(IMAGEMANAGER->findImage(_MonsterRogue->str));
	_MonsterRogue->setForm(BATTLE);
	_MonsterRogue->setMonsterDirection(LEFT_STAND);
	_MonsterRogue->setMotion(KEYANIMANAGER->findAnimation("RogueLeftStand"));
	_MonsterRogue->getMotion()->start();

}

void Rogue::MonsterDie(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;
	_MonsterRogue->_isDie = true;
}

void Rogue::Test()
{
	if (KEYMANAGER->isOnceKeyDown('O')) _monsterHP = 0;
	
}

void Rogue::HitMotion()
{
		if (_form == DIE) return;
		if (_Direction == RIGHT_HIT || _Direction == LEFT_HIT) return;
		if (_Direction == RIGHT_MOVE || _Direction == RIGHT_STAND || _Direction == RIGHT_ATTACK)
		{
			SOUNDMANAGER->play("EnemyHurt" );
			_Direction = RIGHT_HIT;
			_Motion = KEYANIMANAGER->findAnimation(_motionName4);
			_Motion->start();
		}
		else if (_Direction == LEFT_MOVE || _Direction == LEFT_STAND || _Direction == LEFT_ATTACK)
		{
			SOUNDMANAGER->play("EnemyHurt" );
			_Direction = LEFT_HIT;
			_Motion = KEYANIMANAGER->findAnimation(_motionName5);
			_Motion->start();
		}
}

void Rogue::Die()
{
	if (_monsterHP <= 0)
	{
		if (_form == DIE) return;
		if (_Direction == RIGHT_MOVE || _Direction == RIGHT_HIT || _Direction == RIGHT_STAND)
		{
			SOUNDMANAGER->play("EnemyDie" );
			_Direction = RIGHT_DIE;
			_form = DIE;
			_Motion = KEYANIMANAGER->findAnimation(_motionName6);
			_Motion->start();
		}
		else if (_Direction == LEFT_MOVE || _Direction == LEFT_HIT || _Direction == LEFT_STAND)
		{
			SOUNDMANAGER->play("EnemyDie" );
			_Direction = LEFT_DIE;
			_form = DIE;
			_Motion = KEYANIMANAGER->findAnimation(_motionName7);
			_Motion->start();
		}
	}
}
