#pragma once
#include "gameNode.h"
#include "inventory.h"
#include "item.h"
#include "store.h"
#include <vector>

class player;

class itemManager : public gameNode
{
private:
	vector<item*> _vItem; //아이템 백터
	vector<item*>::iterator _viItem; //아이템 백터 이터레이터
	player* _player; //플레이어
	inventory* _inventory; //인벤토리
	store* _store; //상점
public:
	itemManager();
	~itemManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	
	void setStoreItem();

	vector<item*> getVItem() { return _vItem; }
	inventory* getInventory() { return _inventory; }
	void setItem(item* item, STATUS status, POINTFLOAT position);
	bool addItemToInventory(item* item);
	bool addItemToStore(item* item);
	bool sellItem(item* item);
	void dropCoin(POINTFLOAT position);
	void takeCoin(int index);
	void setPlayerAddressLink(player* getLink) { _player = getLink; }
};