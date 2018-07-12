#pragma once
#include "gameNode.h"
#include "item.h"
#include "skill.h"
#include "UI.h"
#include "skillSet.h"

#define PLAYER_MOVE_ANI_SPEED 10
#define PLAYER_ACTION_ANI_SPEED 20

#define PLAYER_HP 50000.0f
#define PLAYER_DAMAGE 1.0f
#define PLAYER_SPEED 3.0f
#define PLAYER_CRITICAL 10.0f
#define PLAYER_DASH_SPEED 4.0f

enum DIRECTION { UP, DOWN, LEFT, RIGHT }; //방향
enum ACTION { IDLE, MOVE, ATTACK1, ATTACK2, DASH, FIREBALL, FIRESWORD, WINDSTORM, DEAD }; //행동
enum ANGLE { ANGLE0, ANGLE1, ANGLE2, ANGLE3, ANGLE4, ANGLE5, ANGLE6, ANGLE7 }; //각도 (라디안 기준 0부터 2PI까지 8분할)

class tagMapToolTile;
class itemManager;
class projectileManager;
class enemyManager;

class player : public gameNode
{
private:
	POINTFLOAT _position; //좌표
	DIRECTION _direction; //방향
	ACTION _action; //행동
	ANGLE _angle; //각도
	image* _image; //이미지
	animation* _animation; //에니매이션
	RECT _body; //바디
	RECT _tileCheck; //타일 충돌 체크용 렉트
	float _maxHp; //최대 체력
	float _currentHp; //현재 체력
	float _damage; //공격력
	float _speed; //스피드
	float _critical; //치명타율
	float _dashSpeed; //대쉬 스피드
	float _dashCoolTime;
	int _coin; //코인
	tagMapToolTile* _tile; //타일 정보
	itemManager* _itemManager; //인벤토리
	projectileManager* _ptM; // 투사체 매니저 호환
	bool _canTakeItem; //아이템 줍기 가능인지 여부
	bool _isDead;
	int _playerTileIndex;
	skillSet* _skillSet;
	enemyManager* _enemyManager;

public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyProcess(); //키 입력 처리
	void attackAngleProcess(); //공격 각도 처리
	void animationProcess(); //에니매이션 처리
	void moveProcess(); //이동 처리
	void collisionCheckWithTile(); //타일 충돌 처리
	void collisionCheckWithItem(); //아이템 충돌 처리
	void inventoryProcess(); //인벤토리 처리
	void playerHpCheck(); //플레이어 체력 체크
	static void afterActionCallBack(void* obj); //에니매이션 콜백용
	void afterAction(); //에니매이션 콜백용
	static void playerDead(void* obj); //플레이어 죽음 콜백용


	RECT getBody() { return _body; }
	POINTFLOAT getPosition() { return _position; }
	DIRECTION getDirection() { return _direction; }
	float getMaxHp() { return _maxHp; }
	float getCurrentHp() { return _currentHp; }
	float getDamage() { return _damage; }
	float getCritical() { return _critical; }
	int getPlayerIndex() { return _playerTileIndex; }
	int getCoin() { return _coin; }
	bool getCanTakeItem() { return _canTakeItem; }
	bool getIsDead() { return _isDead; }
	void setPlayerHit(float att) { _currentHp -= att; }
	skillSet* getSkillSet() { return _skillSet; }
	void setIsDead(bool isDead) { _isDead = isDead; }
	void setTileAddressLink(tagMapToolTile* getLink) { _tile = getLink; }
	void setItemManagerAddressLink(itemManager* getLink) { _itemManager = getLink; }
	void setProjectileManagerAddressLink(projectileManager* getLink) { _ptM = getLink; }
	void setSaveInfo(POINTFLOAT position, float currentHp, int coin);
	RECT getPlayerRect() { return _body; }
	void setPosition(POINTFLOAT position) { _position = position; }

	void setEnemyManagerAddressLink(enemyManager* em) { _enemyManager = em; }
};