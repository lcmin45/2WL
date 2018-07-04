#include "stdafx.h"
#include "itemManager.h"
#include "inventory.h"
#include "player.h"

itemManager::itemManager() {}
itemManager::~itemManager() {}

HRESULT itemManager::init()
{
	//������ �ʱⰪ ����
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

	_inventory = new inventory;
	_inventory->init();

	//�ӽ�
	setItem(_vItem[0], ON_FIELD, { 500, 500 });
	setItem(_vItem[4], ON_FIELD, { 600, 600 });
	setItem(_vItem[7], ON_FIELD, { 500, 600 });
	setItem(_vItem[9], ON_FIELD, { 500, 700 });

	return S_OK;
}

void itemManager::release() {}

void itemManager::update()
{
	//�κ��丮�� ���ΰ� ��ǥ ����
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

//�κ��丮�� ������ �߰� �̿��� ������ �� ���� �Լ�
void itemManager::setItem(item* item, STATUS status, POINTFLOAT position)
{
	item->setPosition(position); item->setStatus(status);
}

//�κ��丮�� ������ �߰� �Լ�
bool itemManager::addItem(item * item)
{
	if (_inventory->addItem(item)) { item->setPosition({ -25, -25 }); item->setStatus(IN_INVENTORY); return true; }

	return false;
}