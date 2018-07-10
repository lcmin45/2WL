#include "stdafx.h"
#include "store.h"

store::store() {}
store::~store() {}

HRESULT store::init()
{
	_position = { 3280.0f, 2912.0f };

	return S_OK;
}

void store::release() {}

void store::update() {}

void store::render()
{
	//상점 좌표에 따라 이미지 렌더
	_image = IMAGEMANAGER->findImage("storeNpc");
	_image->render(getMemDC(), _position.x - _image->getWidth() / 2, _position.y - _image->getHeight() / 2 - 75);
	_image = IMAGEMANAGER->findImage("storeTable");
	_image->render(getMemDC(), _position.x - _image->getWidth() / 2, _position.y - _image->getHeight() / 2);

	//아이템 판매 정보
	HFONT font, oldFont;
	RECT priceText;
	font = CreateFont(15, 0, 0, 0, 25, 0, 0, 0, DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_CHARACTER_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("맑은 고딕"));
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
	char price[128];
	for (int i = 0; i < _vItem.size(); i++)
	{
		sprintf_s(price, "%d", _vItem[i]->getPrice());
		priceText = RectMakeCenter(_vItem[i]->getPosition().x, _vItem[i]->getPosition().y + 30, 100, 25);
		DrawText(getMemDC(), TEXT(price), strlen(price), &priceText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	SelectObject(CAMERAMANAGER->getCameraDC(), oldFont);
	DeleteObject(font);
}

bool store::addItem(item * item)
{
	if (_vItem.size() != 4)
	{
		_vItem.push_back(item);

		for (int i = 0; i < _vItem.size(); i++) _vItem[i]->setPosition({ _position.x - 60 + i * 40, _position.y - 15 });

		return true;
	}

	return false;
}

void store::sellItem(item * item)
{
	//아이템 판매
	for (int i = 0; i < _vItem.size(); i++) { if (_vItem[i] == item) _vItem.erase(_vItem.begin() + i); }

	item->setStatus(IN_INVENTORY);
}