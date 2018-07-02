#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class inventory : public gameNode
{
private:
	vector<item*> _vItem;
	vector<item*>::iterator _viItem;
	POINTFLOAT _position;
	image* _image;
	RECT _itemRect[3];
	bool _isOpen;
public:
	inventory();
	~inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyProcess();

	void addItem(item* item);
	const char* dumpItem(int index);
};