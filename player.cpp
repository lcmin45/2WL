#include "stdafx.h"
#include "player.h"
#include "itemManager.h"
#include "projectileManager.h"

player::player() {}
player::~player() {}

HRESULT player::init() //초기화
{
	_position.x = WINSIZEX / 2;
	_position.y = WINSIZEY / 2;
	_direction = DOWN;
	_action = IDLE;
	_angle = ANGLE3;
	_image = IMAGEMANAGER->findImage("player");

	int playerIdleUp[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleUp", "player", playerIdleUp, 1, 1, false);
	int playerIdleDown[] = { 16 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleDown", "player", playerIdleDown, 1, 1, false);
	int playerIdleLeft[] = { 32 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleLeft", "player", playerIdleLeft, 1, 1, false);
	int playerIdleRight[] = { 48 };
	KEYANIMANAGER->addArrayFrameAnimation("playerIdleRight", "player", playerIdleRight, 1, 1, false);

	int playerMoveUp[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveUp", "player", playerMoveUp, 10, PLAYER_MOVE_ANI_SPEED, true);
	int playerMoveDown[] = { 17, 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveDown", "player", playerMoveDown, 10, PLAYER_MOVE_ANI_SPEED, true);
	int playerMoveLeft[] = { 33, 34, 35, 36, 37, 38, 39, 40, 41, 42 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveLeft", "player", playerMoveLeft, 10, PLAYER_MOVE_ANI_SPEED, true);
	int playerMoveRight[] = { 49, 50, 51, 52, 53, 54, 55, 56, 57, 58 };
	KEYANIMANAGER->addArrayFrameAnimation("playerMoveRight", "player", playerMoveRight, 10, PLAYER_MOVE_ANI_SPEED, true);

	int playerAttack1Up[] = { 64, 65, 66, 67, 68, 69, 70, 71 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Up", "player", playerAttack1Up, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack2Up[] = { 72, 73, 74, 75, 76, 77, 78, 79 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Up", "player", playerAttack2Up, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack1Down[] = { 80, 81, 82, 83, 84, 85, 86, 87 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Down", "player", playerAttack1Down, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack2Down[] = { 88, 89, 90, 91, 92, 93, 94, 95 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Down", "player", playerAttack2Down, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack1Left[] = { 96, 97, 98, 99, 100, 101, 102, 103 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Left", "player", playerAttack1Left, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack2Left[] = { 104, 105, 106, 107, 108, 109, 110, 111 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Left", "player", playerAttack2Left, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack1Right[] = { 112, 113, 114, 115, 116, 117, 118, 119 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack1Right", "player", playerAttack1Right, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerAttack2Right[] = { 120, 121, 122, 123, 124, 125, 126, 127 };
	KEYANIMANAGER->addArrayFrameAnimation("playerAttack2Right", "player", playerAttack2Right, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);

	int playerDashUp[] = { 128, 129, 130, 131, 132, 133, 134, 135, 136, 136, 136, 136, 136 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDashUp", "player", playerDashUp, 13, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerDashDown[] = { 144, 145, 146, 147, 148, 149, 150, 151, 152, 152, 152, 152, 152 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDashDown", "player", playerDashDown, 13, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerDashLeft[] = { 160, 161, 162, 163, 164, 165, 166, 167, 168, 168, 168, 168, 168 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDashLeft", "player", playerDashLeft, 13, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerDashRight[] = { 176, 177, 178, 179, 180, 181, 182, 183, 184, 184, 184, 184, 184 };
	KEYANIMANAGER->addArrayFrameAnimation("playerDashRight", "player", playerDashRight, 13, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);

	int playerKickUp[] = { 192, 193, 194, 195, 196, 197, 198, 199 };
	KEYANIMANAGER->addArrayFrameAnimation("playerKickUp", "player", playerKickUp, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerKickDown[] = { 208, 209, 210, 211, 212, 213, 214, 215 };
	KEYANIMANAGER->addArrayFrameAnimation("playerKickDown", "player", playerKickDown, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerKickLeft[] = { 224, 225, 226, 227, 228, 229, 230, 231 };
	KEYANIMANAGER->addArrayFrameAnimation("playerKickLeft", "player", playerKickLeft, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerKickRight[] = { 240, 241, 242, 243, 244, 245, 246, 247 };
	KEYANIMANAGER->addArrayFrameAnimation("playerKickRight", "player", playerKickRight, 8, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);

	int playerBangUp[] = { 256, 257, 258, 259, 260, 261, 262, 263, 263, 263, 263, 263, 264, 265 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBangUp", "player", playerBangUp, 14, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);
	int playerBangDown[] = { 272, 273, 274, 275, 276, 277, 278, 279, 279, 279, 279, 279, 280, 281 };
	KEYANIMANAGER->addArrayFrameAnimation("playerBangDown", "player", playerBangDown, 14, PLAYER_ACTION_ANI_SPEED, false, afterAction, this);

	_animation = KEYANIMANAGER->findAnimation("playerIdleDown");

	_body = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);

	_maxHp = _currentHp = PLAYER_HP;
	_damage = PLAYER_DAMAGE;
	_speed = PLAYER_SPEED;
	_critical = PLAYER_CRITICAL;
	_coin = 0;

	_canTakeItem = false;

	return S_OK;
}

void player::release() {}

void player::update()
{
	keyProcess();
	actionProcess();
	collisionProcess();
	inventoryProcess();
	CAMERAMANAGER->setCameraPoint(_position);

	//////////////////////////////////////////////임시
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		_currentHp -= 5.0f;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_itemManager->dropCoin({ float(getMousePoint().x), float(getMousePoint().y) });
	}
	/////////////////////////////////////////////////
}

void player::render()
{
	_image->aniRender(getMemDC(), _position.x - _image->getFrameWidth() / 2, _position.y - _image->getFrameHeight() / 2, _animation);

	//임시
	char temp[128];
	sprintf_s(temp, "HP : %f / %f | DAMAGE : %f | SPEED : %f | CRITICAL : %f", _currentHp, _maxHp, _damage, _speed, _critical);
	TextOut(CAMERAMANAGER->getCameraDC(), WINSIZEX - 700, 50, temp, strlen(temp));
}

void player::keyProcess()
{
	if (_itemManager->getInventory()->getIsOpen()) return;

	//이동 키 입력시
	if ((KEYMANAGER->isStayKeyDown('W') || KEYMANAGER->isStayKeyDown('S') || KEYMANAGER->isStayKeyDown('A') || KEYMANAGER->isStayKeyDown('D')) && (_action == IDLE || _action == MOVE))
	{
		//단일 이동 키 입력
		if (KEYMANAGER->isStayKeyDown('W')) { _direction = UP; _action = MOVE; _angle = ANGLE2; }
		if (KEYMANAGER->isStayKeyDown('S')) { _direction = DOWN; _action = MOVE; _angle = ANGLE6; }
		if (KEYMANAGER->isStayKeyDown('A')) { _direction = LEFT; _action = MOVE; _angle = ANGLE4; }
		if (KEYMANAGER->isStayKeyDown('D')) { _direction = RIGHT; _action = MOVE; _angle = ANGLE0; }

		//대각선 이동 키 입력
		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('D'))
		{
			_direction = RIGHT;
			_action = MOVE;
			_angle = ANGLE1;
		}
		if (KEYMANAGER->isStayKeyDown('W') && KEYMANAGER->isStayKeyDown('A'))
		{
			_direction = LEFT;
			_action = MOVE;
			_angle = ANGLE3;
		}
		if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('A'))
		{
			_direction = LEFT;
			_action = MOVE;
			_angle = ANGLE5;
		}
		if (KEYMANAGER->isStayKeyDown('S') && KEYMANAGER->isStayKeyDown('D'))
		{
			_direction = RIGHT;
			_action = MOVE;
			_angle = ANGLE7;
		}
		//이동 키 업다운 때 마다 에니매이션 갱신
		if (KEYMANAGER->isOnceKeyDown('W') || KEYMANAGER->isOnceKeyDown('S') || KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('D') || KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) animationProcess();
	}
	//모든 이동 키에 입력이 없을 경우 행동은 IDLE, 에니매이션 갱신
	else if ((KEYMANAGER->isOnceKeyUp('W') || KEYMANAGER->isOnceKeyUp('S') || KEYMANAGER->isOnceKeyUp('A') || KEYMANAGER->isOnceKeyUp('D')) && (_action == IDLE || _action == MOVE)) { _action = IDLE; animationProcess(); }

	//마우스 왼쪽(공격 키 입력)
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_action = (_action == ATTACK1 ? ATTACK2 : ATTACK1);
		attackAngleProcess();
		animationProcess();
		_ptM->fire("바람베기");
	}
	//쉬프트(대쉬 키 입력)
	if (KEYMANAGER->isOnceKeyDown(VK_SHIFT)) //쿨타임 추가 해야함
	{
		if (_angle == ANGLE1 || _angle == ANGLE3) _direction = UP;
		else if (_angle == ANGLE5 || _angle == ANGLE7) _direction = DOWN;
		_action = DASH;
		_dashSpeed = 4;
		animationProcess();
	}

	//스킬 사용
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		_action = (_action == ATTACK1 ? ATTACK2 : ATTACK1);
		attackAngleProcess();
		animationProcess();
		_ptM->fire("불꽃타격");
	}
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		_action = (_action == ATTACK1 ? ATTACK2 : ATTACK1);
		attackAngleProcess();
		animationProcess();
		_ptM->fire("흙주먹");
	}
	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		_action = FIREBALL;
		attackAngleProcess();
		animationProcess();
		_ptM->fire("화염구");
	}
	if (KEYMANAGER->isOnceKeyDown('V'))
	{
		_action = FIRESWORD;
		attackAngleProcess();
		animationProcess();
		_ptM->fire("불타는올가미");
	}
}

void player::attackAngleProcess()
{
	//플레이어와 마우스 포인터의 각도
	float tempAngle = getAngle(_position.x, _position.y, getMousePoint().x, getMousePoint().y);

	if ((tempAngle > 0 && tempAngle <= PI / 4) || (tempAngle > PI / 4 * 7 && tempAngle <= PI2)) { _direction = RIGHT; _angle = ANGLE0; }
	else if (tempAngle <= PI / 4 * 3) { _direction = UP; _angle = ANGLE2; }
	else if (tempAngle <= PI / 4 * 5) { _direction = LEFT; _angle = ANGLE4; }
	else if (tempAngle <= PI / 4 * 7) { _direction = DOWN; _angle = ANGLE6; }

	if (_action == FIRESWORD) { if (tempAngle >= 0 && tempAngle < PI) _direction = UP; else _direction = DOWN; }
}

void player::animationProcess()
{
	char temp[30] = "player";
	//행동에 맞게 에니매이션 이름 추가
	switch (_action)
	{
	case IDLE: strcat_s(temp, "Idle"); break;
	case MOVE: strcat_s(temp, "Move"); break;
	case ATTACK1: strcat_s(temp, "Attack1"); break;
	case ATTACK2: strcat_s(temp, "Attack2"); break;
	case DASH: strcat_s(temp, "Dash"); break;
	case FIREBALL: strcat_s(temp, "Kick"); break;
	case FIRESWORD: strcat_s(temp, "Bang"); break;
	}
	//방향에 맞게 에니매이션 이름 추가
	switch (_direction)
	{
	case UP: strcat_s(temp, "Up"); break;
	case DOWN: strcat_s(temp, "Down"); break;
	case LEFT: strcat_s(temp, "Left"); break;
	case RIGHT: strcat_s(temp, "Right"); break;
	}
	//에니매이션 변경
	_animation = KEYANIMANAGER->findAnimation(temp);
	//에니매이션 시작
	_animation->start();
}

void player::actionProcess()
{
	//이동 혹은 대쉬
	if (_action == MOVE || _action == DASH)
	{
		//대각선 이동 시 스피드 밸런스용
		float temp = 0.75f;

		if (_angle == ANGLE0) _position.x += (_action == MOVE ? _speed : _speed * _dashSpeed);
		else if (_angle == ANGLE1) { _position.x += (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); _position.y -= (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); }
		else if (_angle == ANGLE2) _position.y -= (_action == MOVE ? _speed : _speed * _dashSpeed);
		else if (_angle == ANGLE3) { _position.x -= (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); _position.y -= (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); }
		else if (_angle == ANGLE4) _position.x -= (_action == MOVE ? _speed : _speed * _dashSpeed);
		else if (_angle == ANGLE5) { _position.x -= (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); _position.y += (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); }
		else if (_angle == ANGLE6) _position.y += (_action == MOVE ? _speed : _speed * _dashSpeed);
		else if (_angle == ANGLE7) { _position.x += (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); _position.y += (_action == MOVE ? _speed * temp : _speed * _dashSpeed * temp); }
		//대쉬일 경우 미끄러지는 속도 구현용
		if (_action == DASH) _dashSpeed -= 0.1f;
	}

	//바디 갱신
	_body = RectMakeCenter(_position.x, _position.y, _image->getFrameWidth() / 2, _image->getFrameHeight() / 2);
}

void player::collisionProcess()
{
	//아이템 줍기 가능 여부 체크
	_canTakeItem = false;
	for (int i = 0; i < _itemManager->getVItem().size(); i++)
	{
		if (getDistance(_position.x, _position.y, _itemManager->getVItem()[i]->getPosition().x, _itemManager->getVItem()[i]->getPosition().y) <= 25)
		{
			if (_itemManager->getVItem()[i]->getEffect()[0].type == COIN)
			{
				_coin += _itemManager->getVItem()[i]->getEffect()[0].amount;
				_itemManager->takeCoin(i);
			}
			else
			{
				_canTakeItem = true;
				if (KEYMANAGER->isOnceKeyDown('F'))
				{
					if (_itemManager->getVItem()[i]->getStatus() == IN_STORE)
					{
						if (_itemManager->sellItem(_itemManager->getVItem()[i]))
						{
							_coin -= _itemManager->getVItem()[i]->getPrice(); break;
						}
					}
					else if (_itemManager->getVItem()[i]->getStatus() == ON_FIELD)
					{
						if (_itemManager->addItem(_itemManager->getVItem()[i])) break;
					}
				}
			}
		}
	}
}

void player::inventoryProcess()
{
	_maxHp = PLAYER_HP;
	_damage = PLAYER_DAMAGE;
	_speed = PLAYER_SPEED;
	_critical = PLAYER_CRITICAL;

	for (int i = 0; i < _itemManager->getInventory()->getVItem().size(); i++)
	{
		item* item = _itemManager->getInventory()->getVItem()[i];
		for (int j = 0; j < 2; j++)
		{
			switch (item->getEffect()[j].type)
			{
			case NONE:
				break;
			case HP:
				_maxHp += _maxHp * item->getEffect()[j].amount / 100;
				break;
			case DAMAGE:
				_damage += _damage * item->getEffect()[j].amount / 100;
				break;
			case SPEED:
				_speed += _speed * item->getEffect()[j].amount / 100;
				break;
			case CRITICAL:
				_critical += _critical * item->getEffect()[j].amount / 100;
				break;
			}
		}
	}

	if (_currentHp > _maxHp) _currentHp = _maxHp;
}

void player::afterAction(void* obj)
{
	player* temp = (player*)obj;
	temp->setAction(IDLE);
	temp->keyProcess();
	temp->animationProcess();
}