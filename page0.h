#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "current.h"

class mapTile;

class page0 : public gameNode
{
private:
#define MAXBOX 6

private:
	tagBox	_box[MAXBOX];
	POINT	_center;

	mapTile* _mapTile;
public:
	page0();
	~page0();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void boxInit(void);					// �ڽ� �ʱ�ȭ

	void checkBox(void);				// �ڽ� ���ý� ���� ���� ����

	void boxRender(void);				// �ڽ� ����
	void fontRender(void);				// ��Ʈ ����

	void setCenterPoint(POINT point);	// å�� ���� ��ǥ�� �޾ƿ� �ڽ��� ��ġ�� �缳��

	void setMapTileClass(mapTile* mapTile) { _mapTile = mapTile; }
};