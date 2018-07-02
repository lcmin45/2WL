#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "mapTile.h"
#include "mapToolBook.h"

class mapTool : public gameNode
{
private:
	mapTile*		_mapTile;
	mapToolBook*	_book;

	int				_moveSpeed;

	

public:
	mapTool();
	~mapTool();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void imageInit(void);
};

