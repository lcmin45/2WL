#pragma once
#include "gameNode.h"
#include "player.h"
#include "mapToolNode.h"
#include "불꽃타격.h"
#include "바람베기.h"
#include "흙주먹.h"
#include "화염구.h"
#include "불타는올가미.h"
#include "맹렬회오리.h"
#include "사이클론부메랑.h"
#include "몬스터근접.h"
#include "몬스터총알.h"
#include "얼음던지기매니저.h"
#include "우박.h"
#include "돌던지기.h"
#include "나무솟기.h"
#include "메테오.h"
#include "불기둥.h"

struct tagCoolTime
{
	const char* name;
	float coolTime;
	float skillTime;
};

class projectileManager : public gameNode
{
private:
	player * _player;
	tagMapToolTile* _tile;

	vector<skill*>				vSkill;
	vector<skill*>::iterator	viSkill;

	tagCoolTime coolTime[7];

public:
	projectileManager();
	~projectileManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool fire(string skillName);
	void fire(const char * skillName, POINTFLOAT pt);
	void vectorCheck();
	void vectorDraw();
	void setPlayerAddressLink(player* getPlayer) { _player = getPlayer; }
	void setTileAddressLink(tagMapToolTile* getLink) { _tile = getLink; }


	vector<skill*>				getVSkill() { return vSkill; };
	vector<skill*>::iterator	getViSkill() { return viSkill; };
	float getCoolTime(const char* name);
};

