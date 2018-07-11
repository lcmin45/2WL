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

class enemyManager : public gameNode
{
private:

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




	//���� Ŭ���� ��ȯ
	woodBoss* _woodBoss;
	iceBoss* _iceBoss;
	fireBoss* _fireBoss;
	//���� ��ǥ����
	POINTFLOAT _woodposition, _iceposition, _fireposition;


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

	stage*			_stage;
	projectileManager* _PM;
	

	POINTFLOAT		_playerPoint;
	int				_playerIndex;

	bool fireBossStart;
	bool iceBossStart;
	bool woodBossStart;

public:
	enemyManager();
	~enemyManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setBoss();
	void BossUpdate();
	void BossRender();

	void settingMonster();
	void monsterUpdate();
	void monsterRender();
	void monsterRemove();

	void setStage(stage* stage) { _stage = stage; }
	void setPlayerPoint(POINTFLOAT point) { _playerPoint = point; }
	void setPlayerIndex(int index) { _playerIndex = index; }
	void setProjectileManagerAddressLink(projectileManager * PM) { _PM = PM; }



	fireBoss* getFireBoss() { return _fireBoss; };
	iceBoss* getIceBoss() { return _iceBoss; };
	woodBoss* getWoodBoss() { return _woodBoss; };


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