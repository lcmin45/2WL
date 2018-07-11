#include "stdafx.h"
#include "option.h"

option::option() { }

option::~option() { }

HRESULT option::init()
{
	_isView = false;

	_bgm.barImg = IMAGEMANAGER->findImage("optionBar");
	_eff.barImg = IMAGEMANAGER->findImage("optionBar");

	_bgm.barRc = RectMake(WINSIZEX / 2 - _bgm.barImg->getWidth() / 2,
		WINSIZEY / 2 - 25, _bgm.barImg->getWidth(), _bgm.barImg->getHeight());
	_eff.barRc = RectMake(WINSIZEX / 2 - _eff.barImg->getWidth() / 2,
		WINSIZEY / 2 + 55, _eff.barImg->getWidth(), _eff.barImg->getHeight());

	_bgm.iconImg = IMAGEMANAGER->findImage("optionChoiceBar");
	_eff.iconImg = IMAGEMANAGER->findImage("optionChoiceBar");
	
	_bgm.volume = SOUNDMANAGER->singleChannelGetVolume();
	_eff.volume = SOUNDMANAGER->getEffectVolume();	

	_bgm.iconX = (_bgm.volume * (float)(_bgm.barRc.right - _bgm.barRc.left)) + _bgm.barRc.left;
	_eff.iconX = (_eff.volume * (float)(_eff.barRc.right - _eff.barRc.left)) + _eff.barRc.left;

	_bgm.iconRc = RectMake(_bgm.iconX - _bgm.iconImg->getWidth() / 2, WINSIZEY / 2 - 25 - 5, _bgm.iconImg->getWidth(), _bgm.iconImg->getHeight());
	_eff.iconRc = RectMake(_eff.iconX - _eff.iconImg->getHeight() / 2, WINSIZEY / 2 + 55 - 5, _eff.iconImg->getWidth(), _eff.iconImg->getHeight());

	_button = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 170, 130, 50);
	
	return S_OK;
}

void option::release()
{

}

void option::update()
{
	if (!_isView) return;

	if (!KEYMANAGER->isStayKeyDown(VK_LBUTTON)) return;

	if (PtInRect(&_button, getCameraPoint()))	// 취소 버튼
	{
		_isView = false;
	}

	if (PtInRect(&_bgm.iconRc, getCameraPoint()))
	{
		_bgm.iconX = getCameraPoint().x;	

		if (_bgm.iconX < _bgm.barRc.left) _bgm.iconX = _bgm.barRc.left;
		if (_bgm.iconX > _bgm.barRc.right) _bgm.iconX = _bgm.barRc.right;

		_bgm.volume = (float)(_bgm.iconX - _bgm.barRc.left) / (float)(_bgm.barRc.right - _bgm.barRc.left);
		_bgm.iconRc = RectMake(_bgm.iconX - _bgm.iconImg->getWidth() / 2, WINSIZEY / 2 - 25 - 5, _bgm.iconImg->getWidth(), _bgm.iconImg->getHeight());
	}
	
	if (PtInRect(&_eff.iconRc, getCameraPoint()))
	{
		_eff.iconX = getCameraPoint().x;

		if (_eff.iconX < _eff.barRc.left) _eff.iconX = _eff.barRc.left;
		if (_eff.iconX > _eff.barRc.right) _eff.iconX = _eff.barRc.right;

		_eff.volume = (float)(_eff.iconX - _eff.barRc.left) / (float)(_eff.barRc.right - _eff.barRc.left);
		_eff.iconRc = RectMake(_eff.iconX - _eff.iconImg->getHeight() / 2, WINSIZEY / 2 + 55 - 5, _eff.iconImg->getWidth(), _eff.iconImg->getHeight());
	}

	SOUNDMANAGER->setEffectVolume(_eff.volume);
	SOUNDMANAGER->singleChannelChangeVolume(_bgm.volume);
}

void option::render()
{
	if (!_isView) return;

	IMAGEMANAGER->findImage("option")->render(CAMERAMANAGER->getCameraDC(),
		WINSIZEX / 2 - IMAGEMANAGER->findImage("option")->getWidth() / 2,
		WINSIZEY / 2 - IMAGEMANAGER->findImage("option")->getHeight() / 2);

	_bgm.barImg->render(CAMERAMANAGER->getCameraDC(),
		_bgm.barRc.left, _bgm.barRc.top);
	_eff.barImg->render(CAMERAMANAGER->getCameraDC(),
		_eff.barRc.left, _eff.barRc.top);
	
	_bgm.iconImg->render(CAMERAMANAGER->getCameraDC(),
		_bgm.iconRc.left, _bgm.iconRc.top);
	_eff.iconImg->render(CAMERAMANAGER->getCameraDC(),
		_eff.iconRc.left, _eff.iconRc.top);
}

void option::setIsView(bool isView)
{
	_isView = isView;

	_bgm.volume = SOUNDMANAGER->singleChannelGetVolume();
	_eff.volume = SOUNDMANAGER->getEffectVolume();

	_bgm.iconX = (_bgm.volume * (float)(_bgm.barRc.right - _bgm.barRc.left)) + _bgm.barRc.left;
	_eff.iconX = (_eff.volume * (float)(_eff.barRc.right - _eff.barRc.left)) + _eff.barRc.left;

	_bgm.iconRc = RectMake(_bgm.iconX - _bgm.iconImg->getWidth() / 2, WINSIZEY / 2 - 25 - 5, _bgm.iconImg->getWidth(), _bgm.iconImg->getHeight());
	_eff.iconRc = RectMake(_eff.iconX - _eff.iconImg->getHeight() / 2, WINSIZEY / 2 + 55 - 5, _eff.iconImg->getWidth(), _eff.iconImg->getHeight());
}