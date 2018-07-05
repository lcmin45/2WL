#include "stdafx.h"
#include "keyAniManager.h"
#include "image.h"
#include "animation.h"

keyAniManager::keyAniManager()
{
}


keyAniManager::~keyAniManager()
{
}

HRESULT keyAniManager::init()
{
	return S_OK;
}

void keyAniManager::release()
{


}

void keyAniManager::update()
{

	iterTotalAnimation vIter;
	iterAnimation		mIter;

	//토탈벡터를 돌아서
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		//그 안에 담겨있는 맵 컨테이너를 돌아서
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			//맵에 담겨있는 벡터 컨테이너에 접근하여
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				//객체의 업데이트를 실행
				if (!(*vArrIter)->isPlay()) continue;
				(*vArrIter)->frameUpdate(TIMEMANAGER->getElapsedTime() * 1.0f);
			}
		}
	}

}

void keyAniManager::render()
{
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop)
{
	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;


	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction)
{
	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;


	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);

}

void keyAniManager::addDefaultFrameAnimation(string animationKeyName, const char * imageKeyName, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{
	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;


	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setDefPlayFrame(reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);

}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop)
{
	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;


	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction)
{

	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::addArrayFrameAnimation(string animationKeyName, const char * imageKeyName, int * arr, int arrLen, int fps, bool loop, void * cbFunction, void * obj)
{

	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(arr, arrLen, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop)
{

	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction)
{

	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION)cbFunction);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::addCoordinateFrameAnimation(string animationKeyName, const char * imageKeyName, int start, int end, int fps, bool reverse, bool loop, void * cbFunction, void * obj)
{

	arrAnimations		_vAnimations;
	arrAnimation		_vAnimation;

	image* img = IMAGEMANAGER->findImage(imageKeyName);
	animation* ani = new animation;

	ani->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
	ani->setPlayFrame(start, end, reverse, loop, (CALLBACK_FUNCTION_PARAMETER)cbFunction, obj);
	ani->setFPS(fps);

	_vAnimations.push_back(ani);
	_vAnimation.insert(pair<string, arrAnimations>(animationKeyName, _vAnimations));
	_vTotalAnimation.push_back(_vAnimation);
}

void keyAniManager::start(string animationKeyName)
{
	//iterAnimation iter = _vTotalAnimation.find(animationKeyName);
	//
	//iter->second->start();



	iterTotalAnimation vIter;
	iterAnimation		mIter;

	//토탈벡터를 돌아서
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		//그 안에 담겨있는 맵 컨테이너를 돌아서
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first != animationKeyName) break;
			//맵에 담겨있는 벡터 컨테이너에 접근하여
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				//객체의 업데이트를 실행
				if ((*vArrIter)->isPlay()) continue;
				(*vArrIter)->start();
				return;
			}
		}
	}
}

void keyAniManager::stop(string animationKeyName)
{
	/*iterAnimation iter = _vTotalAnimation.find(animationKeyName);

	iter->second->stop();*/


	iterTotalAnimation vIter;
	iterAnimation		mIter;

	//토탈벡터를 돌아서
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		//그 안에 담겨있는 맵 컨테이너를 돌아서
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first != animationKeyName) break;
			//맵에 담겨있는 벡터 컨테이너에 접근하여
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->stop();
				return;

			}
		}
	}
}

void keyAniManager::pause(string animationKeyName)
{/*
 iterAnimation iter = _vTotalAnimation.find(animationKeyName);

 iter->second->pause();*/

	iterTotalAnimation vIter;
	iterAnimation		mIter;

	//토탈벡터를 돌아서
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		//그 안에 담겨있는 맵 컨테이너를 돌아서
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first != animationKeyName) break;
			//맵에 담겨있는 벡터 컨테이너에 접근하여
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->pause();
				return;
			}
		}
	}
}

void keyAniManager::resume(string animationKeyName)
{
	/*iterAnimation iter = _vTotalAnimation.find(animationKeyName);

	iter->second->resume();*/

	iterTotalAnimation vIter;
	iterAnimation		mIter;

	//토탈벡터를 돌아서
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		//그 안에 담겨있는 맵 컨테이너를 돌아서
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first != animationKeyName) break;
			//맵에 담겨있는 벡터 컨테이너에 접근하여
			iterAnimations vArrIter;
			for (vArrIter = mIter->second.begin(); vArrIter != mIter->second.end(); ++vArrIter)
			{
				(*vArrIter)->resume();
				return;
			}
		}
	}
}

animation * keyAniManager::findAnimation(string animationKeyName)
{
	/*iterAnimation iter = _vTotalAnimation.find(animationKeyName);

	if (iter != _vTotalAnimation.end())
	{
	return iter->second;
	}
	*/

	iterTotalAnimation vIter;
	iterAnimation		mIter;

	//토탈벡터를 돌아서
	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		//그 안에 담겨있는 맵 컨테이너를 돌아서
		for (mIter = vIter->begin(); mIter != vIter->end(); ++mIter)
		{
			if (mIter->first != animationKeyName) break;
			//맵에 담겨있는 벡터 컨테이너에 접근하여
			iterAnimations vArrIter = mIter->second.begin();
			return (*vArrIter);
		}
	}


	return NULL;
}

void keyAniManager::deleteAll()
{
	//for (iterAnimation iter = _vTotalAnimation.begin(); iter != _vTotalAnimation.end();)
	//{
	//	if (iter->second != NULL)
	//	{
	//		iter->second->release();
	//		SAFE_DELETE(iter->second);
	//		iter = _vTotalAnimation.erase(iter);
	//	}
	//	else ++iter;
	//}

	//_vTotalAnimation.clear();


	iterTotalAnimation  vIter;
	iterAnimation		mIter;

	for (vIter = _vTotalAnimation.begin(); vIter != _vTotalAnimation.end(); ++vIter)
	{
		mIter = vIter->begin();

		for (; mIter != vIter->end();)
		{
			if (mIter->second.size() != 0)
			{
				iterAnimations vArrIter = mIter->second.begin();

				for (; vArrIter != mIter->second.end();)
				{
					(*vArrIter)->release();
					delete *vArrIter;
					vArrIter = mIter->second.erase(vArrIter);
				}
			}
			else ++mIter;
		}
	}
	_vTotalAnimation.clear();


}
