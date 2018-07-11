#include "stdafx.h"
#include "option.h"

option::option() { }

option::~option() { }

HRESULT option::init()
{
	_isView = false;

	_effectX = SOUNDMANAGER->getEffectVolume();
	_bgmX = SOUNDMANAGER->singleChannelGetVolume();

	return S_OK;
}

void option::release()
{

}

void option::update()
{
	if (!_isView) return;

	if (!KEYMANAGER->isStayKeyDown(VK_LBUTTON)) return;

	// ��Ʈ �巡�� ó��
	//_volumeBar.px = _ptMouse.x;
	//if (_volumeBar.px >= _volumeBar.barRC.right)	_volumeBar.px = _volumeBar.barRC.right;
	//if (_volumeBar.px <= _volumeBar.barRC.left)		_volumeBar.px = _volumeBar.barRC.left;
	//
	//_volumeBar.pointRC = RectMakeCenter(_volumeBar.px, _volumeBar.y, _volumeBar.point->getWidth(), _volumeBar.point->getHeight());
	//
	//_volume = (float)(_volumeBar.px - _volumeBar.barRC.left) / (float)(_volumeBar.barRC.right - _volumeBar.barRC.left);

	// �̴ϸ� �ƽø� ó��

	// ���� ����
	SOUNDMANAGER->setEffectVolume(_effectX);
	SOUNDMANAGER->singleChannelChangeVolume(_bgmX);

	// ��Ʈ ����
}

void option::render()
{
	if (!_isView) return;


}