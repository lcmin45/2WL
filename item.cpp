#include "stdafx.h"
#include "item.h"

item::item() {}
item::~item() {}

HRESULT item::init(POINTFLOAT position, STATUS status, EFFECT effect0, EFFECT effect1, const char * imageName, const char * name, const char * info)
{
	//초기값 설정
	char directory[128];
	_position = position;
	_status = status;
	_effect[0] = effect0;
	_effect[1] = effect1;
	sprintf_s(directory, "image/item/%s.bmp", imageName);
	_image = IMAGEMANAGER->addImage(imageName, directory, 25, 25, true, RGB(255, 0, 255));
	_name = name;
	_info = info;

	return S_OK;
}

void item::release() {}

void item::update() {}

void item::render()
{
	//아이템의 상태가 필드에 있을 때만 랜더
	if (_status == ON_FIELD) _image->render(getMemDC(), _position.x - _image->getWidth() / 2, _position.y - _image->getHeight() / 2);
}