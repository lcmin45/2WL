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
	const char* info[10] = { "���� ���� ������ ���� ���� �е�", "������ �������� ������ ���� ��", "������ �������� �Ǽ�Ʈ�� ����", "������ �ΰ� �ƴ��� �� �� ������", "������ �� �ǻ� ���� �巹�� ����", "���� ���� ������ ���� ����", "�뵵�� ������ ��ģ ��Ǹ� ����� �Ǻ�", "����� Į���� Ż���� ���", "�� 3������ ��� ���������� ��", "�뵵�� ������ õ�� ���ϼ� ����" };
	int price[10] = { 100, 100, 100, 100, 250, 125, 125, 125, 125, 250 };
	//���� �����ۿ� ����
	int coinAni[] = { 0, 1, 2, 3, 4, 5 };
	KEYANIMANAGER->addArrayFrameAnimation("coin", "coinFrame", coinAni, 6, 5, true);

	for (int i = 0; i < 10; i++) //������ �ʱ�ȭ
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
	_vItem.clear(); //������ ���� Ŭ����
}

void itemManager::update()
{
	//�κ��丮�� ���ΰ� ��ǥ ����
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
	for (int i = 0; i < 4;) //�������� ������ ������ 4�� ��ġ
	{
		int rand = RND->getInt(10);
		if (_vItem[rand]->getStatus() == IN_STORE) continue;
		else addItemToStore(_vItem[rand]); i++;
	}
}

//�κ��丮�� ������ �߰� �̿��� ������ �� ���� �Լ�
void itemManager::setItem(item* item, STATUS status, POINTFLOAT position)
{
	item->setPosition(position); item->setStatus(status);
}

//���� �������� ȣ��޾� �������� ����� �Լ�
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

//�κ��丮�� ������ �߰� �Լ�
bool itemManager::addItemToInventory(item * item)
{
	if (_inventory->addItem(item)) { item->setPosition({ -25, -25 }); item->setStatus(IN_INVENTORY); return true; }

	return false;
}

//������ ������ �߰� �Լ�
bool itemManager::addItemToStore(item * item)
{
	if (_store->addItem(item)) { item->setStatus(IN_STORE); return true; }

	return false;
}

//�������� ������ �Ǹ� �Լ�
bool itemManager::sellItem(item * item)
{
	if (_player->getCoin() >= item->getPrice()) { if (addItemToInventory(item)) { _store->sellItem(item); return true; } }

	return false;
}

//���� ��� �Լ�
void itemManager::dropCoin(POINTFLOAT position)
{
	int randCount = RND->getInt(4) + 1;

	for (int i = 0; i < randCount; i++)
	{
		POINTFLOAT randPosition = { position.x + (RND->getFloat(50.0f) - 25.0f), position.y + (RND->getFloat(50.0f) - 25.0f) };
		EFFECT effect[2] = { { COIN, RND->getInt(10) + 5 }, { NONE, 0 } };
		const char* name = "�������� ����";
		const char* info = "������ �� �������� �����̴�";

		item* tempItem = new item;
		tempItem->init(randPosition, ON_FIELD, effect[0], effect[1], "coin", name, info, 0);
		_vItem.push_back(tempItem);
	}
}

//���� ȸ�� �Լ�
void itemManager::takeCoin(int index)
{
	_vItem.erase(_vItem.begin() + index);
}