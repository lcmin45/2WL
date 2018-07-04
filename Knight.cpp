#include "stdafx.h"
#include "Knight.h"


Knight::Knight()
{
}


Knight::~Knight()
{
}

HRESULT Knight::init(const char * imgName, POINTFLOAT point, float speed)
{
	sprintf_s(str, "%s", imgName);
	sprintf_s(str2, "image/monster/%s.bmp", imgName);


	_image = IMAGEMANAGER->addFrameImage(str, str2, 0, 0, 420 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));

	_KnightDirection = KNIGHT_RIGHT_STAND;
	_attackRange = 30; _bottomX = point.x;
	_bottomY = point.y;
	_x = _bottomX;
	_y = _bottomY - _image->getFrameHeight() / 2;
	_speed = speed;
	_Zrc = RectMakeCenter(_bottomX, _bottomY, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());
	


	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightStand", str, rightStand, 1, 6, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftStand", str, leftStand, 1, 6, false);

	int rightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightMove", str, rightMove, 5, 1, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftMove", str, leftMove, 5, 1, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightAttack", str, rightAttack, 2, 1, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftAttack", str, leftAttack, 2, 1, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightHit", str, rightHit, 2, 2, false);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftHit", str, leftHit, 2, 2, false);


	int rightDie[] = { 20,21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightRightDie", str, rightDie, 7, 1, false);
	int leftDie[] = { 30,31,32,33,34,35,36 };
	KEYANIMANAGER->addArrayFrameAnimation("KnightLeftDie", str, leftDie, 7, 1, false);




	_KnightMotion = KEYANIMANAGER->findAnimation("KnightRightStand");

	return S_OK;
}

void Knight::release()
{
}

void Knight::update()
{

	Test();
	KEYANIMANAGER->update();
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

void Knight::Test()
{

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_KnightDirection = KNIGHT_RIGHT_MOVE;
		_KnightMotion = KEYANIMANAGER->findAnimation("KnightRightMove");
		_KnightMotion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_KnightDirection = KNIGHT_LEFT_MOVE;
		_KnightMotion = KEYANIMANAGER->findAnimation("KnightLeftMove");
		_KnightMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_KnightDirection == KNIGHT_RIGHT_MOVE || _KnightDirection == KNIGHT_RIGHT_STAND)
		{
			_KnightDirection = KNIGHT_RIGHT_ATTACK;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightRightAttack");
			_KnightMotion->start();
		}
		else if (_KnightDirection == KNIGHT_LEFT_MOVE || _KnightDirection == KNIGHT_LEFT_STAND)
		{
			_KnightDirection = KNIGHT_LEFT_ATTACK;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightLeftAttack");
			_KnightMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_KnightDirection == KNIGHT_RIGHT_MOVE || _KnightDirection == KNIGHT_RIGHT_HIT || _KnightDirection == KNIGHT_RIGHT_STAND)
		{
			_KnightDirection = KNIGHT_RIGHT_HIT;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightRightHit");
			_KnightMotion->start();
		}
		else if (_KnightDirection == KNIGHT_LEFT_MOVE || _KnightDirection == KNIGHT_LEFT_HIT || _KnightDirection == KNIGHT_LEFT_STAND)
		{
			_KnightDirection = KNIGHT_LEFT_HIT;
			_KnightMotion = KEYANIMANAGER->findAnimation("KnightLeftHit");
			_KnightMotion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
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
