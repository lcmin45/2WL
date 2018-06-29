#pragma once
#include "gameNode.h"
#include "mapToolBook.h"

class mapTool : public gameNode
{
private:
	mapToolBook * _book;

public:
	mapTool();
	~mapTool();

	virtual HRESULT init(void);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);
};
