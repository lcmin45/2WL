#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "option.h"

class player;
class projectileManager;

class UI : public gameNode
{
private:
	image * _image;								//UI 이미지
	player* _player;							//플레이어 수치확인을 위한 객체
	projectileManager* _projectileManager;		//스킬 쿨타임 확인을 위한 객체
	progressBar* _progressBar;					//보스 체력바
	option* _option;							//사운드 옵션
	RECT _optionRC;								//옵션 충돌판정을 위한 렉트 
public:
	UI();
	~UI();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPlayerAddressLink(player* getLink) { _player = getLink; }
	void setProjectileManagerAddressLink(projectileManager* getLink) { _projectileManager = getLink; }
};