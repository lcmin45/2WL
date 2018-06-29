#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool() {}

mapTool::~mapTool() {}


HRESULT mapTool::init(void)
{

	_book = new mapToolBook;
	_book->init();

	return S_OK;
}

void mapTool::release(void)
{
	_book->release();
}

void mapTool::update(void)
{
	_book->update();
}

void mapTool::render(void)
{
	_book->render();
}