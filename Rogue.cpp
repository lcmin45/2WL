#include "stdafx.h"
#include "Rogue.h"


Rogue::Rogue()
{
}


Rogue::~Rogue()
{
}

HRESULT Rogue::init(const char * imgName, POINTFLOAT point,int index)
{
	sprintf_s(str, "%s", imgName);
	_image = IMAGEMANAGER->findImage("SummonMonster");
	_form = CARD;
	//_image = IMAGEMANAGER->findImage(str);

	_RogueDirection = ROGUE_RIGHT_STAND;
	_attackRange = 200;
	_monsterHP = 250;
	_bottomPosition = point;
	_position.x = point.x;
	_position.y = point.y - _image->getFrameHeight() / 2;
	_speed = 4.0F;
	_Zrc = RectMakeCenter(_bottomPosition.x, _bottomPosition.y, _image->getFrameWidth(), 10);
	_rc = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth(),
		_image->getFrameHeight());


	sprintf_s(_motionName1, "RogueMonsterSummon%d", index);
	sprintf_s(_motionName2, "RogueRightAttack%d", index);
	sprintf_s(_motionName3, "RogueLeftAttack%d", index);
	sprintf_s(_motionName4, "RogueRightHit%d", index);
	sprintf_s(_motionName5, "RogueLeftHit%d", index);

	int Summon[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName1, "SummonMonster", Summon, 29, 10, false, summonOn, this);


	int rightStand[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightStand", str, rightStand, 1, 6, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftStand", str, leftStand, 1, 6, false);

	int rightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightMove", str, rightMove, 5, 1, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftMove", str, leftMove, 5, 1, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName2, str, rightAttack, 2, 1, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName3, str, leftAttack, 2, 1, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName4, str, rightHit, 2, 2, false, rightStop, this);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation(_motionName5, str, leftHit, 2, 2, false, leftStop, this);


	int rightDie[] = { 20,21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightDie", str, rightDie, 7, 6, false);
	int leftDie[] = { 30,31,32,33,34,35,36};
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftDie", str, leftDie, 7, 6, false);




	_RogueMotion = KEYANIMANAGER->findAnimation(_motionName1);

	return S_OK;
}

void Rogue::release()
{
}

void Rogue::update()
{

	Test();
	KEYANIMANAGER->update();
}

void Rogue::render()
{
	_image->aniRender(getMemDC(), _rc.left, _rc.top, _RogueMotion);
	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(getMemDC(), _Zrc.left, _Zrc.top, _Zrc.right, _Zrc.bottom);
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
}

void Rogue::RogueMove()
{
}

void Rogue::rightStop(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;

	_MonsterRogue->setRogueDirection(ROGUE_RIGHT_STAND);
	_MonsterRogue->setRogueMotion(KEYANIMANAGER->findAnimation("RogueRightStand"));
	_MonsterRogue->getRogueMotion()->start();
}

void Rogue::leftStop(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;

	_MonsterRogue->setRogueDirection(ROGUE_LEFT_STAND);
	_MonsterRogue->setRogueMotion(KEYANIMANAGER->findAnimation("RogueLeftStand"));
	_MonsterRogue->getRogueMotion()->start();
}


void Rogue::summonOn(void * obj)
{
	Rogue* _MonsterRogue = (Rogue*)obj;

	_MonsterRogue->setImage(IMAGEMANAGER->findImage(_MonsterRogue->str));
	_MonsterRogue->setForm(BATTLE);
	_MonsterRogue->setRogueDirection(ROGUE_LEFT_STAND);
	_MonsterRogue->setRogueMotion(KEYANIMANAGER->findAnimation("RogueLeftStand"));
	_MonsterRogue->getRogueMotion()->start();

}

void Rogue::Test()
{

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_RogueDirection == ROGUE_RIGHT_MOVE || _RogueDirection == ROGUE_RIGHT_HIT || _RogueDirection == ROGUE_RIGHT_STAND || _RogueDirection == ROGUE_RIGHT_ATTACK)
		{
			_RogueDirection = ROGUE_RIGHT_HIT;
			_RogueMotion = KEYANIMANAGER->findAnimation(_motionName4);
			_RogueMotion->start();
		}
		else if (_RogueDirection == ROGUE_LEFT_MOVE || _RogueDirection == ROGUE_LEFT_HIT || _RogueDirection == ROGUE_LEFT_STAND || _RogueDirection == ROGUE_LEFT_ATTACK)
		{
			_RogueDirection = ROGUE_LEFT_HIT;
			_RogueMotion = KEYANIMANAGER->findAnimation(_motionName5);
			_RogueMotion->start();
		}
	}


	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_RogueDirection == ROGUE_RIGHT_MOVE || _RogueDirection == ROGUE_RIGHT_HIT)
		{
			_RogueDirection = ROGUE_RIGHT_DIE;
			_RogueMotion = KEYANIMANAGER->findAnimation("RogueRightDie");
			_RogueMotion->start();
		}
		else if (_RogueDirection == ROGUE_LEFT_MOVE || _RogueDirection == ROGUE_LEFT_HIT)
		{
			_RogueDirection = ROGUE_LEFT_DIE;
			_RogueMotion = KEYANIMANAGER->findAnimation("RogueLeftDie");
			_RogueMotion->start();
		}
	}

}
