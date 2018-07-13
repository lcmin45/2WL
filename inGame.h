#pragma once
#include "gameNode.h"
#include "projectileManager.h"
#include "enemyManager.h"
#include "itemManager.h"
#include "scenePart.h"
#include "player.h"
#include "store.h"
#include "UI.h"
#include "stage.h"
#include "Astar.h"
#include "saveAndLoad.h"

struct HITEFFECT
{
	image* img;						//맞는 이펙트 구조체
	POINT pt;						//맞는 이펙트 좌표
	RECT rc;						//맞는 이펙트 렉트
	int frameIndex;					//맞는 이펙트 프레임 번호
};

class inGame : public gameNode
{
private:

	vector<HITEFFECT*>				vEffect;
	vector<HITEFFECT*>::iterator	viEffect;

	UI * _UI;
	player* _player;
	itemManager* _itemManager;
	projectileManager* _ptM;
	enemyManager* _enemyManager;
	stage * _stage;
	Astar* _Astar;
	saveAndLoad* _saveAndLoad;

	int _count;

public:
	inGame();
	~inGame();

	HRESULT init();
	HRESULT init(void* obj);
	void release();
	void update();
	void render();

	void saveData();

	void collide();


	void createEffect(RECT rect);
	void updateEffect();
	void drawEffect();
};