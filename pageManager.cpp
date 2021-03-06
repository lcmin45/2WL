#include "stdafx.h"
#include "pageManager.h"

pageManager::pageManager() { }

pageManager::~pageManager() { }

HRESULT pageManager::init(void)
{
	pageInit();

	return S_OK;
}

void pageManager::release(void)
{
	_page0->release();
	_page1->release();
	_page2->release();
	_page3->release();
	_page4->release();
	_page5->release();
	_page6->release();
	_page7->release();
	_page8->release();
	_page9->release();
	_page10->release();
}

void pageManager::update(void)
{
	pageUpdate();
}

void pageManager::render(void)
{
	switch (_pageIndex)
	{
	case 0:
		_page0->render();
		break;
	case 1:
		_page1->render();
		break;
	case 2:
		_page2->render();
		break;
	case 3:
		_page3->render();
		break;
	case 4:
		_page4->render();
		break;
	case 5:
		_page5->render();
		break;
	case 6:
		_page6->render();
		break;
	case 7:
		_page7->render();
		break;
	case 8:
		_page8->render();
		break;
	case 9:
		_page9->render();
		break;
	case 10:
		_page10->render();
		break;
	}
}

void pageManager::pageInit(void)
{
	_page0 = new page0;
	_page0->init();
	_page1 = new page1;
	_page1->init();
	_page2 = new page1;
	_page2->init();
	_page3 = new page2;
	_page3->init();
	_page4 = new page2;
	_page4->init();
	_page5 = new page3;
	_page5->init();
	_page6 = new page3;
	_page6->init();
	_page7 = new page4;
	_page7->init();
	_page8 = new page4;
	_page8->init();
	_page9 = new page4;
	_page9->init();
	_page10 = new page4;
	_page10->init();

	_page1->setIndex(0);
	_page2->setIndex(1);
	_page3->setIndex(0);
	_page4->setIndex(1);
	_page5->setIndex(0);
	_page6->setIndex(1);
	_page7->setIndex(0);
	_page8->setIndex(1);
	_page9->setIndex(2);
	_page10->setIndex(3);
}

void pageManager::pageUpdate(void)
{
	switch (_pageIndex)
	{
	case 0:
		_page0->update();
		break;
	case 1:
		_page1->update();
		break;
	case 2:
		_page2->update();
		break;
	case 3:
		_page3->update();
		break;
	case 4:
		_page4->update();
		break;
	case 5:
		_page5->update();
		break;
	case 6:
		_page6->update();
		break;
	case 7:
		_page7->update();
		break;
	case 8:
		_page8->update();
		break;
	case 9:
		_page9->update();
		break;
	case 10:
		_page10->update();
		break;
	}
}

void pageManager::setCenterPoint(POINT center)
{
	switch (_pageIndex)
	{
	case 0:
		_page0->setCenterPoint(center);
		break;
	case 1:
		_page1->setCenterPoint(center);
		break;
	case 2:
		_page2->setCenterPoint(center);
		break;
	case 3:
		_page3->setCenterPoint(center);
		break;
	case 4:
		_page4->setCenterPoint(center);
		break;
	case 5:
		_page5->setCenterPoint(center);
		break;
	case 6:
		_page6->setCenterPoint(center);
		break;
	case 7:
		_page7->setCenterPoint(center);
		break;
	case 8:
		_page8->setCenterPoint(center);
		break;
	case 9:
		_page9->setCenterPoint(center);
		break;
	case 10:
		_page10->setCenterPoint(center);
		break;
	}
}