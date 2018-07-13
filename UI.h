#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "option.h"

class player;
class projectileManager;

class UI : public gameNode
{
private:
	image * _image; //�̹���
	player* _player; //���ΰ�
	projectileManager* _projectileManager; //�߻�ü ����
	progressBar* _progressBar; //���α׷��� ��
	option* _option; //�ɼ�
	RECT _optionRC; //�ɼ� ��Ʈ
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