#pragma once
#include "gameNode.h"
#include "stage.h"
#include "tile.h"
#include "Astar.h"
#include "projectileManager.h"

enum MONSTERDIRECTION		//���� ���� ��������
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


enum MONDIRECTION	{ DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };	//���� ����
enum MONSTERFORM	{ CARD, SUMMOM, BATTLE, DIE };				//���� ����

class monster : public gameNode
{
protected:


	Astar*					_Astar;						//������ A* Ŭ����
	projectileManager*		_PM;						//���Ͱ� ����� ��ų Ŭ����
	MONSTERDIRECTION		_Direction;					//���� ��������
	animation*				_Motion;					//���� ���ϸ��̼�
	MONDIRECTION			_dir;						//���Ͱ� ������ ����
	MONSTERFORM				_form;						//���� ���� (ī��,��ȯ��,��ȯ�Ϸ�)
	image *					_image;						//�̹���
	POINTFLOAT				_position;					//�߽� ��ġ
	POINTFLOAT				_bottomPosition;			//�ٴ� ��ġ
	POINTFLOAT				_playerPosition;			//���Ͱ� �˰� �ִ� �÷��̾� ��ġ
	POINTFLOAT				_endPosition;				//���Ͱ� ������ Ÿ���� ��ġ
	RECT					_rc;						//Ÿ������ ���� ��Ʈ
	RECT					_Zrc;						//Z���� ���� �ٴڷ�Ʈ
	float					_monsterHP;					//ü��
	float					_attackRange;				//���� ����
	float					_angle;						//�÷��̾���� ����
	float					_distance;					//�÷��̾���� �Ÿ�
	float					_speed;						//������ �ӵ�
	int						_timecnt;					//�÷��̾��� ��ġ�� �޾ƿ� �ð�
	int						_playerIndex;				//���Ͱ� �˰��ִ� �÷��̾� �ε���
	int						_monsterIndex;				//���Ͱ� ������ �ִ� �ε��� (�÷��̾�� ������ ��ȯ)
	int						_keyIndex;					//���� �ݹ��Լ��� ���� Ű��
	int						_attackCount;				//���� ��Ÿ��
	bool					_attackReady;				//���� �غ��߳�?
	bool					_isDie;						//���� �� �غ� �Ǿ���
	char					_motionName1[128];			//�ݹ��Լ��� ���� ��� ����
	char					_motionName2[128];			//�ݹ��Լ��� ���� ��� ����
	char					_motionName3[128];			//�ݹ��Լ��� ���� ��� ����
	char					_motionName4[128];			//�ݹ��Լ��� ���� ��� ����
	char					_motionName5[128];			//�ݹ��Լ��� ���� ��� ����
	char					_motionName6[128];			//�ݹ��Լ��� ���� ��� ����
	char					_motionName7[128];			//�ݹ��Լ��� ���� ��� ����
	char					str[256];					//�̹����� Ű��
	char					str2[256];					//���� �����̹����� Ű��


public:
	monster();
	~monster();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	


	//���� �¾����� ����� �Լ�
	inline void HitHP(float att, float angle) 
	{ _monsterHP -= att; _bottomPosition.x += cos(angle) * 1; _bottomPosition.y += -sin(angle) * 1;}


	//============== ������ ������ ==========
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