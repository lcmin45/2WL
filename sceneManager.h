#pragma once
#include "singletonBase.h"
#include <map>

//���� ���� ���ӳ�� ���漱��
class gameNode;

class sceneManager : public singletonBase<sceneManager>
{
public:
	typedef map<string, gameNode*>				mapSceneList;
	typedef map<string, gameNode*>::iterator	mapSceneIter;

private:
	static gameNode*	_currentScene;	//���� ��
	mapSceneList		_mSceneList;

public:
	sceneManager();
	~sceneManager();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	//�� �߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//�� ����
	HRESULT changeScene(string sceneName);
	HRESULT changeScene(string sceneName, void* info);
};