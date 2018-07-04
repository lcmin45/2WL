#pragma once
#include "gameNode.h"
#include "progressBar.h"

class player;

class UI : public gameNode
{
private:
	image * _image;
	player* _player;
	progressBar* _progressBar;
public:
	UI();
	~UI();
	
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* getLink) { _player = getLink; }
};