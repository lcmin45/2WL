#pragma once
#include "gameNode.h"
#include "stage.h"
#include "tile.h"
#include "Astar.h"
#include "projectileManager.h"

enum MONSTERDIRECTION		//몬스터 방향 상태정의
{
	RIGHT_STAND,
	LEFT_STAND,
	RIGHT_MOVE,
	LEFT_MOVE,
	RIGHT_ATTACK,
	LEFT_ATTACK,
	RIGHT_HIT,
	LEFT_HIT,
	RIGHT_DIE,
	LEFT_DIE
};


enum MONDIRECTION	{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };	//몬스터 방향
enum MONSTERFORM	{ CARD, SUMMOM, BATTLE, DIE };				//몬스터 상태

class monster : public gameNode
{
protected:


	Astar*					_Astar;						//움직일 A* 클래스
	projectileManager*		_PM;						//몬스터가 사용할 스킬 클래스
	MONSTERDIRECTION		_Direction;					//몬스터 상태정의
	animation*				_Motion;					//몬스터 에니메이션
	MONDIRECTION			_dir;						//몬스터가 움직일 방향
	MONSTERFORM				_form;						//몬스터 상태 (카드,소환중,소환완료)
	image *					_image;						//이미지
	POINTFLOAT				_position;					//중심 위치
	POINTFLOAT				_bottomPosition;			//바닥 위치
	POINTFLOAT				_playerPosition;			//몬스터가 알고 있는 플레이어 위치
	POINTFLOAT				_endPosition;				//몬스터가 움직일 타일의 위치
	RECT					_rc;						//타격판정 위한 렉트
	RECT					_Zrc;						//Z오더 위한 바닥렉트
	float					_monsterHP;					//체력
	float					_attackRange;				//공격 범위
	float					_angle;						//플레이어와의 각도
	float					_distance;					//플레이어와의 거리
	float					_speed;						//움직일 속도
	int						_timecnt;					//플레이어의 위치를 받아올 시간
	int						_playerIndex;				//몬스터가 알고있는 플레이어 인덱스
	int						_monsterIndex;				//몬스터가 가지고 있는 인덱스 (플레이어와 같으면 소환)
	int						_keyIndex;					//몬스터 콜백함수를 위한 키값
	int						_attackCount;				//공격 쿨타임
	bool					_attackReady;				//공격 준비했나?
	bool					_isDie;						//삭제 될 준비 되었나
	char					_motionName1[128];			//콜백함수를 위한 모션 네임
	char					_motionName2[128];			//콜백함수를 위한 모션 네임
	char					_motionName3[128];			//콜백함수를 위한 모션 네임
	char					_motionName4[128];			//콜백함수를 위한 모션 네임
	char					_motionName5[128];			//콜백함수를 위한 모션 네임
	char					_motionName6[128];			//콜백함수를 위한 모션 네임
	char					_motionName7[128];			//콜백함수를 위한 모션 네임
	char					str[256];					//이미지의 키값
	char					str2[256];					//몬스터 공격이미지의 키값


public:
	monster();
	~monster();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	


	//몬스터 맞았을때 사용할 함수
	inline void HitHP(float att, float angle) 
	{ _monsterHP -= att; _bottomPosition.x += cos(angle) * 1; _bottomPosition.y += -sin(angle) * 1;}


	//============== 접근자 설정자 ==========
	inline bool getIsDie()							{ return _isDie; }
	inline float getHP()							{ return _monsterHP; }
	inline int getMonsterIndex()					{ return _monsterIndex; }
	inline POINTFLOAT getPosition()					{ return _position; }
	inline POINTFLOAT getBottomPosition()			{ return _bottomPosition; }
	inline RECT getMonsterRC()						{ return _rc; }
	inline MONSTERFORM getForm()					{ return _form; }
	inline MONSTERDIRECTION getMonsterDirection()	{ return _Direction; }
	inline animation* getMotion()					{ return _Motion; }

	inline void setForm(MONSTERFORM form)						{ _form = form; }
	inline void setImage(image* img)							{ _image = img; }
	inline void setMotion(animation* ani)						{ _Motion = ani; }
	inline void setSkillLink(projectileManager* PM)				{ _PM = PM; }
	inline void setStageLink(stage* sta)						{_Astar->setStageMemoryAdressLink(sta);}
	inline void setPlayerIndex(int index)						{_playerIndex = index; }
	inline void setMonsterDirection(MONSTERDIRECTION direction) { _Direction = direction; }
	inline void setPlayerPoint(POINTFLOAT playerPosition) 
	{ 
		_playerPosition = playerPosition;
		_Astar->setPlayerPositionLink(playerPosition);
	}
	
};