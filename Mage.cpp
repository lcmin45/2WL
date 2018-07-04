#include "stdafx.h"
#include "Mage.h"


Mage::Mage()
{
}


Mage::~Mage()
{
}

HRESULT Mage::init(const char* imgName, POINTFLOAT point, float speed)
{

	sprintf_s(str, "%s", imgName);
	sprintf_s(str2, "image/monster/%s.bmp", imgName);


	_image = IMAGEMANAGER->addFrameImage(str, str2, 0, 0,280*2, 200*2, 10, 4, true, RGB(255, 0, 255));

	_MageDirection = MAGE_RIGHT_STAND;
	_attackRange = 100;
	_bottomX = point.x;
	_bottomY = point.y;
	_x = _bottomX;
	_y = _bottomY - _image->getFrameHeight() / 2;
	_speed = speed;
	_Zrc = RectMakeCenter(_bottomX, _bottomY, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());


	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightStand", str, rightStand, 1, 6, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftStand", str, leftStand, 1, 6, false);

	int rightMove[] = { 1,2,3,4,5};
	KEYANIMANAGER->addArrayFrameAnimation("MageRightMove", str, rightMove, 5, 1, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftMove", str, leftMove, 5, 1, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightAttack", str, rightAttack, 2,1, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftAttack", str, leftAttack, 2, 1, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightHit", str, rightHit, 2, 2, false);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftHit", str, leftHit, 2, 2, false);


	int rightDie[] = { 20,21,22,23,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightDie", str, rightDie, 8, 1, false);
	int leftDie[] = { 30,31,32,33,34,35,36,37 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftDie", str, leftDie, 8, 1, false);




	_MageMotion = KEYANIMANAGER->findAnimation("MageRightStand");

	return S_OK;
}

void Mage::release()
{
}

void Mage::update()
{

	Test();
	KEYANIMANAGER->update();
}

void Mage::render()
{

	_image->aniRender(getMemDC(), _rc.left, _rc.top, _MageMotion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void Mage::MageMove()
{
}

void Mage::rightStop(void * obj)
{
	Mage* _MonsterMage = (Mage*)obj;

	_MonsterMage->setMageDirection(MAGE_RIGHT_STAND);
	_MonsterMage->setMageMotion(KEYANIMANAGER->findAnimation("MageRightStand"));
	_MonsterMage->getMageMotion()->start();
}

void Mage::leftStop(void * obj)
{
	Mage* _MonsterMage = (Mage*)obj;

	_MonsterMage->setMageDirection(MAGE_LEFT_STAND);
	_MonsterMage->setMageMotion(KEYANIMANAGER->findAnimation("MageLeftStand"));
	_MonsterMage->getMageMotion()->start();
}

void Mage::Test()
{

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_MageDirection = MAGE_RIGHT_MOVE;
		_MageMotion = KEYANIMANAGER->findAnimation("MageRightMove");
		_MageMotion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_MageDirection = MAGE_LEFT_MOVE;
		_MageMotion = KEYANIMANAGER->findAnimation("MageLeftMove");
		_MageMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_MageDirection == MAGE_RIGHT_MOVE || _MageDirection == MAGE_RIGHT_STAND)
		{
			_MageDirection = MAGE_RIGHT_ATTACK;
			_MageMotion = KEYANIMANAGER->findAnimation("MageRightAttack");
			_MageMotion->start();
		}
		else if (_MageDirection == MAGE_LEFT_MOVE || _MageDirection == MAGE_LEFT_STAND)
		{
			_MageDirection = MAGE_LEFT_ATTACK;
			_MageMotion = KEYANIMANAGER->findAnimation("MageLeftAttack");
			_MageMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_MageDirection == MAGE_RIGHT_MOVE || _MageDirection == MAGE_RIGHT_HIT || _MageDirection == MAGE_RIGHT_STAND)
		{
			_MageDirection = MAGE_RIGHT_HIT;
			_MageMotion = KEYANIMANAGER->findAnimation("MageRightHit");
			_MageMotion->start();
		}
		else if (_MageDirection == MAGE_LEFT_MOVE || _MageDirection == MAGE_LEFT_HIT || _MageDirection == MAGE_LEFT_STAND)
		{
			_MageDirection = MAGE_LEFT_HIT;
			_MageMotion = KEYANIMANAGER->findAnimation("MageLeftHit");
			_MageMotion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_MageDirection == MAGE_RIGHT_MOVE || _MageDirection == MAGE_RIGHT_HIT)
		{
			_MageDirection = MAGE_RIGHT_DIE;
			_MageMotion = KEYANIMANAGER->findAnimation("MageRightDie");
			_MageMotion->start();
		}
		else if (_MageDirection == MAGE_LEFT_MOVE || _MageDirection == MAGE_LEFT_HIT)
		{
			_MageDirection = MAGE_LEFT_DIE;
			_MageMotion = KEYANIMANAGER->findAnimation("MageLeftDie");
			_MageMotion->start();
		}
	}
}
