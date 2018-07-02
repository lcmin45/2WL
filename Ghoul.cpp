#include "stdafx.h"
#include "Ghoul.h"
#include "player.h"


Ghoul::Ghoul()
{
}


Ghoul::~Ghoul()
{
}

HRESULT Ghoul::init(POINTFLOAT point,float speed)
{

	_image = IMAGEMANAGER->addFrameImage("Ghoul", "image/monster/Ghoul.bmp", 0, 0, 560, 304, 10, 4, true, RGB(255, 0, 255));

	_ghoulDirection = GHOUL_RIGHT_MOVE; 
	_attackRange = 20;
	_x = point.x;
	_y = point.y;
	_speed = speed;
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());



	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightStand", "Ghoul", rightStand, 1, 1, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftStand", "Ghoul", leftStand, 1, 1, false);

	int rightMove[] = { 3,4,5,6,7,8 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightMove", "Ghoul", rightMove, 6, 1, true);
	int leftMove[] = { 13,14,15,16,17,18 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftMove", "Ghoul", leftMove, 6, 1, true);


	int rightAttack[] = { 1 ,2, 2 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightAttack", "Ghoul", rightAttack, 3, 1, false, rightStop, this);
	int leftAttack[] = { 11 ,12, 12 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftAttack", "Ghoul", leftAttack, 3, 1, false, leftStop, this);


	int rightHit[] = { 20 ,9 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightHit", "Ghoul", rightHit, 2, 3, false);
	int leftHit[] = { 30 ,19 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftHit", "Ghoul", leftHit, 2, 3, false);



	int rightDie[] = { 21,22,23,24,25,26,27,28,29 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulRightDie", "Ghoul", rightDie, 9, 1, false);
	int leftDie[] = { 31,32,33,34,35,36,37,38,39 };
	KEYANIMANAGER->addArrayFrameAnimation("GhoulLeftDie", "Ghoul", leftDie, 9, 1, false);


	_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightMove");


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

	//ghoulMove();
	Test();
	KEYANIMANAGER->update();
}

void Ghoul::render()
{

	//Rectangle(CAMERAMANAGER->getCameraDC(), PRC.left, PRC.top, PRC.right, PRC.bottom);
	_image->aniRender(CAMERAMANAGER->getCameraDC(), _rc.left, _rc.top, _ghoulMotion);
}

void Ghoul::ghoulMove()
{
	_angle = getAngle(_x, _y, PX, PY);

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	if (_attackRange * _speed > getDistance(_x, _y, PX, PY))
	{
		if (_x < PX)
		{
			if (_ghoulDirection == GHOUL_RIGHT_MOVE)
			{
				_ghoulDirection = GHOUL_RIGHT_ATTACK;
				_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightAttack");
				_ghoulMotion->start();
			}
		}
		else if (_x > PX)
		{

			if (_ghoulDirection == GHOUL_LEFT_MOVE)
			{
				_ghoulDirection = GHOUL_LEFT_ATTACK;
				_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulLeftAttack");
				_ghoulMotion->start();
			}
		}
	}
	//=====================================테스트용=======================
	else //맵 완성 되면 에이스타로 움직이기!
	{
		_x += cos(_angle) * _speed;
		_y += -sin(_angle) * _speed;


		if (_x < PX)
		{
			if (_ghoulDirection == GHOUL_RIGHT_MOVE) return;
			_ghoulDirection = GHOUL_RIGHT_MOVE;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightMove");
			_ghoulMotion->start();

		}
		else if (_x > PX)
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


//=====================================테스트용=======================
void Ghoul::Test()
{
	/*if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		PX += 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		PX -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		PY -= 2;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		PY += 2;
	}
	PRC = RectMakeCenter(PX, PY, 30, 30);*/


	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_ghoulDirection = GHOUL_RIGHT_MOVE;
		_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightMove");
		_ghoulMotion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_ghoulDirection = GHOUL_LEFT_MOVE;
		_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulLeftMove");
		_ghoulMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_ghoulDirection == GHOUL_RIGHT_MOVE)
		{
			_ghoulDirection = GHOUL_RIGHT_ATTACK;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightAttack");
			_ghoulMotion->start();
		}
		else if (_ghoulDirection == GHOUL_LEFT_MOVE)
		{
			_ghoulDirection = GHOUL_LEFT_ATTACK;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulLeftAttack");
			_ghoulMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_ghoulDirection == GHOUL_RIGHT_MOVE || _ghoulDirection == GHOUL_RIGHT_HIT)
		{
			_ghoulDirection = GHOUL_RIGHT_HIT;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulRightHit");
			_ghoulMotion->start();
		}
		else if (_ghoulDirection == GHOUL_LEFT_MOVE || _ghoulDirection == GHOUL_LEFT_HIT)
		{
			_ghoulDirection = GHOUL_LEFT_HIT;
			_ghoulMotion = KEYANIMANAGER->findAnimation("GhoulLeftHit");
			_ghoulMotion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
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
