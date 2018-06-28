#pragma once
#include "gameNode.h"
#include "skill.h"
#include "inventory.h"

enum DIRECTION { UP, DOWN, LEFT, RIGHT };
enum ACTION { IDLE, MOVE, ATTACK1, ATTACK2 };

class player : public gameNode
{
private:
	POINTFLOAT _position;
	DIRECTION _direction;
	ACTION _action;
	image* _image;
	animation* _animation;
	RECT _body;
	float _speed;
public:
	player();
	~player();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyProcess();
	void animationProcess();
	static void afterAttack(void* obj);

	DIRECTION getDirection() { return _direction; }
	void setAction(ACTION action) { _action = action; }
	void setAnimation(animation* animation) { _animation = animation; }
};