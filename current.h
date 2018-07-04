#pragma once
#include "mapToolNode.h"

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

