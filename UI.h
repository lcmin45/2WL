#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "option.h"

class player;
class projectileManager;

class UI : public gameNode
{
private:
	image * _image;
	player* _player;
	projectileManager* _projectileManager;
	progressBar* _progressBar;
	option* _option;
	RECT _optionRC;
public:
	UI();
	~UI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* getLink) { _player = getLink; }
	void setProjectileManagerAddressLink(projectileManager* getLink) { _projectileManager = getLink; }
};