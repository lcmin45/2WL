#include "stdafx.h"
#include "boss.h"

boss::boss() {}
boss::~boss() {}

HRESULT boss::init()
{
	//나무 보스 이미지
	IMAGEMANAGER->addFrameImage("나무소환", "image/boss/나무보스/나무보스소환.bmp", 0, 0, 3200, 129, 25, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무등장", "image/boss/나무보스/나무보스등장.bmp", 0, 0, 294*2, 58 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무점프", "image/boss/나무보스/나무보스점프.bmp", 0, 0, 420 * 2, 69 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무오른쪽", "image/boss/나무보스/나무보스오른쪽이동.bmp", 0, 0, 184 * 2, 51 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무왼쪽", "image/boss/나무보스/나무보스왼쪽이동.bmp", 0, 0, 184 * 2, 51 * 2, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무스킬", "image/boss/나무보스/나무보스스킬.bmp", 0, 0, 210 * 2, 58 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무스킬2오른쪽", "image/boss/나무보스/나무보스스킬2오른쪽.bmp", 0, 0, 430 * 2, 58 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무스킬2왼쪽", "image/boss/나무보스/나무보스스킬2왼쪽.bmp", 0, 0, 430 * 2, 58 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무오른쪽피격", "image/boss/나무보스/나무보스오른쪽피격.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무왼쪽피격", "image/boss/나무보스/나무보스왼쪽피격.bmp", 0, 0, 70 * 2, 59 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("나무죽음", "image/boss/나무보스/나무보스죽음.bmp", 0, 0, 34 * 2, 45 * 2, 1, 1, true, RGB(255, 0, 255));

	//얼음 보스 이미지
	IMAGEMANAGER->addFrameImage("얼음소환", "image/boss/얼음보스/얼음보스소환.bmp", 0, 0, 500 * 2, 61 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음등장", "image/boss/얼음보스/얼음보스등장.bmp", 0, 0, 228 * 2, 54 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음뒤", "image/boss/얼음보스/얼음보스뒤이동.bmp", 0, 0, 31 * 2, 42 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음앞", "image/boss/얼음보스/얼음보스앞이동.bmp", 0, 0, 32 * 2, 35 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음오른쪽", "image/boss/얼음보스/얼음보스오른쪽이동.bmp", 0, 0, 32 * 2, 40 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음왼쪽", "image/boss/얼음보스/얼음보스왼쪽이동.bmp", 0, 0, 32 * 2,40 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음스킬", "image/boss/얼음보스/얼음보스스킬.bmp", 0, 0, 306 * 2, 52 * 2, 9, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음스킬2", "image/boss/얼음보스/얼음보스스킬2.bmp", 0, 0,96*2, 50*2, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음피격", "image/boss/얼음보스/얼음보스피격.bmp", 0, 0, 40 * 2, 48 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("얼음죽음", "image/boss/얼음보스/얼음보스죽음.bmp", 0, 0, 32 * 2, 38 * 2, 1, 1, true, RGB(255, 0, 255));

	//불꽃 보스 이미지
	IMAGEMANAGER->addFrameImage("불소환", "image/boss/불보스/불보스소환.bmp", 0, 0, 350 * 2, 45 * 2, 7, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불등장", "image/boss/불보스/불보스등장.bmp", 0, 0, 350 * 2, 33 * 2, 10, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불오른쪽", "image/boss/불보스/불보스오른쪽이동.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불왼쪽", "image/boss/불보스/불보스왼쪽이동.bmp", 0, 0, 40 * 2, 28 * 2, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬오른쪽", "image/boss/불보스/불보스스킬오른쪽.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬왼쪽", "image/boss/불보스/불보스스킬왼쪽.bmp", 0, 0, 228 * 2, 40 * 2, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬2오른쪽", "image/boss/불보스/불보스스킬2오른쪽.bmp", 0, 0, 135 * 2, 40 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불스킬2왼쪽", "image/boss/불보스/불보스스킬2왼쪽.bmp", 0, 0, 135 * 2, 40 * 2, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불피격", "image/boss/불보스/불보스피격.bmp", 0, 0, 42 * 2, 37 * 2, 2, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("불죽음", "image/boss/불보스/불보스죽음.bmp", 0, 0, 28 * 2, 30 * 2, 1, 1, true, RGB(255, 0, 255));

	_woodBossDie = false;
	_iceBossDie= false;
	_fireBossDie= false;
	_index = 0;

	_woodDirection = WOODDIRECTION_SOHWAN;
	_iceDirection = ICEDIRECTION_SOHWAN;
	_fireDirection = FIREDIRECTION_SHOW;

	return S_OK;
}

HRESULT boss::setting(const char * imageName, POINT position)
{
	_frameCount = 0;
	_bossImg = IMAGEMANAGER->findImage(imageName);
	_bossRc = RectMakeCenter(position.x, position.y, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());
	return S_OK;
}

void boss::release() {}

void boss::render()
{
	_bossImg->frameRender(CAMERAMANAGER->getCameraDC(), _bossRc.left, _bossRc.top, _index,0);
}

void boss::update()
{
	_frameCount++;
	if (_frameCount % 10 == 0)
	{
		++_index;
		if (_woodDirection == WOODDIRECTION_SHOW || _iceDirection == ICEDIRECTION_SHOW || _fireDirection == FIREDIRECTION_SHOW)
		{
			if (_index > _bossImg->getMaxFrameX())
			{
				_index = 0;
			}
		}
		_frameCount = 0;
	}
}

void boss::woodMove()
{
}

void boss::iceMove()
{
}

void boss::fireMove()
{
}

void boss::woodSkill()
{
}

void boss::iceSkill()
{
}

void boss::fireSkill()
{
}
