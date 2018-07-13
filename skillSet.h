#pragma once
#include "gameNode.h"

enum SET_TYPE { NORMAL, ACTIVE_SKILL };

struct tagSkillSet
{
	string name;
	string info;
	SET_TYPE type;
};

class skillSet : public gameNode
{
private:
	image * _image;						//스킬 아이콘 이미지
	tagSkillSet _skillSet[7];			
	RECT _skillSetRect;
	RECT _sampleRect[7];
	int _selectedSkillIndex;
	bool _isOpen;
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