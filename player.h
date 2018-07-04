#pragma once
#include "gameNode.h"
#include "item.h"
#include "skill.h"

#define PLAYER_HP 500.0f
#define PLAYER_DAMAGE 1.0f
#define PLAYER_SPEED 3.0f
#define PLAYER_CRITICAL 10.0f

enum DIRECTION { UP, DOWN, LEFT, RIGHT }; //����
enum ACTION { IDLE, MOVE, ATTACK1, ATTACK2, DASH, FIREBALL, FIRESWORD }; //�ൿ
enum ANGLE { ANGLE0, ANGLE1, ANGLE2, ANGLE3, ANGLE4, ANGLE5, ANGLE6, ANGLE7 }; //���� (���� ���� 0���� 2PI���� 8����)

class itemManager;
class projectileManager;

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
	float _maxHp; //�ִ� ü��
	float _currentHp; //���� ü��
	float _damage; //���ݷ�
	float _speed; //���ǵ�
	float _critical; //ġ��Ÿ��
	float _dashSpeed; //�뽬 ���ǵ�
	itemManager* _itemManager; //�κ��丮
	projectileManager* _ptM; // ����ü �Ŵ��� ȣȯ
	bool _canTakeItem;
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
	void actionProcess(); //�ൿ ó��
	void collisionProcess();
	void inventoryProcess(); //�κ��丮 ó��
	static void afterAction(void* obj); //���ϸ��̼� �ݹ��

	POINTFLOAT getPosition() { return _position; }
	DIRECTION getDirection() { return _direction; }
	float getMaxHp() { return _maxHp; }
	float getCurrentHp() { return _currentHp; }
	bool getCanTakeItem() { return _canTakeItem; }
	void setAction(ACTION action) { _action = action; }
	void setAnimation(animation* animation) { _animation = animation; }
	void setItemManagerAddressLink(itemManager* getLink) { _itemManager = getLink; }
	void setProjectileManagerAddressLink(projectileManager* getLink) { _ptM = getLink; }
};