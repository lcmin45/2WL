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
	//������ ������ �⺻���� �Ӽ�//��Ʈ,�̹���,��ǥ
	RECT _bossRc;
	image* _bossImg;
	POINTFLOAT _position;

	//������ ���� ���
	WOODDIRECTION _woodDirection;
	ICEDIRECTION _iceDirection;
	FIREDIRECTION _fireDirection;
	
	//������  �������� Ȯ�� ����
	bool _woodBossDie;
	bool _iceBossDie;
	bool _fireBossDie;

	//������ ��ų ���� �ð� ����
	int _bossSkillCount;

	//������ ���� ����
	int _frameCount;
	int _index;

	//���� ü�� ��������
	progressBar* _hpBar;		
	float _currentHP, _maxHP;	//����ü�� / �ִ�ü��

public:
	boss();
	~boss();

	virtual HRESULT init();
	///////////////�ʱ� �̹����� ��ǥ����
	virtual HRESULT setting(const char* imageName, POINT position);
	virtual void release();
	virtual void render();
	virtual void update();

	///////////���� ������ �Լ�
	virtual void woodMove();
	virtual void iceMove();
	virtual void fireMove();

	//////////���� ��ų �Լ�
	virtual void woodSkill();
	virtual void iceSkill();
	virtual void fireSkill();

	//������
	inline RECT getbossRect() { return _bossRc; }
	inline void setbossimage(image* bossimg) { _bossImg = bossimg; }

	inline image * getbossimage() { return  _bossImg; }

};