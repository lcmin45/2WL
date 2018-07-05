#include "stdafx.h"
#include "Knight.h"


Knight::Knight()
{
}


Knight::~Knight()
{
}

HRESULT Knight::init(const char * imgName, POINTFLOAT point,int index)
{
	sprintf_s(str, "%s", imgName);

	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;

	//_image = IMAGEMANAGER->findImage(str);

	_KnightDirection = KNIGHT_RIGHT_STAND;
	_attackRange = 50;
	_monsterHP = 300;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_speed = 4.0F;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),
		_image->getFrameHeight());
	
	sprintf_s(_motionName1, "KnightMonsterSummon%d", index);
	sprintf_s(_motionName2, "KnightRightAttack%d", index);
	sprintf_s(_motionName3, "KnightLeftAttack%d", index);
	sprintf_s(_motionName4, "KnightRightHit%d", index);
	sprintf_s(_motionName5, "KnightLeftHit%d", index);

	int Summon[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName1, "SummonMonster", Summon, 29, 10, false, summonOn, this);


	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightStand", str, rightStand, 1, 6, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftStand", str, leftStand, 1, 6, false);

	int rightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightMove", str, rightMove, 5, 1, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftMove", str, leftMove, 5, 1, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, str, rightAttack, 2, 1, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, str, leftAttack, 2, 1, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, str, rightHit, 2, 2, false, rightStop, this);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, str, leftHit, 2, 2, false, leftStop, this);


	int rightDie[] = { 20,21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightDie", str, rightDie, 7, 6, false);
	int leftDie[] = { 30,31,32,33,34,35,36 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftDie", str, leftDie, 7, 6, false);




	_KnightMotion = KEYANIMANAGER->findAnimation(_motionName1);



	//=====================================테스트용=======================
	PX = WINSIZEX / 2 + 200;
	PY = WINSIZEY / 2 + 200;
	PRC = RectMakeCenter(PX, PY, 30, 30);
	//=====================================테스트용=======================

	return S_OK;
}

void Knight::release()
{
}

void Knight::update()
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
		getKnightMotion()->start();
	}

	if (_form == BATTLE)
	{
		KnightMove();
		Test();
	}
}

void Knight::render()
{

	_image->aniRender(getMemDC(), _rc.left, _rc.top, _KnightMotion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void Knight::KnightMove()
{

	if (_KnightDirection == KNIGHT_RIGHT_HIT || _KnightDirection == KNIGHT_LEFT_HIT ||
		_KnightDirection == KNIGHT_RIGHT_DIE || _KnightDirection == KNIGHT_LEFT_DIE) return;



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
			if (_KnightDirection == KNIGHT_RIGHT_MOVE || _KnightDirection == KNIGHT_RIGHT_STAND)
			{
				_KnightDirection = KNIGHT_RIGHT_ATTACK;
				_KnightMotion = KEYANIMANAGER->findAnimation(_motionName2);
				_KnightMotion->start();
			}
		}
		else if (_position.x > PX)
		{

			if (_KnightDirection == KNIGHT_LEFT_MOVE || _KnightDirection == KNIGHT_LEFT_STAND)
			{
				_KnightDirection = KNIGHT_LEFT_ATTACK;
				_KnightMotion = KEYANIMANAGER->findAnimation(_motionName3);
				_KnightMotion->start();
			}
		}
	}
	//=====================================테스트용=======================
	else //맵 완성 되면 에이스타로 움직이기!
	{

		_position.x += cos(_angle) * _speed;
		_position.y += -sin(_angle) * _speed;


		if (_position.x < PX)
		{
			if (_KnightDirection == KNIGHT_RIGHT_MOVE) return;
			_KnightDirection = KNIGHT_RIGHT_MOVE;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightRightMove");
			_KnightMotion->start();

		}
		else if (_position.x > PX)
		{
			if (_KnightDirection == KNIGHT_LEFT_MOVE) return;
			_KnightDirection = KNIGHT_LEFT_MOVE;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightLeftMove");
			_KnightMotion->start();
		}
	}
	//=====================================테스트용=======================
}


void Knight::rightStop(void * obj)
{
	Knight* _MonsterKnight = (Knight*)obj;

	_MonsterKnight->setKnightDirection(KNIGHT_RIGHT_STAND);
	_MonsterKnight->setKnightMotion(KEYANIMANAGER->findAnimation("KnightRightStand"));
	_MonsterKnight->getKnightMotion()->start();
}

void Knight::leftStop(void * obj)
{
	Knight* _MonsterKnight = (Knight*)obj;

	_MonsterKnight->setKnightDirection(KNIGHT_LEFT_STAND);
	_MonsterKnight->setKnightMotion(KEYANIMANAGER->findAnimation("KnightLeftStand"));
	_MonsterKnight->getKnightMotion()->start();
}

void Knight::summonOn(void * obj)
{

	Knight* _MonsterKnight = (Knight*)obj;

	_MonsterKnight->setImage(IMAGEMANAGER->findImage(_MonsterKnight->str));
	_MonsterKnight->setForm(BATTLE);
	_MonsterKnight->setKnightDirection(KNIGHT_LEFT_STAND);
	_MonsterKnight->setKnightMotion(KEYANIMANAGER->findAnimation("KnightLeftStand"));
	_MonsterKnight->getKnightMotion()->start();

}	

void Knight::Test()
{


	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_KnightDirection == KNIGHT_RIGHT_HIT || _KnightDirection == KNIGHT_LEFT_HIT) return;
		if (_KnightDirection == KNIGHT_RIGHT_MOVE || _KnightDirection == KNIGHT_RIGHT_HIT || _KnightDirection == KNIGHT_RIGHT_STAND || _KnightDirection == KNIGHT_RIGHT_ATTACK)
		{
			_KnightDirection = KNIGHT_RIGHT_HIT;
			_KnightMotion = KEYANIMANAGER->findAnimation(_motionName4);
			_KnightMotion->start();
		}
		else if (_KnightDirection == KNIGHT_LEFT_MOVE || _KnightDirection == KNIGHT_LEFT_HIT || _KnightDirection == KNIGHT_LEFT_STAND || _KnightDirection == KNIGHT_LEFT_ATTACK)
		{
			_KnightDirection = KNIGHT_LEFT_HIT;
			_KnightMotion = KEYANIMANAGER->findAnimation(_motionName5);
			_KnightMotion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_KnightDirection == KNIGHT_RIGHT_DIE || _KnightDirection == KNIGHT_LEFT_DIE) return;
		if (_KnightDirection == KNIGHT_RIGHT_MOVE || _KnightDirection == KNIGHT_RIGHT_HIT)
		{
			_KnightDirection = KNIGHT_RIGHT_DIE;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightRightDie");
			_KnightMotion->start();
		}
		else if (_KnightDirection == KNIGHT_LEFT_MOVE || _KnightDirection == KNIGHT_LEFT_HIT)
		{
			_KnightDirection = KNIGHT_LEFT_DIE;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightLeftDie");
			_KnightMotion->start();
		}
	}
}
