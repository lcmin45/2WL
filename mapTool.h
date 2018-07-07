#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "mapTile.h"
#include "mapToolBook.h"

class miniMap;

class mapTool : public gameNode
{
private:
	mapTile*		_mapTile;		// Ÿ�ϸ�
	mapToolBook*	_book;			// å
	miniMap*		_miniMap;		// �̴ϸ�

	int				_moveSpeed;		// ȭ�� ������ �ӵ���

public:
	mapTool();
	~mapTool();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void miniMapViewUpdate(void);	// �̴ϸ� ����
	void mapToolUpdate(void);		// ���� ����
	void inputKey(void);			// �Է�Ű ó��

	void miniMapRender(void);	// �̴ϸ� ����
	void mapToolRender(void);	// ���� ����
};

