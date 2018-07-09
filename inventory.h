#pragma once
#include "gameNode.h"
#include "item.h"
#include <vector>

class inventory : public gameNode
{
private:
	vector<item*> _vItem; //������ ����
	image* _image; //�̹���
	RECT _inventoryRect; //�κ��丮 ��Ʈ
	RECT _itemRect[3]; //�κ��丮 ���� ������ 3���� ��Ʈ
	int _selectedItemIndex; //���� ������ ���� �ε���
	bool _isOpen; //�κ��丮�� ���� �����ִ��� ����
public:
	inventory();
	~inventory();

	virtual HRESULT init();
	virtual void release();
	virtual void update(POINTFLOAT position);
	virtual void render();

	void keyProcess(POINTFLOAT position); //Ű ���μ���
	bool addItem(item* item); //������ �߰� �Լ�
	void dumpItem(int index, POINTFLOAT position); //������ ������ �Լ�

	bool getIsOpen() { return _isOpen; }
	vector<item*> getVItem() { return _vItem; }
};