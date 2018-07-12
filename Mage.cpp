#include "stdafx.h"
#include "Mage.h"


Mage::Mage()
{
}


Mage::~Mage()
{
}

HRESULT Mage::init(const char* imgName, POINTFLOAT point, int monsterRoomIndex, int a)
{
	_Astar = new Astar;
	sprintf_s(str, "%s", imgName);
	sprintf_s(str2, "%sBullet", imgName);
	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	_Direction = RIGHT_STAND;
	_attackRange = 480;
	_monsterHP = 200;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_timecnt = 32;
	_speed = 1.0F;
	_monsterIndex = monsterRoomIndex;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),	_image->getFrameHeight());
	_keyIndex = int(point.x + point.y + monsterRoomIndex +a);

	sprintf_s(_motionName1, "MageMonsterSummon%d", _keyIndex);
	sprintf_s(_motionName2, "MageRightAttack%d", _keyIndex);
	sprintf_s(_motionName3, "MageLeftAttack%d", _keyIndex);
	sprintf_s(_motionName4, "MageRightHit%d", _keyIndex);
	sprintf_s(_motionName5, "MageLeftHit%d", _keyIndex);
	sprintf_s(_motionName6, "MageRightDie%d", _keyIndex);
	sprintf_s(_motionName7, "MageLeftDie%d", _keyIndex);

	int Summon[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName1, "SummonMonster", Summon, 29, 10, false, summonOn, this);

	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightStand", str, rightStand, 1, 1, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftStand", str, leftStand, 1, 1, false);

	int rightMove[] = { 1,2,3,4,5};
	KEYANIMANAGER->addArrayFrameAnimation("MageRightMove", str, rightMove, 5, 3, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftMove", str, leftMove, 5, 3, true);

	int rightAttack[] = { 6,6,6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, str, rightAttack, 4, 4, false, rightStop, this);
	int leftAttack[] = { 16,16,16,17 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, str, leftAttack, 4, 4, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, str, rightHit, 2, 3, false, rightStop, this);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, str, leftHit, 2, 3, false, leftStop, this);


	int rightDie[] = { 20,21,22,23,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName6, str, rightDie, 8, 6, false,MonsterDie,this);
	int leftDie[] = { 30,31,32,33,34,35,36,37 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName7, str, leftDie, 8, 6, false, MonsterDie, this);



	_Motion = KEYANIMANAGER->findAnimation(_motionName1);

	return S_OK;
}

void Mage::release()
{
}

void Mage::update()
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
		MageMove();
		Die();
		Test();
	}
}


void Mage::render()
{

	_image->aniRender(getMemDC(), _rc.left, _rc.top, _Motion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void Mage::MageMove()
{

	_position.x = _bottomPosition.x;
	_position.y = _bottomPosition.y - _image->getFrameHeight() / 2;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(), _image->getFrameHeight());

	if (_Direction == RIGHT_HIT || _Direction == LEFT_HIT ||
		_Direction == RIGHT_DIE || _Direction == LEFT_DIE ||
		_Direction == RIGHT_ATTACK || _Direction == LEFT_ATTACK	) return;

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
				SOUNDMANAGER->play("MageAttack" );
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
				SOUNDMANAGER->play("MageAttack" );
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
			_Motion = KEYANIMANAGER->findAnimation("MageRightMove");
			_Motion->start();

		}
		else if (_position.x > _playerPosition.x)
		{
			if (_Direction == LEFT_MOVE) return;
			_Direction = LEFT_MOVE;
			_Motion = KEYANIMANAGER->findAnimation("MageLeftMove");
			_Motion->start();
		}
	}


}

void Mage::rightStop(void * obj)
{
	Mage* _MonsterMage = (Mage*)obj;
	if (_MonsterMage->getForm() == DIE) return;
	_MonsterMage->setMonsterDirection(RIGHT_STAND);
	_MonsterMage->setMotion(KEYANIMANAGER->findAnimation("MageRightStand"));
	_MonsterMage->getMotion()->start();
}

void Mage::leftStop(void * obj)
{
	Mage* _MonsterMage = (Mage*)obj;
	if (_MonsterMage->getForm() == DIE) return;
	_MonsterMage->setMonsterDirection(LEFT_STAND);
	_MonsterMage->setMotion(KEYANIMANAGER->findAnimation("MageLeftStand"));
	_MonsterMage->getMotion()->start();
}

void Mage::summonOn(void * obj)
{

	Mage* _MonsterMage = (Mage*)obj;

	_MonsterMage->setImage(IMAGEMANAGER->findImage(_MonsterMage->str));
	_MonsterMage->setForm(BATTLE);
	_MonsterMage->setMonsterDirection(LEFT_STAND);
	_MonsterMage->setMotion(KEYANIMANAGER->findAnimation("MageLeftStand"));
	_MonsterMage->getMotion()->start();


}

void Mage::MonsterDie(void * obj)
{
	Mage* _MonsterMage = (Mage*)obj;
	_MonsterMage->_isDie = true;
}

void Mage::Test()
{

	if (KEYMANAGER->isOnceKeyDown('O')) _monsterHP = 0;


	
}

void Mage::HitMotion()
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
	else if (_Direction == LEFT_MOVE || _Direction == LEFT_HIT || _Direction == LEFT_STAND || _Direction == LEFT_ATTACK)
	{
		SOUNDMANAGER->play("EnemyHurt" );
		_Direction = LEFT_HIT;
		_Motion = KEYANIMANAGER->findAnimation(_motionName5);
		_Motion->start();
	}
}

void Mage::Die()
{

	if (_monsterHP <= 0)
	{
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
