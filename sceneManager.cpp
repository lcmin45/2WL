#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//����ƽ���� ������ �Ǿ �ʱ�ȭ�� �������� �ʱ�ȭ
gameNode* sceneManager::_currentScene = NULL;

sceneManager::sceneManager() {}
sceneManager::~sceneManager() {}

HRESULT sceneManager::init()
{
	_currentScene = NULL;

	return S_OK;
}

void sceneManager::release()
{
	mapSceneIter miSceneList = _mSceneList.begin();

	for (; miSceneList != _mSceneList.end();)
	{
		if (miSceneList->second != NULL)
		{
			if (miSceneList->second == _currentScene) miSceneList->second->release();
			SAFE_DELETE(miSceneList->second);
			miSceneList = _mSceneList.erase(miSceneList);
		}
		else ++miSceneList;
	}

	_mSceneList.clear();
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode* scene)
{
	//���� ���ٸ� NULL���� ��ȯ�ض�
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//���ͷ����� == ���� ����� ����? -> ��ã�Ҵ�
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ���� ���̸� ���д�
	if (find->second == _currentScene) return S_OK;

	//���������� ���� �ٲ�� init() �Լ��� �����Ѵ�

	if (SUCCEEDED(find->second->init()))
	{
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}

HRESULT sceneManager::changeScene(string sceneName, void* info)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//���ͷ����� == ���� ����� ����? -> ��ã�Ҵ�
	if (find == _mSceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ���� ���̸� ���д�
	if (find->second == _currentScene) return S_OK;

	//���������� ���� �ٲ�� init() �Լ��� �����Ѵ�

	if (SUCCEEDED(find->second->init(info)))
	{
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}