#pragma once
#include "gameNode.h"

enum SUBJECT
{
	PLAYER, ENEMY
};

struct PARTICLE
{
	image* img;
	POINTFLOAT pt;
	RECT rc;
	int indexX;
	int indexY;
	float angle;
	float startTime;
};

class skill : public gameNode
{
protected:
	SUBJECT _subject;
	image* _img;
	RECT _rc;
	char _str[1024];
	POINTFLOAT _firePt;
	POINTFLOAT _pt;
	float _angle;
	float _speed;
	float _range;
	float _damage;
	float _coolTime;
	int _amount;
	int _frameIndex;
	float _startTime;

public:
	skill();
	~skill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//skillName : 1skill(�Ҳ�Ÿ��, �ٶ�����, ���ָ�) 2skill(ȭ����, �ͷ�ȸ����, �����ǹ���),3skill(��Ÿ�¿ð���,����Ŭ�кθ޶�,�����ǰ�)
	//����, ������ǥ, ����, ���ǵ�, ��Ÿ�, ������
	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	//��ų ������
	virtual void move();

	//������ �̹���
	virtual void frameCount();

	//�浹 ������ �簢��
	RECT getRect() { return _rc; }
	image* getImage() { return _img; }
	int getFrameIndex() { return _frameIndex; }
};