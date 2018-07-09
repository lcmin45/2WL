#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class inventory : public gameNode
{
private:
	vector<item*> _vItem; //아이템 백터
	image* _image; //이미지
	RECT _inventoryRect; //인벤토리 렉트
	RECT _itemRect[3]; //인벤토리 내의 아이템 3개의 렉트
	int _selectedItemIndex; //버릴 아이템 선택 인덱스
	bool _isOpen; //인벤토리가 현재 열려있는지 여부
public:
	inventory();
	~inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void update(POINTFLOAT position);
	virtual void render();

	void keyProcess(POINTFLOAT position); //키 프로세스
	bool addItem(item* item); //아이템 추가 함수
	void dumpItem(int index, POINTFLOAT position); //아이템 버리는 함수

	bool getIsOpen() { return _isOpen; }
	vector<item*> getVItem() { return _vItem; }
};