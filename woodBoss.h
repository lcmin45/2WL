#pragma once
#include "boss.h"
class woodBoss : public boss
{
private:

	bool _isCheck; //�������� 0���� ����� ���� ����
public:
	woodBoss();
	~woodBoss();


	virtual void render();
	virtual void update();
	virtual void woodMove();
	virtual void woodSkill();
};

