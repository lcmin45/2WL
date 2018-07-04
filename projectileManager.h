#pragma once
#include "gameNode.h"
#include "player.h"
#include "불꽃타격.h"
#include "바람베기.h"
#include "흙주먹.h"
#include "화염구.h"
#include "불타는올가미.h"

class player;

class projectileManager:public gameNode
{
private:
	불꽃타격 * firePunchAtt;
	바람베기 * windCutterAtt;
	흙주먹 * earthPunchAtt;

	화염구 * fireBallAtt;


	불타는올가미* fireSword;

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

