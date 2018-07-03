#include "stdafx.h"
#include "inventory.h"

inventory::inventory() {}
inventory::~inventory() {}

HRESULT inventory::init()
{
	_image = new image;
	_image = IMAGEMANAGER->addImage("inventory", "image/item/inventory.bmp", 400, 500, true, RGB(255, 0, 255));

	_isOpen = false;

	return S_OK;
}

void inventory::release() {}

void inventory::update()
{
	keyProcess();
}

void inventory::render()
{
	if (_isOpen)
	{
		_position = { CAMERAMANAGER->getCameraPoint().x - WINSIZEX / 4, CAMERAMANAGER->getCameraPoint().y };
		_image->alphaRender(CAMERAMANAGER->getCameraDC(), _position.x - _image->getWidth() / 2, _position.y - _image->getHeight() / 2, 200);

		for (int i = 0; i < _vItem.size(); i++)
		{
			_itemRect[i] = RectMakeCenter(_position.x - 90 + i * 100, _position.y - 150, 50, 50);
			_vItem[i]->getImage()->render(CAMERAMANAGER->getCameraDC(), _itemRect[i].left, _itemRect[i].top);
			if (PtInRect(&_itemRect[i], _ptMouse))
			{
				HFONT font, oldFont;
				RECT itemText;
				font = CreateFont(25, 0, 0, 0, 25, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("¸¼Àº °íµñ"));
				oldFont = (HFONT)SelectObject(CAMERAMANAGER->getCameraDC(), font);
				SetTextColor(CAMERAMANAGER->getCameraDC(), RGB(0, 0, 0));
				SetBkMode(CAMERAMANAGER->getCameraDC(), TRANSPARENT);
				itemText = RectMakeCenter(_position.x, _position.y - 25, 300, 50);
				DrawText(CAMERAMANAGER->getCameraDC(), TEXT(_vItem[i]->getName()), strlen(_vItem[i]->getName()), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				itemText = RectMakeCenter(_position.x, _position.y + 25, 300, 50);
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
					sprintf_s(info, (temp.type == HP ? "HP %s" : (temp.type == DAMAGE ? "DAMAGE %s" : (temp.type == SPEED ? "SPEED %s" : "CRITICAL %s"))), c);
					itemText = RectMakeCenter(_position.x, _position.y + 50 + j * 20, 300, 50);
					DrawText(CAMERAMANAGER->getCameraDC(), TEXT(info), strlen(info), &itemText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				}

				SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
				DeleteObject(font);
			}
		}
	}
}

void inventory::keyProcess()
{
	if (KEYMANAGER->isOnceKeyDown('I')) _isOpen = (_isOpen ? false : true);
}

void inventory::addItem(item * item)
{
	if (_vItem.size() != 3) _vItem.push_back(item);
}

const char * inventory::dumpItem(int index)
{
	if (index != -1) return _vItem[index]->getName();

	return NULL;
}