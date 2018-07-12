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

enum DIRECTION { UP, DOWN, LEFT, RIGHT }; //����
enum ACTION { IDLE, MOVE, ATTACK1, ATTACK2, DASH, FIREBALL, FIRESWORD, WINDSTORM, DEAD }; //�ൿ
enum ANGLE { ANGLE0, ANGLE1, ANGLE2, ANGLE3, ANGLE4, ANGLE5, ANGLE6, ANGLE7 }; //���� (���� ���� 0���� 2PI���� 8����)

class tagMapToolTile;
class itemManager;
class projectileManager;
class enemyManager;

class player : public gameNode
{
private:
	POINTFLOAT _position; //��ǥ
	DIRECTION _direction; //����
	ACTION _action; //�ൿ
	ANGLE _angle; //����
	image* _image; //�̹���
	animation* _animation; //���ϸ��̼�
	RECT _body; //�ٵ�
	RECT _tileCheck; //Ÿ�� �浹 üũ�� ��Ʈ
	float _maxHp; //�ִ� ü��
	float _currentHp; //���� ü��
	float _damage; //���ݷ�
	float _speed; //���ǵ�
	float _critical; //ġ��Ÿ��
	float _dashSpeed; //�뽬 ���ǵ�
	float _dashCoolTime;
	int _coin; //����
	tagMapToolTile* _tile; //Ÿ�� ����
	itemManager* _itemManager; //�κ��丮
	projectileManager* _ptM; // ����ü �Ŵ��� ȣȯ
	bool _canTakeItem; //������ �ݱ� �������� ����
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

	void keyProcess(); //Ű �Է� ó��
	void attackAngleProcess(); //���� ���� ó��
	void animationProcess(); //���ϸ��̼� ó��
	void moveProcess(); //�̵� ó��
	void collisionCheckWithTile(); //Ÿ�� �浹 ó��
	void collisionCheckWithItem(); //������ �浹 ó��
	void inventoryProcess(); //�κ��丮 ó��
	void playerHpCheck(); //�÷��̾� ü�� üũ
	static void afterActionCallBack(void* obj); //���ϸ��̼� �ݹ��
	void afterAction(); //���ϸ��̼� �ݹ��
	static void playerDead(void* obj); //�÷��̾� ���� �ݹ��


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