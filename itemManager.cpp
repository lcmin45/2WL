#include "stdafx.h"
#include "itemManager.h"
#include "inventory.h"

itemManager::itemManager() {}
itemManager::~itemManager() {}

HRESULT itemManager::init()
{
	EFFECT effect[10][2] = { { { HP, 10 }, { NONE, 0 } }, { { DAMAGE, 10 }, { NONE, 0 } }, { { SPEED, 10 }, { NONE, 0 } }, { { CRITICAL, 10 }, { NONE, 0 } }, { { CRITICAL, 50 }, { HP, -50 } }, { { HP, 5 }, { DAMAGE, 5 } }, { { DAMAGE, 5 }, { CRITICAL, 5 } }, { { SPEED, 5 }, { CRITICAL, 5 } }, { { DAMAGE, 5 }, { SPEED, 5 } }, { { SPEED, 50 },{ DAMAGE, -50 } } };
	char imageName[128];
	const char* name[10] = { "��콺���̽� �е�", "���� ��", "�Ǽ�Ʈ�� ����", "�ƴ��� ������", "�巹�� ����", "������ ����", "����� �Ǻ�", "Ż���� ���", "���������� ��", "������ ��" };
	const char* info[10] = { "���� ������ ������ �е�", "�������� ������ ���� ��", "�������� �Ǽ�Ʈ�� ����", "�ƴ��� �� �� ������", "���� �巹�� ����", "���� ������ ���� ����", "��Ǹ� ����� �Ǻ�", "������ Ż���� ���", "������ ��� ���������� ��", "���� ������ ���ϼ� ����" };

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