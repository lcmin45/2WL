#pragma once
#include "gameNode.h"

enum TYPE { NONE, HP, DAMAGE, SPEED, CRITICAL, COIN };
enum STATUS { NOWHERE, ON_FIELD, IN_INVENTORY, IN_STORE };

struct EFFECT
{
	TYPE type; //������ ȿ��
	int amount; //ȿ���� ��ġ
};

class item : public gameNode
{
private:
	POINTFLOAT _position; //��ǥ
	STATUS _status; //���� ��� �ִ���
	EFFECT _effect[2]; //�� ������ �� ���� ȿ���� 2��
	image* _image; //�̹���
	const char* _name; //�̸�
	const char* _info; //����
	float _speed; //���ο� ���ǵ�
	animation* _animation; //���ο� �ִϸ��̼�
public:
	item();
	~item();

	virtual HRESULT init(POINTFLOAT position, STATUS status, EFFECT effect0, EFFECT effect1, const char* imageName, const char* name, const char* info);
	virtual void release();
	virtual void update();
	virtual void render();
	void coinMove(float angle); //���ο� ������ �Լ�

	POINTFLOAT getPosition() { return _position; }
	STATUS getStatus() { return _status; }
	EFFECT* getEffect() { return _effect; }
	image* getImage() { return _image; }
	const char* getName() { return _name; }
	const char* getInfo() { return _info; }
	void setPosition(POINTFLOAT position) { _position = position; }
	void setStatus(STATUS status) { _status = status; }
};