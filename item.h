#pragma once
#include "gameNode.h"

enum TYPE { NONE, HP, DAMAGE, SPEED, CRITICAL };
enum STATUS { NOWHERE, ON_FIELD, IN_INVENTORY, IN_STORE };

struct EFFECT
{
	TYPE type;
	int amount;
};

class item : public gameNode
{
private:
	POINTFLOAT _position;
	STATUS _status;
	EFFECT _effect[2];
	image* _image;
	const char* _name;
	const char* _info;
public:
	item();
	~item();

	virtual HRESULT init(POINTFLOAT position, STATUS status, EFFECT effect0, EFFECT effect1, const char* imageName, const char* name, const char* info);
	virtual void release();
	virtual void update();
	virtual void render();

	EFFECT* getEffect() { return _effect; }
	image* getImage() { return _image; }
	const char* getName() { return _name; }
	const char* getInfo() { return _info; }
	void setPosition(POINTFLOAT position) { _position = position; }
	void setStatus(STATUS status) { _status = status; }
};