#pragma once
#include "gameNode.h"
#include "player.h"
#include "�Ҳ�Ÿ��.h"
#include "�ٶ�����.h"
#include "���ָ�.h"
#include "ȭ����.h"
#include "��Ÿ�¿ð���.h"
class projectileManager : public gameNode
{
private:
	player * _player;

	vector<�Ҳ�Ÿ��>			vFirePunchAtt;
	vector<�Ҳ�Ÿ��>::iterator	viFirePunchAtt;

	vector<�ٶ�����>			vWindCutterAtt;
	vector<�ٶ�����>::iterator	viWindCutterAtt;

	vector<���ָ�>			vEarthPunchAtt;
	vector<���ָ�>::iterator	viEarthPunchAtt;

	vector<ȭ����>			vFireBallAtt;
	vector<ȭ����>::iterator	viFireBallAtt;

	vector<��Ÿ�¿ð���>			vFireSword;
	vector<��Ÿ�¿ð���>::iterator	viFireSword;

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

