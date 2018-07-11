#pragma once
//==================================================================================//
//============== 현재 체크된 맵툴의 상태를 맵 타일에 전해주기 위한 클래스 ==============//
//==================================================================================//

#include "mapToolNode.h"

extern ERASER				_eraser;
extern currentCheck			_currentCheck;		// 현재 어떤 상태인지
extern tagCurrentTerrain	_currentTerrain;	// 현재 지형 정보
extern tagCurrentObject		_currentObject;		// 현재 오브젝트 정보
extern tagCurrentAuto		_currentAuto;		// 현재 자동 타일 정보

class current
{
public:
	current();
	~current();
};