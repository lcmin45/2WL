#pragma once
#include "gameNode.h"
#include "skill.h"
#include "bossProgressBar.h"
#include "player.h"

class player;

class boss : public gameNode
{
protected:

	//������ ������ �⺻���� �Ӽ�/
	RECT _bossRc;
	image* _bossImg;

	//�÷��̾� ��ġ�� �˱� ���� Ŭ���� ����
	player _player;

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

public:
	boss();
	~boss();

	virtual HRESULT init();
	///////////////�ʱ� �̹����� ��ǥ����
	virtual HRESULT setting(const char* imageName, POINTFLOAT position);
	virtual void release();
	virtual void render();
	virtual void update();

	//������
	inline RECT getbossRect() { return _bossRc; }
	inline void setbossimage(image* bossimg) { _bossImg = bossimg; }
	inline image * getbossimage() { return  _bossImg; }

};