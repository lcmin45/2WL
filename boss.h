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

	//������ ������ �⺻���� �Ӽ�/
	RECT _bossRc;
	image* _bossImg;

	//�÷��̾� ��ġ�� �˱� ���� Ŭ���� ����
	player _player;

	//���� �����ִ� ����
	bool _woodBossDie;
	bool _iceBossDie;
	bool _fireBossDie;

	//���� �̵� �ð� ����
	int _bossMoveCount;

	//���� ��ȭâ ����
	bool _woodDialogue;
	bool _iceDialogue;
	bool _fireDialogue;

	//���� ������ ����
	bool _woodMove;
	bool _iceMove;
	bool _fireMove;

	//������ ���� ����
	int _frameCount;
	int _woodindex;
	int _iceindex;
	int _fireindex;

	//���� ü�� ��������
	bossProgressBar* _woodHpBar;
	bossProgressBar* _iceHpBar;
	bossProgressBar* _fireHpBar;
	float _woodCurrentHP, _woodMaxHP;	//����ü�� / �ִ�ü��
	float _iceCurrentHP, _iceMaxHP;	//����ü�� / �ִ�ü��
	float _fireCurrentHP, _fireMaxHP;	//����ü�� / �ִ�ü��

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
	///////////////�ʱ� �̹����� ��ǥ����
	virtual HRESULT setting(const char* imageName, POINTFLOAT position);
	virtual void release();
	virtual void render();
	virtual void update();

	void setFireBossHit(float att) { _fireCurrentHP -= att; }
	void setIceBossHit(float att) { _iceCurrentHP -= att; }
	void setWoodBossHit(float att) { _woodCurrentHP -= att; }

	//������
	POINTFLOAT getPosition() { return { _x, _y }; }
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
	void setFireBossDie(bool die) { _fireBossDie = die; }
	void setIceBossDie(bool die) { _iceBossDie = die; }
	void setWoodBossDie(bool die) { _woodBossDie = die; }
	bool getWoodDialogue() {return _woodDialogue; }
	bool getIceDialogue() { return _iceDialogue; }
	bool getFireDialogue(){return _fireDialogue; }
};