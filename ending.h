#pragma once
#include "gameNode.h"

class ending : public gameNode
{
	int _index; //�̹��� �ε���
	image* _image; //���� �̹���
	int _count; //�ε��� ī��Ʈ
public:
	ending();
	~ending();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};