#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class store : public gameNode
{
private:
	POINTFLOAT _position;
	vector<item*> _vItem;
	image* _image;
public:
	store();
	~store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void addItem(item* item);
	void sellItem(item* item);
};