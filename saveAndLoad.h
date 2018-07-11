#pragma once
#include "gameNode.h"
#include "saveAndLoad.h"
#include "item.h"
#include "skillSet.h"

struct tagSaveInfo
{
	POINTFLOAT playerPosition;
	float currnetHp;
	int coin;
	POINTFLOAT itemPosition[10];
	STATUS itemStatus[10];
	tagSkillSet skillSet[7];
};

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