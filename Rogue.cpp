#include "stdafx.h"
#include "Rogue.h"


Rogue::Rogue()
{
}


Rogue::~Rogue()
{
}

HRESULT Rogue::init(const char * imgName, POINTFLOAT point, float speed)
{//¤±¤¤¤·
	sprintf_s(str, "%s", imgName);
	sprintf_s(str2, "image/monster/%s.bmp", imgName);


	_image = IMAGEMANAGER->addFrameImage(str, str2, 0, 0, 280 * 2, 200 * 2, 10, 4, true, RGB(255, 0, 255));

	_RogueDirection = ROGUE_RIGHT_STAND;
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
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightStand", str, rightStand, 1, 6, false);
	int leftStand[] = { 10 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftStand", str, leftStand, 1, 6, false);

	int rightMove[] = { 1,2,3,4,5 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightMove", str, rightMove, 5, 1, true);
	int leftMove[] = { 11,12,13,14,15 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftMove", str, leftMove, 5, 1, true);

	int rightAttack[] = { 6,7 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightAttack", str, rightAttack, 2, 1, false, rightStop, this);
	int leftAttack[] = { 16,17 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftAttack", str, leftAttack, 2, 1, false, leftStop, this);

	int rightHit[] = { 9,8 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightHit", str, rightHit, 2, 2, false);
	int leftHit[] = { 19,18 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftHit", str, leftHit, 2, 2, false);


	int rightDie[] = { 20,21,22,23,24,25,26 };
	KEYANIMANAGER->addArrayFrameAnimation("RogueRightDie", str, rightDie, 7, 1, false);
	int leftDie[] = { 30,31,32,33,34,35,36};
	KEYANIMANAGER->addArrayFrameAnimation("RogueLeftDie", str, leftDie, 7, 1, false);




	_RogueMotion = KEYANIMANAGER->findAnimation("RogueRightStand");

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

void Rogue::Test()
{

	_rc = RectMakeCenter(_x, _y, _image->getFrameWidth(),
		_image->getFrameHeight());

	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_RogueDirection = ROGUE_RIGHT_MOVE;
		_RogueMotion = KEYANIMANAGER->findAnimation("RogueRightMove");
		_RogueMotion->start();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_RogueDirection = ROGUE_LEFT_MOVE;
		_RogueMotion = KEYANIMANAGER->findAnimation("RogueLeftMove");
		_RogueMotion->start();
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_RogueDirection == ROGUE_RIGHT_MOVE || _RogueDirection == ROGUE_RIGHT_STAND)
		{
			_RogueDirection = ROGUE_RIGHT_ATTACK;
			_RogueMotion = KEYANIMANAGER->findAnimation("RogueRightAttack");
			_RogueMotion->start();
		}
		else if (_RogueDirection == ROGUE_LEFT_MOVE || _RogueDirection == ROGUE_LEFT_STAND)
		{
			_RogueDirection = ROGUE_LEFT_ATTACK;
			_RogueMotion = KEYANIMANAGER->findAnimation("RogueLeftAttack");
			_RogueMotion->start();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_RogueDirection == ROGUE_RIGHT_MOVE || _RogueDirection == ROGUE_RIGHT_HIT || _RogueDirection == ROGUE_RIGHT_STAND)
		{
			_RogueDirection = ROGUE_RIGHT_HIT;
			_RogueMotion = KEYANIMANAGER->findAnimation("RogueRightHit");
			_RogueMotion->start();
		}
		else if (_RogueDirection == ROGUE_LEFT_MOVE || _RogueDirection == ROGUE_LEFT_HIT || _RogueDirection == ROGUE_LEFT_STAND)
		{
			_RogueDirection = ROGUE_LEFT_HIT;
			_RogueMotion = KEYANIMANAGER->findAnimation("RogueLeftHit");
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
