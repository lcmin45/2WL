#include "stdafx.h"
#include "inventory.h"

inventory::inventory() {}
inventory::~inventory() {}

HRESULT inventory::init()
{
	//�ʱⰪ ����
	_image = new image;
	_image = IMAGEMANAGER->addImage("inventory", "image/item/inventory.bmp", 400, 500, true, RGB(255, 0, 255));
	_inventoryRect = RectMakeCenter(WINSIZEX / 4, WINSIZEY / 2, 400, 500);
	_selectedItemIndex = -1;
	_isOpen = false;

	return S_OK;
}

void inventory::release() {}

void inventory::update(POINTFLOAT position)
{
	keyProcess(position);
}

void inventory::render()
{
	if (_isOpen) //�κ��丮�� �������� ��� ����
	{
		_image->alphaRender(CAMERAMANAGER->getCameraDC(), _inventoryRect.left, _inventoryRect.top, 200);

		for (int i = 0; i < _vItem.size(); i++)
		{
			_itemRect[i] = RectMakeCenter(_inventoryRect.left + 110 + i * 100, _inventoryRect.top + 100, 50, 50);
			_vItem[i]->getImage()->render(CAMERAMANAGER->getCameraDC(), _itemRect[i].left, _itemRect[i].top);
			if (PtInRect(&_itemRect[i], _ptMouse))
			{
				//������ �̸�, ������ ���� ���� �۾�
				HFONT font, oldFont;
				RECT itemText;
				font = CreateFont(25, 0, 0, 0, 25, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("���� ���"));
				oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font);
				SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(0, 0, 0));
				SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);
				itemText = RectMakeCenter(_inventoryRect.left + 200, _inventoryRect.top + 250, 300, 50);
				DrawText(CAMERAMANAGER->getCameraDC(), TEXT(_vItem[i]->getName()), strlen(_vItem[i]->getName()), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				itemText = RectMakeCenter(_inventoryRect.left + 200, _inventoryRect.top + 300, 300, 50);
				DrawText(CAMERAMANAGER->getCameraDC(), TEXT(_vItem[i]->getInfo()), strlen(_vItem[i]->getInfo()), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

				char info[128];
				char info2[128];
				for (int j = 0; j < 2; j++)
				{
					EFFECT temp = _vItem[i]->getEffect()[j];
					if (temp.type == NONE) break;
					char c[10];
					if (temp.amount > 0) sprintf_s(c, "+%d", temp.amount);
					else sprintf_s(c, "%d", temp.amount);
					strcat_s(c, "\%");
					sprintf_s(info, (temp.type == HP ? "HP %s" : (temp.type == DAMAGE ? "DAMAGE %s" : (temp.type == SPEED ? "SPEED %s" : "CRITICAL %s"))), c);
					itemText = RectMakeCenter(_inventoryRect.left + 200, _inventoryRect.top + 325 + j * 20, 300, 50);
					DrawText(CAMERAMANAGER->getCameraDC(), TEXT(info), strlen(info), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
				DeleteObject(font);
			}
		}
	}
}

void inventory::keyProcess(POINTFLOAT position)
{
	//�κ��丮 ����
	if (KEYMANAGER->isOnceKeyDown('I')) _isOpen = (_isOpen ? false : true);

	//�����ִ� ���¿��� ������ ������ ó��
	if (_isOpen)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			for (int i = 0; i < _vItem.size(); i++)
			{
				if (PtInRect(&_itemRect[i], _ptMouse))
				{
					_selectedItemIndex = i;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
		{
			if (!PtInRect(&_inventoryRect, _ptMouse))
			{
				if (_selectedItemIndex != -1) dumpItem(_selectedItemIndex, position);
				_selectedItemIndex = -1;
			}
		}
	}
}

//������ �߰�
bool inventory::addItem(item * item)
{
	if (_vItem.size() != 3) { _vItem.push_back(item); return true; }

	return false;
}

//������ ������
void inventory::dumpItem(int index, POINTFLOAT position)
{
	_vItem[_selectedItemIndex]->setPosition(position);
	_vItem[_selectedItemIndex]->setStatus(ON_FIELD);
	_vItem.erase(_vItem.begin() + index);
}