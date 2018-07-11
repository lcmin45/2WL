#pragma once
#include "skill.h"
#include "player.h"

struct WOODPARTICLE
{
	image* img;
	POINTFLOAT pt;
	RECT rc;
	int frameIndex;
};

class ³ª¹«¼Ú±â : public skill
{
private:
	player * _player;
	vector<WOODPARTICLE*>			vWood;
	vector<WOODPARTICLE*>::iterator	viWood;
	int _fireCount;
public:
	³ª¹«¼Ú±â();
	~³ª¹«¼Ú±â();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	virtual void fire(const char * skillName, int amount, POINTFLOAT pt, float angle, float speed, float range, float damage, float coolTime, SUBJECT subject);

	virtual void move();
	virtual void frameCount();
	void woodVector();
	void getPlayerAddressLink(player* player) { _player = player; }
};

