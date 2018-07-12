#pragma once
#include "gameNode.h"

class ending : public gameNode
{
	int _index;
	image* _image;
	int _count;
public:
	ending();
	~ending();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};