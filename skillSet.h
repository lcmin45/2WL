#pragma once
#include "gameNode.h"

enum SET_TYPE { NORMAL, ACTIVE_SKILL };

struct tagSkillSet
{
	const char* name;
	const char* info;
	SET_TYPE type;
};

class skillSet : public gameNode
{
private:
	image * _image;
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
	bool getIsOpen() { return _isOpen; }
};