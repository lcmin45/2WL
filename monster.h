#pragma once
#include "gameNode.h"
#include "stage.h"
#include "tile.h"
#include "Astar.h"

enum MONSTERDIRECTION
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


enum MONDIRECTION	{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
enum MONSTERFORM	{ CARD, SUMMOM, BATTLE };

class monster : public gameNode
{
protected:


	//전체 타일을 담을 벡터
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//갈 수 있는 길을 담은 벡터
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//가장 빠른 길이 담기는 벡터
	vector<tile*>			_vClosedList;
	vector<tile*>::iterator _viClosedList;

	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;

	stage* _stage;
	Astar* _Astar;


	MONSTERDIRECTION _Direction;		//몬스터 상태정의
	animation* _Motion;					//몬스터 에니메이션
	MONDIRECTION _dir;					//몬스터가 움직일 방향
	MONSTERFORM _form;					//몬스터 상태 (카드,소환중,소환완료)
	image * _image;						//이미지
	POINTFLOAT _position;				//중심 위치
	POINTFLOAT _bottomPosition;			//바닥 위치
	POINTFLOAT _playerPosition;			//몬스터가 알고 있는 플레이어 위치
	POINTFLOAT _endPosition;			//몬스터가 움직일 타일의 위치
	RECT _rc;							//타격판정 위한 렉트
	RECT _Zrc;							//Z오더 위한 바닥렉트
	float _monsterHP;					//체력
	float _attackRange;					//공격 범위
	float _angle;						//플레이어와의 각도
	float _distance;					//플레이어와의 거리
	float _speed;						//움직일 속도
	int _timecnt;						//플레이어의 위치를 받아올 시간
	int _playerIndex;					//몬스터가 알고있는 플레이어 인덱스
	int _monsterIndex;					//몬스터가 가지고 있는 인덱스 (플레이어와 같으면 소환)
	char _motionName1[128];				//콜백함수를 위한 모션 네임
	char _motionName2[128];				//콜백함수를 위한 모션 네임
	char _motionName3[128];				//콜백함수를 위한 모션 네임
	char _motionName4[128];				//콜백함수를 위한 모션 네임
	char _motionName5[128];				//콜백함수를 위한 모션 네임
	char str[256];						//이미지의 키값


public:
	monster();
	~monster();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	inline void HitHP(float att) { _monsterHP -= att; }
	inline float getHP() { return _monsterHP; }

	void setImage(image* img) { _image = img; }
	void setForm(MONSTERFORM form) { _form = form; }

	POINTFLOAT getPosition() { return _position; }
	POINTFLOAT getBottomPosition() { return _bottomPosition; }



	//상태에 대한 접근자, 설정자

	MONSTERDIRECTION getMonsterDirection() { return _Direction; }
	void setMonsterDirection(MONSTERDIRECTION direction) { _Direction = direction; }

	animation* getMotion() { return _Motion; }
	void setMotion(animation* ani) { _Motion = ani; }


	void setStageLink(stage* sta)	{_Astar->setStageMemoryAdressLink(sta);}
	void setPlayerIndex(int index)	{_playerIndex = index; }
	void setPlayerPoint(POINTFLOAT playerPosition) 
	{ 
		_playerPosition = playerPosition;
		_Astar->setPlayerPositionLink(playerPosition);
	}
	
};