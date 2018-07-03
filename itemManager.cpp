#include "stdafx.h"
#include "itemManager.h"
#include "inventory.h"

itemManager::itemManager() {}
itemManager::~itemManager() {}

HRESULT itemManager::init()
{
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

	return S_OK;
}

void itemManager::release() {}

void itemManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		int rand = RND->getInt(10);
		_vItem[rand]->setStatus(IN_INVENTORY);
		_inventory->addItem(_vItem[rand]);
	}
}

void itemManager::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		(*_viItem)->render();
	}
}

void itemManager::setPosition(const char * name, POINTFLOAT position)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		if (strcmp(name, (*_viItem)->getName())) { (*_viItem)->setPosition(position); break; }
	}
}

void itemManager::setStatus(const char * name, STATUS status)
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); _viItem++)
	{
		if (strcmp(name, (*_viItem)->getName())) { (*_viItem)->setStatus(status); break; }
	}
}