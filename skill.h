#pragma once
#include "gameNode.h"

class skill : public gameNode
{
private:
	image* img;
	RECT _rc;
	const char* str[1024];
	float _x, _y;
	float _speed;
	float _range;
	float _damage;
	int _frameIndex;

public:
	skill();
	~skill();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//skillName
	//�Ҳ�Ÿ��, �ٶ�����, ���ָ�
	//ȭ������, ��������, ���ñ�
	//ȭ����, �ͷ�ȸ����, �����ǹ���
	//��Ÿ�¿ð���,����Ŭ�кθ޶�,�����ǰ�
	void fire(char* skillName, float x, float y, float speed, float range, float damage);
	void move();
};