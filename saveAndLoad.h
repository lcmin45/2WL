#pragma once
#include "gameNode.h"
#include "saveAndLoad.h"
#include "item.h"

struct tagSaveInfo
{
	POINTFLOAT playerPosition;
	float currnetHp;
	int coin;
	POINTFLOAT itemPosition[10];
	STATUS status[10];
};

class player;
class itemManager;

class saveAndLoad : public gameNode
{
private:
	tagSaveInfo* _saveInfo;
public:
	saveAndLoad();
	~saveAndLoad();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void save(tagSaveInfo* saveInfo);
	tagSaveInfo* load();
};