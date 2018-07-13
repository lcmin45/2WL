#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "option.h"

class player;
class projectileManager;

class UI : public gameNode
{
private:
	image * _image;								//UI �̹���
	player* _player;							//�÷��̾� ��ġȮ���� ���� ��ü
	projectileManager* _projectileManager;		//��ų ��Ÿ�� Ȯ���� ���� ��ü
	progressBar* _progressBar;					//���� ü�¹�
	option* _option;							//���� �ɼ�
	RECT _optionRC;								//�ɼ� �浹������ ���� ��Ʈ 
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