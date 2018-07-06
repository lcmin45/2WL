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


	//��ü Ÿ���� ���� ����
	vector<tile*>			_vTotalList;
	vector<tile*>::iterator _viTotalList;

	//�� �� �ִ� ���� ���� ����
	vector<tile*>			_vOpenList;
	vector<tile*>::iterator _viOpenList;

	//���� ���� ���� ���� ����
	vector<tile*>			_vClosedList;
	vector<tile*>::iterator _viClosedList;

	tile* _startTile;
	tile* _endTile;
	tile* _currentTile;

	stage* _stage;
	Astar* _Astar;


	MONSTERDIRECTION _Direction;		//���� ��������
	animation* _Motion;					//���� ���ϸ��̼�
	MONDIRECTION _dir;					//���Ͱ� ������ ����
	MONSTERFORM _form;					//���� ���� (ī��,��ȯ��,��ȯ�Ϸ�)
	image * _image;						//�̹���
	POINTFLOAT _position;				//�߽� ��ġ
	POINTFLOAT _bottomPosition;			//�ٴ� ��ġ
	POINTFLOAT _playerPosition;			//���Ͱ� �˰� �ִ� �÷��̾� ��ġ
	POINTFLOAT _endPosition;			//���Ͱ� ������ Ÿ���� ��ġ
	RECT _rc;							//Ÿ������ ���� ��Ʈ
	RECT _Zrc;							//Z���� ���� �ٴڷ�Ʈ
	float _monsterHP;					//ü��
	float _attackRange;					//���� ����
	float _angle;						//�÷��̾���� ����
	float _distance;					//�÷��̾���� �Ÿ�
	float _speed;						//������ �ӵ�
	int _timecnt;						//�÷��̾��� ��ġ�� �޾ƿ� �ð�
	int _playerIndex;					//���Ͱ� �˰��ִ� �÷��̾� �ε���
	int _monsterIndex;					//���Ͱ� ������ �ִ� �ε��� (�÷��̾�� ������ ��ȯ)
	char _motionName1[128];				//�ݹ��Լ��� ���� ��� ����
	char _motionName2[128];				//�ݹ��Լ��� ���� ��� ����
	char _motionName3[128];				//�ݹ��Լ��� ���� ��� ����
	char _motionName4[128];				//�ݹ��Լ��� ���� ��� ����
	char _motionName5[128];				//�ݹ��Լ��� ���� ��� ����
	char str[256];						//�̹����� Ű��


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



	//���¿� ���� ������, ������

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