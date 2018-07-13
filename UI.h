#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "option.h"

class player;
class projectileManager;

class UI : public gameNode
{
private:
	image * _image; //이미지
	player* _player; //주인공
	projectileManager* _projectileManager; //발사체 관리
	progressBar* _progressBar; //프로그래스 바
	option* _option; //옵션
	RECT _optionRC; //옵션 렉트
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