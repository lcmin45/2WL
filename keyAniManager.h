#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

class image;
class animation;

class keyAniManager : public singletonBase<keyAniManager>
{
private:

	//����
	typedef vector<animation*>								arrAnimations;
	typedef vector<animation*>::iterator					iterAnimations;
	//����
	typedef map<string, arrAnimations>						arrAnimation;
	typedef map<string, arrAnimations>::iterator			iterAnimation;
	//����
	typedef vector<map<string, arrAnimations>>				arrTotalAnimation;
	typedef vector<map<string, arrAnimations>>::iterator	iterTotalAnimation;


private:

	arrTotalAnimation	_vTotalAnimation; //���常 �������� , ����� ������ ��������


public:
	keyAniManager();
	~keyAniManager();

	HRESULT init();
	void release();
	void update();
	void render();

	//����Ʈ �ִϸ��̼�
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction);
	void addDefaultFrameAnimation(string animationKeyName, const char* imageKeyName, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	//�迭 �ִϸ��̼�
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction);
	void addArrayFrameAnimation(string animationKeyName, const char* imageKeyName, int* arr, int arrLen, int fps, bool loop, void* cbFunction, void* obj);

	//���� �ִϸ��̼�
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction);
	void addCoordinateFrameAnimation(string animationKeyName, const char* imageKeyName, int start, int end, int fps, bool reverse, bool loop, void* cbFunction, void* obj);

	void start(string animationKeyName);
	void stop(string animationKeyName);
	void pause(string animationKeyName);
	void resume(string animationKeyName);

	animation* findAnimation(string animationKeyName);

	void deleteAll();
};

