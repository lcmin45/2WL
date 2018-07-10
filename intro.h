#pragma once
#include "gameNode.h"


struct chageScene
{
	bool isChanged;
	int menuIndex;
};
class intro : public gameNode
{
	int _timer;
	int _buttonAlpha;
	int _titleY;
	int _setScene;
	int _sceneAlpha;

	image* _GameStart;
	image* _Load;
	image* _MapTool;
	image* _Setting;
	image* _EXIT;

	RECT _rc[5];
	chageScene _chageScene;

	int _soundCheck;



public:
	intro();
	~intro();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};