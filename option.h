#pragma once
#include "gameNode.h"

class option : public gameNode
{
private:
	struct tagIcon
	{
		image*	barImg;
		RECT	barRc;
		image*	iconImg;
		RECT	iconRc;
		float	iconX;
		float	volume;
	};

private:
	tagIcon		_bgm;
	tagIcon		_eff;

	bool		_isView;
	RECT		_button;
	
public:
	option();
	~option();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setIsView(bool isView);
	bool getIsView(void) { return _isView; }
};