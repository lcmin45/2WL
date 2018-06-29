#include "stdafx.h"
#include "player.h"

player::player() {}
player::~player() {}

HRESULT player::init()
{
	_position.x = WINSIZEX / 2;
	_position.y = WINSIZEY / 2;
	_direction = DOWN;
	_action = IDLE;
	_image = IMAGEMANAGER->addFrameImage("playerSprite", "image/player/playerSprite.bmp", 3200, 1600, 16, 8, true, RGB(255, 0, 255));

	int playerIdleUp[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleUp", "playerSprite", playerIdleUp, 1, 1, false);
	int playerIdleDown[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleDown", "playerSprite", playerIdleDown, 1, 1, false);
	int playerIdleLeft[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleLeft", "playerSprite", playerIdleLeft, 1, 1, false);
	int playerIdleRight[] = { 48 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleRight", "playerSprite", playerIdleRight, 1, 1, false);

	int playerMoveUp[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveUp", "playerSprite", playerMoveUp, 10, 10, true);
	int playerMoveDown[] = { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveDown", "playerSprite", playerMoveDown, 10, 10, true);
	int playerMoveLeft[] = { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveLeft", "playerSprite", playerMoveLeft, 10, 10, true);
	int playerMoveRight[] = { 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveRight", "playerSprite", playerMoveRight, 10, 10, true);

	int playerAttack1Up[] = { 64, 65, 66, 67, 68, 69, 70, 71 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Up", "playerSprite", playerAttack1Up, 8, 20, false, afterAttack, this);
	int playerAttack2Up[] = { 72, 73, 74, 75, 76, 77, 78, 79 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Up", "playerSprite", playerAttack2Up, 8, 20, false, afterAttack, this);
	int playerAttack1Down[] = { 80, 81, 82, 83, 84, 85, 86, 87 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Down", "playerSprite", playerAttack1Down, 8, 20, false, afterAttack, this);
	int playerAttack2Down[] = { 88, 89, 90, 91, 92, 93, 94, 95 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Down", "playerSprite", playerAttack2Down, 8, 20, false, afterAttack, this);
	int playerAttack1Left[] = { 96, 97, 98, 99, 100, 101, 102, 103 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Left", "playerSprite", playerAttack1Left, 8, 20, false, afterAttack, this);
	int playerAttack2Left[] = { 104, 105, 106, 107, 108, 109, 110, 111 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Left", "playerSprite", playerAttack2Left, 8, 20, false, afterAttack, this);
	int playerAttack1Right[] = { 112, 113, 114, 115, 116, 117, 118, 119 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Right", "playerSprite", playerAttack1Right, 8, 20, false, afterAttack, this);
	int playerAttack2Right[] = { 120, 121, 122, 123, 124, 125, 126, 127 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Right", "playerSprite", playerAttack2Right, 8, 20, false, afterAttack, this);

	_animation = KEYANIMANAGER->findAnimation("playerIdleDown");

	_body = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);

	_speed = 8.0f;

	return S_OK;
}

void player::release() {}

void player::update()
{
	keyProcess();
	KEYANIMANAGER->update();
}

void player::render()
{
	_image->aniRender(CAMERAMANAGER->getCameraDC(), _position.x - _image->getFrameWidth() / 2, _position.y - _image->getFrameHeight() / 2, _animation);
}

void player::keyProcess()
{
	if (KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D'))
	{
		if (KEYMANAGER->isStayKeyDown('W'))
		{
			_direction = UP;
			_action = MOVE;
			_position.y -= _speed;
		}
		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_direction = DOWN;
			_action = MOVE;
			_position.y += _speed;
		}
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_direction = LEFT;
			_action = MOVE;
			_position.x -= _speed;
		}
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_direction = RIGHT;
			_action = MOVE;
			_position.x += _speed;
		}
		if (KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('D') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) animationProcess();
	}
	else if (KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) { _action = IDLE; animationProcess(); }

	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_action = (_action == ATTACK1 ? ATTACK2 : ATTACK1);
		animationProcess();
	}

	_body = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);
}

void player::animationProcess()
{
	switch (_direction)
	{
	case UP:
		if (_action == IDLE) _animation = KEYANIMANAGER->findAnimation("playerIdleUp");
		else if (_action == MOVE) _animation = KEYANIMANAGER->findAnimation("playerMoveUp");
		else if (_action == ATTACK1) _animation = KEYANIMANAGER->findAnimation("playerAttack1Up");
		else if (_action == ATTACK2) _animation = KEYANIMANAGER->findAnimation("playerAttack2Up");
		break;
	case DOWN:
		if (_action == IDLE) _animation = KEYANIMANAGER->findAnimation("playerIdleDown");
		else if (_action == MOVE) _animation = KEYANIMANAGER->findAnimation("playerMoveDown");
		else if (_action == ATTACK1) _animation = KEYANIMANAGER->findAnimation("playerAttack1Down");
		else if (_action == ATTACK2) _animation = KEYANIMANAGER->findAnimation("playerAttack2Down");
		break;
	case LEFT:
		if (_action == IDLE) _animation = KEYANIMANAGER->findAnimation("playerIdleLeft");
		else if (_action == MOVE) _animation = KEYANIMANAGER->findAnimation("playerMoveLeft");
		else if (_action == ATTACK1) _animation = KEYANIMANAGER->findAnimation("playerAttack1Left");
		else if (_action == ATTACK2) _animation = KEYANIMANAGER->findAnimation("playerAttack2Left");
		break;
	case RIGHT:
		if (_action == IDLE) _animation = KEYANIMANAGER->findAnimation("playerIdleRight");
		else if (_action == MOVE) _animation = KEYANIMANAGER->findAnimation("playerMoveRight");
		else if (_action == ATTACK1) _animation = KEYANIMANAGER->findAnimation("playerAttack1Right");
		else if (_action == ATTACK2) _animation = KEYANIMANAGER->findAnimation("playerAttack2Right");
		break;
	}
	_animation->start();
}

void player::afterAttack(void* obj)
{
	player* temp = (player*)obj;
	temp->setAction(IDLE);
	switch (temp->getDirection())
	{
	case UP:
		temp->setAnimation(KEYANIMANAGER->findAnimation("playerIdleUp"));
		break;
	case DOWN:
		temp->setAnimation(KEYANIMANAGER->findAnimation("playerIdleDown"));
		break;
	case LEFT:
		temp->setAnimation(KEYANIMANAGER->findAnimation("playerIdleLeft"));
		break;
	case RIGHT:
		temp->setAnimation(KEYANIMANAGER->findAnimation("playerIdleRight"));;
		break;
	}
}