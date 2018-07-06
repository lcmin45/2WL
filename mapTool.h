#pragma once
#include "gameNode.h"
#include "mapToolNode.h"
#include "mapTile.h"
#include "mapToolBook.h"

class miniMap;

class mapTool : public gameNode
{
private:
	mapTile*		_mapTile;		// Å¸ÀÏ¸Ê
	mapToolBook*	_book;			// Ã¥
	miniMap*		_miniMap;		// ¹Ì´Ï¸Ê

	int				_moveSpeed;		// È­¸é ¿òÁ÷ÀÓ ¼Óµµ¤¤

public:
	mapTool();
	~mapTool();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void miniMapViewUpdate(void);	// ¹Ì´Ï¸Ê µ¿ÀÛ
	void mapToolUpdate(void);		// ¸ÊÅø µ¿ÀÛ
	void inputKey(void);			// ÀÔ·ÂÅ° Ã³¸®

	void miniMapRender(void);	// ¹Ì´Ï¸Ê ·£´õ
	void mapToolRender(void);	// ¸ÊÅø ·»´õ
};

