#pragma once
#include "gameNode.h"
#include "mapToolNode.h"

class player;

class stage : public gameNode
{
private:	
	image * _stage1;									//프레임 저하를 막기위한 만든 스테이지의 이미지
	image * _image;										//F키 버튼

	tagMapToolTile		_tile[MAXTILEX * MAXTILEY];		//타일맵 이미지
	int		_stage;										//스테이지 체크를 위한 변수
	player* _player;									//플레이어 정보
				
	image * _potal[6];									//포탈
	RECT _potalRc[6];									//포탈 충돌판정 위한 렉트
	int _potalCount;									//포탈 프레임 이미지 위한 카운트
	int _potalIndex;									//포탈 X 이미지 인덱스

public:
	stage();
	~stage();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void stageLoad(int stage);							//어떤 스테이지를 불러올까
	void warp();										//포탈 이동

	tagMapToolTile* getTileinfo() { return _tile; }
	void setPlayerMemoryAdressLink(player* player) { _player = player; }
};