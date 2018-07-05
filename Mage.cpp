#include "stdafx.h"
#include "Mage.h"


Mage::Mage()
{
}


Mage::~Mage()
{
}

HRESULT Mage::init(const char* imgName, POINTFLOAT point,int index)
{
	sprintf_s(str, "%s", imgName);

	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	//_image = IMAGEMANAGER->findImage(str);

	_MageDirection = MAGE_RIGHT_STAND;
	_attackRange = 300;
	_monsterHP = 200;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_speed = 4.0F;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),
		_image->getFrameHeight());


	sprintf_s(_motionName1, "MageMonsterSummon%d", index);
	sprintf_s(_motionName2, "MageRightAttack%d", index);
	sprintf_s(_motionName3, "MageLeftAttack%d", index);
	sprintf_s(_motionName4, "MageRightHit%d", index);
	sprintf_s(_motionName5, "MageLeftHit%d", index);

	int Summon[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName1, "SummonMonster", Summon, 29, 10, false, summonOn, this);

	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightStand", str, rightStand, 1, 6, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftStand", str, leftStand, 1, 6, false);

	int rightMove[] = { 1,2,3,4,5};
	KEYANIMANAGER->addArrayFrameAnimation("MageRightMove", str, rightMove, 5, 1, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftMove", str, leftMove, 5, 1, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, str, rightAttack, 2,1, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, str, leftAttack, 2, 1, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, str, rightHit, 2, 2, false, rightStop, this);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, str, leftHit, 2, 2, false, leftStop, this);


	int rightDie[] = { 20,21,22,23,24,25,26,27 };
	KEYANIMANAGER->addArrayFrameAnimation("MageRightDie", str, rightDie, 8, 6, false);
	int leftDie[] = { 30,31,32,33,34,35,36,37 };
	KEYANIMANAGER->addArrayFrameAnimation("MageLeftDie", str, leftDie, 8, 6, false);




	_MageMotion = KEYANIMANAGER->findAnimation(_motionName1);

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

void Mage::summonOn(void * obj)
{


	Mage* _MonsterMage = (Mage*)obj;
	_MonsterMage->setImage(IMAGEMANAGER->findImage(_MonsterMage->str));
	_MonsterMage->setForm(BATTLE);
	_MonsterMage->setMageDirection(MAGE_LEFT_STAND);
	_MonsterMage->setMageMotion(KEYANIMANAGER->findAnimation("MageLeftStand"));
	_MonsterMage->getMageMotion()->start();


}

void Mage::Test()
{


	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_MageDirection == MAGE_RIGHT_MOVE || _MageDirection == MAGE_RIGHT_HIT || _MageDirection == MAGE_RIGHT_STAND || _MageDirection == MAGE_RIGHT_ATTACK)
		{
			_MageDirection = MAGE_RIGHT_HIT;
			_MageMotion = KEYANIMANAGER->findAnimation(_motionName4);
			_MageMotion->start();
		}
		else if (_MageDirection == MAGE_LEFT_MOVE || _MageDirection == MAGE_LEFT_HIT || _MageDirection == MAGE_LEFT_STAND || _MageDirection == MAGE_LEFT_ATTACK)
		{
			_MageDirection = MAGE_LEFT_HIT;
			_MageMotion = KEYANIMANAGER->findAnimation(_motionName5);
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
