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
	const char* info[10] = { "남쪽 난쟁이 장인의 패딩", "대장장이 돌안이 만든 검", "음유시인 악센트의 발톱", "아담의 그 곳 가리개", "닥터 드레의 반지", "도시 나락의 성벽 조각", "대악마 양샘의 피부", "엘프왕 탈골의 등뼈", "우주의 기원 도르마무의 눈", "수도 경일의 지하수 결정" };

	for (int i = 0; i < 10; i++)
	{
		sprintf_s(imageName, "item%d", i);
		item* tempItem = new item;
		tempItem->init({ 0, 0 }, NOWHERE, effect[i][0], effect[i][1], imageName, name[i], info[i]);
		_vItem.push_back(tempItem);
	}

	_inventory = new inventory;
	_inventory->init();

	//임시
	setItem(_vItem[0], ON_FIELD, { 500, 500 });
	setItem(_vItem[4], ON_FIELD, { 600, 600 });
	setItem(_vItem[7], ON_FIELD, { 500, 600 });
	setItem(_vItem[9], ON_FIELD, { 500, 700 });

	return S_OK;
}

void itemManager::release() {}

void itemManager::update()
{
	//인벤토리에 주인공 좌표 전송
	_inventory->update(_player->getPosition());
}

void itemManager::render()
{
	_inventory->render();

	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}
}

//인벤토리에 아이템 추가 이외의 아이템 값 설정 함수
void itemManager::setItem(item* item, STATUS status, POINTFLOAT position)
{
	item->setPosition(position); item->setStatus(status);
}

//인벤토리에 아이템 추가 함수
bool itemManager::addItem(item * item)
{
	if (_inventory->addItem(item)) { item->setPosition({ -25, -25 }); item->setStatus(IN_INVENTORY); return true; }

	return false;
}