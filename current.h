#pragma once
//==================================================================================//
//============== ���� üũ�� ������ ���¸� �� Ÿ�Ͽ� �����ֱ� ���� Ŭ���� ==============//
//==================================================================================//

#include "mapToolNode.h"

extern ERASER				_eraser;
extern currentCheck			_currentCheck;		// ���� � ��������
extern tagCurrentTerrain	_currentTerrain;	// ���� ���� ����
extern tagCurrentObject		_currentObject;		// ���� ������Ʈ ����
extern tagCurrentAuto		_currentAuto;		// ���� �ڵ� Ÿ�� ����

class current
{
public:
	current();
	~current();
};