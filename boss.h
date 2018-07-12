#pragma once
#include "gameNode.h"
#include "skill.h"
#include "bossProgressBar.h"
#include "player.h"
#include "projectileManager.h"

class player;

class boss : public gameNode
{
protected:

	//보스가 가지는 기본적인 속성/
	RECT _bossRc;
	image* _bossImg;

	//플레이어 위치를 알기 위한 클래스 선언
	player _player;

	//보스 없애주는 변수
	bool _woodBossDie;
	bool _iceBossDie;
	bool _fireBossDie;

	//보스 이동 시간 변수
	int _bossMoveCount;

	//보스 대화창 변수
	bool _woodDialogue;
	bool _iceDialogue;
	bool _fireDialogue;

	//보스 움직임 변수
	bool _woodMove;
	bool _iceMove;
	bool _fireMove;

	//프래임 관련 변수
	int _frameCount;
	int _woodindex;
	int _iceindex;
	int _fireindex;

	//보스 체력 게이지바
	bossProgressBar* _woodHpBar;
	bossProgressBar* _iceHpBar;
	bossProgressBar* _fireHpBar;
	float _woodCurrentHP, _woodMaxHP;	//현재체력 / 최대체력
	float _iceCurrentHP, _iceMaxHP;	//현재체력 / 최대체력
	float _fireCurrentHP, _fireMaxHP;	//현재체력 / 최대체력

	float _x, _y;

	float _angle;
	float _speed;
	float _distance;

	float _jump;

	POINTFLOAT _playerPosition;
	projectileManager* _ptM;
	bool _skill;

public:
	boss();
	~boss();

	virtual HRESULT init();
	///////////////초기 이미지와 좌표설정
	virtual HRESULT setting(const char* imageName, POINTFLOAT position);
	virtual void release();
	virtual void render();
	virtual void update();

	void setFireBossHit(float att) { _fireCurrentHP -= att; }
	void setIceBossHit(float att) { _iceCurrentHP -= att; }
	void setWoodBossHit(float att) { _woodCurrentHP -= att; }

	//접근자
	inline RECT getbossRect() { return _bossRc; }
	inline void setbossimage(image* bossimg) { _bossImg = bossimg; }
	inline image * getbossimage() { return  _bossImg; }
	void setPlayerPoint(POINTFLOAT playerPosition)
	{
		_playerPosition = playerPosition;
	}
	void setProjectileAddressLink(projectileManager* ptM) { _ptM = ptM; }
	bool getWoodBossDie() { return _woodBossDie; }
	bool getIceBossDie() { return _iceBossDie; }
	bool getFireBossDie() { return _fireBossDie; }
	bool getWoodDialogue() {return _woodDialogue; }
	bool getIceDialogue() { return _iceDialogue; }
	bool getFireDialogue(){return _fireDialogue; }
};