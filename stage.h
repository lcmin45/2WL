#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class player;

class stage : public gameNode
{
private:	
	image * _stage1;									//������ ���ϸ� �������� ���� ���������� �̹���
	image * _image;										//FŰ ��ư

	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];		//Ÿ�ϸ� �̹���
	int		_stage;										//�������� üũ�� ���� ����
	player* _player;									//�÷��̾� ����
				
	image * _potal[6];									//��Ż
	RECT _potalRc[6];									//��Ż �浹���� ���� ��Ʈ
	int _potalCount;									//��Ż ������ �̹��� ���� ī��Ʈ
	int _potalIndex;									//��Ż X �̹��� �ε���

public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void stageLoad(int stage);							//� ���������� �ҷ��ñ�
	void warp();										//��Ż �̵�

	tagMapToolTile* getTileinfo() { return _tile; }
	void setPlayerMemoryAdressLink(player* player) { _player = player; }
};