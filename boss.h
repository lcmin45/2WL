#pragma once
#include "gameNode.h"
#include "skill.h"
#include "progressBar.h"

enum WOODDIRECTION
{
	WOODDIRECTION_SOHWAN,
	WOODDIRECTION_SHOW,
	WOODDITECTION_JUMP,
	WOODDITECTION_RIGHT,
	WOODDITECTION_LEFT,
	WOODDITECTION_SKILL,
	WOODDITECTION_SKILL2_RIGHT,
	WOODDITECTION_SKILL2_LEFT,
	WOODDITECTION_CRASH_RIGHT,
	WOODDITECTION_CRASH_LEFT,
	WOODDITECTION_DIE
};

enum ICEDIRECTION
{
	ICEDIRECTION_SOHWAN,
	ICEDIRECTION_SHOW,
	ICEDIRECTION_RIGHT,
	ICEDIRECTION_LEFT,
	ICEDIRECTION_REAR,
	ICEDIRECTION_FRONT,
	ICEDIRECTION_SKILL,
	ICEDIRECTION_SKILL2,
	ICEDIRECTION_CRASH,
	ICEDIRECTION_DIE
};

enum FIREDIRECTION
{
	FIREDIRECTION_SHOW,
	FIREDIRECTION_RIGHT,
	FIREDIRECTION_LEFT,
	FIREDIRECTION_SKILL_RIGHT,
	FIREDIRECTION_SKILL_LEFT,
	FIREDIRECTION_CRASH,
	FIREDIRECTION_DIE
};

class boss : public gameNode
{
private:
	//보스가 가지는 기본적인 속성//렉트,이미지,좌표
	RECT _bossRc;
	image* _bossImg;
	POINTFLOAT _position;

	//각각의 보스 모션
	WOODDIRECTION _woodDirection;
	ICEDIRECTION _iceDirection;
	FIREDIRECTION _fireDirection;
	
	//각각의  보스죽음 확인 변수
	bool _woodBossDie;
	bool _iceBossDie;
	bool _fireBossDie;

	//보스의 스킬 공격 시간 변수
	int _bossSkillCount;

	//프래임 관련 변수
	int _frameCount;
	int _index;

	//보스 체력 게이지바
	progressBar* _hpBar;		
	float _currentHP, _maxHP;	//현재체력 / 최대체력

public:
	boss();
	~boss();

	virtual HRESULT init();
	///////////////초기 이미지와 좌표설정
	virtual HRESULT setting(const char* imageName, POINT position);
	virtual void release();
	virtual void render();
	virtual void update();

	///////////보스 움직임 함수
	virtual void woodMove();
	virtual void iceMove();
	virtual void fireMove();

	//////////보스 스킬 함수
	virtual void woodSkill();
	virtual void iceSkill();
	virtual void fireSkill();

	//접근자
	inline RECT getbossRect() { return _bossRc; }
	inline void setbossimage(image* bossimg) { _bossImg = bossimg; }

	inline image * getbossimage() { return  _bossImg; }

};