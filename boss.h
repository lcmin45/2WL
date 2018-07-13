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
	RECT _bossRc; //렉트
	image* _bossImg; //이미지

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

	//보스 좌표
	float _x, _y;

	//보스 앵글 스피드 거리
	float _angle;
	float _speed;
	float _distance;

	//점프
	float _jump;

	//플레이어 좌표
	POINTFLOAT _playerPosition;
	//스킬 연결
	projectileManager* _ptM;
	//스킬 사용 여부
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

	//보스 충돌 연결	
	void setFireBossHit(float att)					{ _fireCurrentHP -= att; }
	void setIceBossHit(float att)					{ _iceCurrentHP -= att; }
	void setWoodBossHit(float att)					{ _woodCurrentHP -= att; }

	//접근자
	POINTFLOAT getPosition()						{ return { _x, _y }; }
	inline RECT getbossRect()						{ return _bossRc; }
	inline void setbossimage(image* bossimg)		{ _bossImg = bossimg; }
	inline image * getbossimage()					{ return  _bossImg; }
	void setPlayerPoint(POINTFLOAT playerPosition)	{	_playerPosition = playerPosition;}
	void setProjectileAddressLink(projectileManager* ptM) { _ptM = ptM; }
	//보스 죽음 상태
	bool getWoodBossDie()							{ return _woodBossDie; }
	bool getIceBossDie()							{ return _iceBossDie; }
	bool getFireBossDie()							{ return _fireBossDie; }
	void setFireBossDie(bool die)					{ _fireBossDie = die; }
	void setIceBossDie(bool die)					{ _iceBossDie = die; }
	void setWoodBossDie(bool die)					{ _woodBossDie = die; }
	//보스 대화상태
	bool getWoodDialogue()							{return _woodDialogue; }
	bool getIceDialogue()							{ return _iceDialogue; }
	bool getFireDialogue()							{return _fireDialogue; }
};