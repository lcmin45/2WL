#pragma once
#include "gameNode.h"
#include "monster.h"
#include "boss.h"
#include "fireBoss.h"
#include "iceBoss.h"
#include "woodBoss.h"
#include "stage.h"
#include "projectileManager.h"

#include <vector>
#include "Ghoul.h"
#include "Knight.h"
#include "Mage.h"
#include "Rogue.h"
#include "Scarecrow.h"

class itemManager;
class enemyManager : public gameNode
{
private:
	
	//벡터를 편리하게 사용하기위한 typedef 
	typedef vector<Ghoul*>					vGhoul;
	typedef vector<Ghoul*>::iterator		viGhoul;
	typedef vector<Knight*>					vKnight;
	typedef vector<Knight*>::iterator		viKnight;
	typedef vector<Mage*>					vMage;
	typedef vector<Mage*>::iterator			viMage;
	typedef vector<Rogue*>					vRogue;
	typedef vector<Rogue*>::iterator		viRogue;
	typedef vector<Scarecrow*>				vScarecrow;
	typedef vector<Scarecrow*>::iterator	viScarecrow;

	//보스 클래스 소환
	woodBoss*		 _woodBoss;
	iceBoss*		 _iceBoss;
	fireBoss*		 _fireBoss;

	POINTFLOAT		 _woodposition, _iceposition, _fireposition;		//보스 좌표설정
	itemManager*	 _itemManager;										//아이템 매니저

	//벡터 설정
	vGhoul			 _vGhoul;
	viGhoul			 _viGhoul;
	vKnight			 _vKnight;
	viKnight		 _viKnight;
	vMage			 _vMage;
	viMage			 _viMage;
	vRogue			 _vRogue;
	viRogue			 _viRogue;
	vScarecrow		 _vScarecrow;
	viScarecrow		 _viScarecrow;

	stage*			_stage;		//스테이어 정보
	projectileManager* _PM;		//스킬 정보
	
	//플레이어 위치와 인덱스번호를 받아옴
	POINTFLOAT		_playerPoint;
	int				_playerIndex;
	
	//아이템이 드랍됬는지 확인하는 변수
	bool _alreadyDrop[3];

	//보스전이 시작됬음을 알리는 변수
	bool fireBossStart;
	bool iceBossStart;
	bool woodBossStart;
	//세이브 됬는지 확인 
	bool saveNow;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//보스 
	void setBoss();			
	void BossUpdate();
	void BossRender();
	void BossDie();
	bool getSaveNow() { return saveNow; }

	//몬스터 
	void settingMonster(int key);
	void monsterUpdate();
	void monsterRender();
	void monsterRemove();

	//링크
	void setItemManagerLink	(itemManager* itemManager)	{ _itemManager = itemManager; }
	void setStage			(stage* stage)				{ _stage = stage; }
	void setPlayerPoint		(POINTFLOAT point)			{ _playerPoint = point; }
	void setPlayerIndex		(int index)					{ _playerIndex = index; }
	void setBossDead		(bool fire, bool ice, bool wood)				{ _fireBoss->setFireBossDie(fire); _iceBoss->setIceBossDie(ice); _woodBoss->setWoodBossDie(wood); }
	void setAlreadyDrop		(bool already0, bool already1, bool already2)	{ _alreadyDrop[0] = already0; _alreadyDrop[1] = already1; _alreadyDrop[2] = already2; }
	void setProjectileManagerAddressLink(projectileManager * PM)			{ _PM = PM; }

	//접근자 
	fireBoss*	getFireBoss()		{ return _fireBoss; };
	iceBoss*	getIceBoss()		{ return _iceBoss; };
	woodBoss*	getWoodBoss()		{ return _woodBoss; };
	vGhoul		getVGhoul()			{ return _vGhoul; }
	viGhoul		getViGhoul()		{ return _viGhoul; }
	vKnight		getVKnight()		{ return _vKnight; }
	viKnight	getViKnight()		{ return _viKnight; }
	vMage		getVMage()			{ return _vMage; }
	viMage		getViMage()			{ return _viMage; }
	vRogue		getVRogue()			{ return _vRogue; }
	viRogue		getViRogue()		{ return _viRogue; }
	vScarecrow	getVScarecrow()		{ return _vScarecrow; }
	viScarecrow	getViScarecrow()	{ return _viScarecrow; }
	
};