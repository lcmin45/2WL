#pragma once
#include "gameNode.h"

enum SET_TYPE { NORMAL, ACTIVE_SKILL };

struct tagSkillSet
{
	string name; //스킬 이름
	string info; //스킬 정보
	SET_TYPE type; //스킬 타입
};

class skillSet : public gameNode
{
private:
	image * _image; //이미지
	tagSkillSet _skillSet[7]; //스킬 7개
	RECT _skillSetRect; //스킬 창 렉트
	RECT _sampleRect[7]; //각 스킬 이미지 렉트
	int _selectedSkillIndex; //선택한 스킬 인덱스
	bool _isOpen; //열렸는지 유무
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