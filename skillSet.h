#pragma once
#include "gameNode.h"

enum SET_TYPE { NORMAL, ACTIVE_SKILL };

struct tagSkillSet
{
	string name; //��ų �̸�
	string info; //��ų ����
	SET_TYPE type; //��ų Ÿ��
};

class skillSet : public gameNode
{
private:
	image * _image; //�̹���
	tagSkillSet _skillSet[7]; //��ų 7��
	RECT _skillSetRect; //��ų â ��Ʈ
	RECT _sampleRect[7]; //�� ��ų �̹��� ��Ʈ
	int _selectedSkillIndex; //������ ��ų �ε���
	bool _isOpen; //���ȴ��� ����
public:
	skillSet();
	~skillSet();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void keyProcess();
	void changeSkillKeySet(int click, int change);
	tagSkillSet* getSettingSkill() { return _skillSet; }
	void setSettingSkill(tagSkillSet skillSet, int skillIndex) { _skillSet[skillIndex] = skillSet; }
	bool getIsOpen() { return _isOpen; }
};