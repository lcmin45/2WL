#pragma once
#include "gameNode.h"
#include "player.h"
#include "阂采鸥拜.h"
#include "官恩海扁.h"
#include "入林冈.h"
#include "拳堪备.h"

class player;

class projectileManager:public gameNode
{
private:
	阂采鸥拜 * firePunchAtt;
	官恩海扁 * windCutterAtt;
	入林冈 * earthPunchAtt;

	拳堪备 * fireBallAtt;
	player* _player;

public:
	projectileManager();
	~projectileManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(const char * skillName);
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }
};

