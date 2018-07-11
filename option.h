#pragma once
#include "gameNode.h"

class option : public gameNode
{
private:
	bool	_isView;
	float	_effectX;
	float	_bgmX;


public:
	option();
	~option();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();




	void setIsView(bool isView) { _isView = isView; }
	bool getIsView(void) { return _isView; }
};