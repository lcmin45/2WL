#pragma once
#include "singletonBase.h"
#include <map>
#include <commdlg.h>//- > OPEN FILE NAME
#include <vector>
#include "inc/fmod.hpp"

#pragma comment(lib, "lib/fmodex64_vc.lib")

using namespace FMOD;

#define SOUNDBUFFER 10
#define EXTRACHANNELBUFFER 10

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

class soundManager : public singletonBase<soundManager>
{
private:

	struct tagSound
	{
		string		keyName;
		Sound*		sound;
		int			channelIndex;
	};

	struct tagChannel
	{
		string		keyName;
		Channel*	channel;
	};

	System*						_system;
	
	vector<tagSound>			_vSound;
	vector<tagSound>::iterator	_viSound;

	tagChannel*					_channel;
	Channel*					_singleChannel;

public:
	HRESULT init();
	void release();
	void update();

	void addSound(string keyName, string soundName, bool bgm, bool loop);
	void addPlayList(void);
	void removePlayList(string keyName);
	void play(string keyName, float volume = 1.0f); // 0.0 ~ 1.0f -> 0 ~ 255
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
	int getLength(string keyName);
	int getPlayTime(string keyName);
	void setPlayTime(string keyName, unsigned int time);
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);

	void singleChannelPlay(string keyName);
	void singleChannelPause(void);
	void singleChannelResume(void);
	void singleChannelChangeVolume(float volume);
	bool singleChannelIsPlay(void);
	bool singleChannelIsPause(void);
	int  singleChannelPlayTime(void);
	void singleChannelSetPlayTime(unsigned int time);
	

	vector<tagSound> getVSound(void) { return _vSound; }
	
	
	soundManager();
	~soundManager();
};

