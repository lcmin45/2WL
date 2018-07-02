#pragma once
#include "gameNode.h"
#include "skill.h"
#include "inventory.h"

#define SPEED 5.0f

enum DIRECTION { UP, DOWN, LEFT, RIGHT }; //����
enum ACTION { IDLE, MOVE, ATTACK1, ATTACK2, DASH }; //�ൿ
enum ANGLE { ANGLE0, ANGLE1, ANGLE2, ANGLE3, ANGLE4, ANGLE5, ANGLE6, ANGLE7 }; //���� (���� ���� 0���� 2PI���� 8����)

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
	float _speed; //���ǵ�
	float _dashSpeed; //�뽬 ���ǵ�

	projectileManager* _ptM; // ����ü �Ŵ��� ȣȯ

	//�ӽ�
	RECT _zOrderBox;
	RECT _box;
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
	static void afterAction(void* obj); //���ϸ��̼� �ݹ��

	DIRECTION getDirection() { return _direction; }
	void setAction(ACTION action) { _action = action; }
	void setAnimation(animation* animation) { _animation = animation; }


	//=======================��ų ��� =================
	POINTFLOAT getPosition() {return _position;}
	void setProjectileManagerAddressLink(projectileManager* getLink) { _ptM = getLink; }
};