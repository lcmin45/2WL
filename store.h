#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class store : public gameNode
{
private:
	POINTFLOAT _position; //상점 위치
	vector<item*> _vItem; //상점 아이템
	image* _image; //이미지
public:
	store();
	~store();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	bool addItem(item* item); //상점에 아이템 추가 함수
	void sellItem(item* item); //아이템 판매 함수
};