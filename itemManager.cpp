#include "stdafx.h"
#include "itemManager.h"
#include "inventory.h"
#include "player.h"

itemManager::itemManager() {}
itemManager::~itemManager() {}

HRESULT itemManager::init()
{
	//아이템 초기값 설정
	EFFECT effect[10][2] = { { { HP, 10 }, { NONE, 0 } }, { { DAMAGE, 10 }, { NONE, 0 } }, { { SPEED, 10 }, { NONE, 0 } }, { { CRITICAL, 10 }, { NONE, 0 } }, { { CRITICAL, 50 }, { HP, -50 } }, { { HP, 5 }, { DAMAGE, 5 } }, { { DAMAGE, 5 }, { CRITICAL, 5 } }, { { SPEED, 5 }, { CRITICAL, 5 } }, { { DAMAGE, 5 }, { SPEED, 5 } }, { { SPEED, 50 },{ DAMAGE, -50 } } };
	char imageName[128];
	const char* name[10] = { "사우스페이스 패딩", "돌안 검", "악센트의 발톱", "아담의 나뭇잎", "드레의 반지", "나락의 성벽", "양샘의 피부", "탈골의 등뼈", "도르마무의 눈", "경일의 땀" };
	const char* info[10] = { "남쪽 장인 난쟁이 장인 곰털 패딩", "유명한 대장장이 돌안이 만든 검", "죽음의 음유시인 악센트의 발톱", "최후의 인간 아담의 그 곳 가리개", "공포의 귀 의사 닥터 드레의 반지", "폐허 도시 나락의 성벽 조각", "대도시 경일을 망친 대악마 양샘의 피부", "비운의 칼슘왕 탈골의 등뼈", "제 3우주의 기원 도르마무의 눈", "대도시 경일의 천년 지하수 결정" };
	int price[10] = { 100, 100, 100, 100, 250, 125, 125, 125, 125, 250 };
	//코인 아이템용 설정
	int coinAni[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("coin", "coinFrame", coinAni, 6, 5, true);

	for (int i = 0; i < 10; i++) //아이템 초기화
	{
		sprintf_s(imageName, "item%d", i);
		item* tempItem = new item;
		tempItem->init({ 0, 0 }, NOWHERE, effect[i][0], effect[i][1], imageName, name[i], info[i], price[i]);
		_vItem.push_back(tempItem);
	}

	_inventory = new inventory;
	_inventory->init();

	_store = new store;
	_store->init();

	return S_OK;
}

void itemManager::release()
{
	_vItem.clear(); //아이템 백터 클리어
}

void itemManager::update()
{
	//인벤토리에 주인공 좌표 전송
	_inventory->update(_player->getPosition());

	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		if ((*_viItem)->getEffect()[0].type == COIN) (*_viItem)->coinMove(getAngle((*_viItem)->getPosition().x, (*_viItem)->getPosition().y, _player->getPosition().x, _player->getPosition().y));
	}
}

void itemManager::render()
{
	_inventory->render();
	_store->render();

	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}
}

void itemManager::setStoreItem()
{
	for (int i = 0; i < 4;) //랜덤으로 상점에 아이템 4개 배치
	{
		int rand = RND->getInt(10);
		if (_vItem[rand]->getStatus() == IN_STORE) continue;
		else addItemToStore(_vItem[rand]); i++;
	}
}

//인벤토리에 아이템 추가 이외의 아이템 값 설정 함수
void itemManager::setItem(item* item, STATUS status, POINTFLOAT position)
{
	item->setPosition(position); item->setStatus(status);
}

//죽은 보스에게 호출받아 아이템을 드랍할 함수
void itemManager::dropItem(POINTFLOAT position)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem) if ((*_viItem)->getStatus() == NOWHERE) break;

	if (_viItem == _vItem.end()) return;

	while (1)
	{
		int rendIndex = RND->getInt(10);
		if (_vItem[rendIndex]->getStatus() == NOWHERE)
		{
			_vItem[rendIndex]->setPosition(position);
			_vItem[rendIndex]->setStatus(ON_FIELD);
			break;
		}
	}
}

//인벤토리에 아이템 추가 함수
bool itemManager::addItemToInventory(item * item)
{
	if (_inventory->addItem(item)) { item->setPosition({ -25, -25 }); item->setStatus(IN_INVENTORY); return true; }

	return false;
}

//상점에 아이템 추가 함수
bool itemManager::addItemToStore(item * item)
{
	if (_store->addItem(item)) { item->setStatus(IN_STORE); return true; }

	return false;
}

//상점에서 아이템 판매 함수
bool itemManager::sellItem(item * item)
{
	if (_player->getCoin() >= item->getPrice()) { if (addItemToInventory(item)) { _store->sellItem(item); return true; } }

	return false;
}

//코인 드랍 함수
void itemManager::dropCoin(POINTFLOAT position)
{
	int randCount = RND->getInt(4) + 1;

	for (int i = 0; i < randCount; i++)
	{
		POINTFLOAT randPosition = { position.x + (RND->getFloat(50.0f) - 25.0f), position.y + (RND->getFloat(50.0f) - 25.0f) };
		EFFECT effect[2] = { { COIN, RND->getInt(10) + 5 }, { NONE, 0 } };
		const char* name = "마법사의 인장";
		const char* info = "금으로 된 마법사의 인장이다";

		item* tempItem = new item;
		tempItem->init(randPosition, ON_FIELD, effect[0], effect[1], "coin", name, info, 0);
		_vItem.push_back(tempItem);
	}
}

//코인 회수 함수
void itemManager::takeCoin(int index)
{
	_vItem.erase(_vItem.begin() + index);
}