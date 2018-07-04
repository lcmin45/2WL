#pragma once
#include "gameNode.h"
#include "player.h"
#include "불꽃타격.h"
#include "바람베기.h"
#include "흙주먹.h"
#include "화염구.h"
#include "불타는올가미.h"
class projectileManager : public gameNode
{
private:
	player * _player;

	vector<불꽃타격>			vFirePunchAtt;
	vector<불꽃타격>::iterator	viFirePunchAtt;

	vector<바람베기>			vWindCutterAtt;
	vector<바람베기>::iterator	viWindCutterAtt;

	vector<흙주먹>			vEarthPunchAtt;
	vector<흙주먹>::iterator	viEarthPunchAtt;

	vector<화염구>			vFireBallAtt;
	vector<화염구>::iterator	viFireBallAtt;

	vector<불타는올가미>			vFireSword;
	vector<불타는올가미>::iterator	viFireSword;

public:
	projectileManager();
	~projectileManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void fire(const char * skillName);
	void vectorCheck();
	void vectorDraw();
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }
};

