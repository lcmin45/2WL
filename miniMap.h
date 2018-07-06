#pragma once
#include "gameNode.h"
#include "current.h"

class miniMap : public gameNode
{
private:
	image*	_miniMap;				// ��ü ���� ����Ͽ� �̴ϸ� �̹����� ��

public:
	miniMap();
	~miniMap();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setMiniMap(HDC hdc);		// ��ü �� �̹����� ����
};

