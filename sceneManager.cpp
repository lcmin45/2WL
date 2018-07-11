#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

//스태틱으로 선언이 되어서 초기화는 전역으로 초기화
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
	//씬이 없다면 NULL값을 반환해라
	if (!scene) return NULL;

	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

HRESULT sceneManager::changeScene(string sceneName)
{
	mapSceneIter find = _mSceneList.find(sceneName);

	//이터레이터 == 맵의 엔드와 같다? -> 못찾았다
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재 씬이면 냅둔다
	if (find->second == _currentScene) return S_OK;

	//성공적으로 씬이 바뀌면 init() 함수를 실행한다

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

	//이터레이터 == 맵의 엔드와 같다? -> 못찾았다
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬이 현재 씬이면 냅둔다
	if (find->second == _currentScene) return S_OK;

	//성공적으로 씬이 바뀌면 init() 함수를 실행한다

	if (SUCCEEDED(find->second->init(info)))
	{
		if (_currentScene) _currentScene->release();

		_currentScene = find->second;

		return S_OK;
	}

	return E_FAIL;
}