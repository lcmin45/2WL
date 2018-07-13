#pragma once
#include "gameNode.h"

class tileObject : public gameNode
{
private:
	image * _img;				// �̹���
	animation*	_animation;			// �ִϸ��̼�
	POINT		_tileCenterPoint;	// Ÿ�� ���� ����Ʈ
	POINT		_renderPoint;		// ����� ��ǥ

public:
	tileObject();
	~tileObject();

	virtual HRESULT init(int index);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setCenterPoint(POINT point) { _tileCenterPoint = point; }
	void setRenderPoint(POINT point) { _renderPoint = point; }
};

