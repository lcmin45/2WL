#include "stdafx.h"
#include "soundManager.h"

soundManager::soundManager() 
	:_system(NULL), 
	_channel(NULL)
{}

soundManager::~soundManager() {}

HRESULT soundManager::init()
{
	System_Create(&_system);

	_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);

	_channel = new tagChannel[TOTALSOUNDBUFFER];

	ZeroMemory(_channel, sizeof(_channel));

	return S_OK;
}

void soundManager::release()
{
	// 사운드 삭제
	for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
	{
		if (_channel[index].keyName != "\0") _channel[index].channel->stop();
	}

	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		_viSound->sound->release();
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_channel);
	_vSound.clear();

	//시스템 닫기 
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update()
{
	//사운드 System 계속적으로 업데이트
	_system->update();

	//볼륨이 바뀌거나 
	//재생이 끝난 사운드를 채널에서 빼내는등의 다양한
	//작업을 자동으로 해준다
}

void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{
	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (_viSound->keyName == keyName) return;
	}

	tagSound sound;
	ZeroMemory(&sound, sizeof(tagSound));
	sound.keyName = (string)keyName;

	if (loop)
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &sound.sound);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, NULL, &sound.sound);
		}
	}
	else
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_DEFAULT, NULL, &sound.sound);
		}
		else
		{
			_system->createSound(soundName.c_str(), FMOD_DEFAULT, NULL, &sound.sound);
		}
	}

	_vSound.push_back(sound);
}

void soundManager::addPlayList(void)
{
	//대강 사용하는 형태
	OPENFILENAME ofn;
	char filePathSize[1028] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePathSize;
	ofn.nMaxFile = sizeof(filePathSize);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = ("*.mp3,*.wav,*.wmv");
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	//예외처리
	if (GetOpenFileName(&ofn) == FALSE) return;

	char temp[1028];
	strncpy_s(temp, strlen(ofn.lpstrFile) + 1, ofn.lpstrFile, strlen(ofn.lpstrFile));

	char* context = NULL;
	char* token = strtok_s(temp, "\\", &context);

	while (strlen(context))
	{
		token = strtok_s(NULL, "\\", &context);
	}
	
	SOUNDMANAGER->addSound(token, ofn.lpstrFile, true, false);
}

void soundManager::removePlayList(string keyName)
{
	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); )
	{
		if (keyName == _viSound->keyName)
		{
			_viSound = _vSound.erase(_viSound);
			break;
		}
		else ++_viSound;
	}
}

void soundManager::play(string KeyName, float volume)
{
	bool isCheck;

	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (KeyName == _viSound->keyName)
		{
			for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
			{
				if (_channel[index].keyName == "\0" || _channel[index].keyName == KeyName)
				{
					_system->playSound(FMOD_CHANNEL_FREE, _viSound->sound, false, &_channel[index].channel);
					_channel[index].keyName = _viSound->keyName;
					_channel[index].channel->setVolume(volume);
					break;
				}				
			}			
			break;	
		}
	}
}

void soundManager::stop(string keyName)
{
	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (keyName == _viSound->keyName)
		{
			for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
			{
				if (keyName == _channel[index].keyName)
				{
					_channel[index].channel->stop();
					_channel[index].keyName = "\0";
					break;
				}
			}
			break;
		}
	}
}

void soundManager::pause(string keyName)
{
	for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
	{
		if (keyName == _channel[index].keyName)
		{
			_channel[index].channel->setPaused(true);
			break;
		}
	}
}

void soundManager::resume(string keyName)
{
	for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
	{
		if (keyName == _channel[index].keyName)
		{
			_channel[index].channel->setPaused(false);
			break;
		}
	}
}

bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;

	for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
	{
		if (keyName == _channel[index].keyName)
		{
			_channel[index].channel->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::isPauseSound(string keyName)
{
	bool isPause;

	for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
	{
		if (keyName == _channel[index].keyName)
		{
			_channel[index].channel->getPaused(&isPause);
			break;
		}
	}

	return isPause;
}

void  soundManager::setEffectVolume(float volume)
{
	for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
	{
		_channel[index].channel->setVolume(volume);
	}
}

float soundManager::getEffectVolume(void)
{
	float volume = 0.0f;
	_channel[0].channel->getVolume(&volume);

	return volume;
}

void soundManager::singleChannelPlay(string keyName)
{
	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (keyName == _viSound->keyName)
		{
			_system->playSound(FMOD_CHANNEL_REUSE, _viSound->sound, false, &_singleChannel);
			break;
		}
	}	
}

void soundManager::singleChannelPause(void)
{
	_singleChannel->setPaused(true);
}

void soundManager::singleChannelResume(void)
{
	_singleChannel->setPaused(false);
}

void soundManager::singleChannelChangeVolume(float volume)
{
	_singleChannel->setVolume(volume);
}

float soundManager::singleChannelGetVolume(void)
{
	float _volume = 0.0f;
	_singleChannel->getVolume(&_volume);

	return _volume;
}

bool soundManager::singleChannelIsPlay(void)
{
	bool isPlay;

	_singleChannel->isPlaying(&isPlay);

	return isPlay;
}

bool soundManager::singleChannelIsPause(void)
{
	bool isPause;

	_singleChannel->getPaused(&isPause);

	return isPause;
}

int soundManager::getLength(string keyName)
{
	unsigned int length = 0;

	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (keyName == _viSound->keyName)
		{
			_viSound->sound->getLength(&length, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return length;
}

int soundManager::getPlayTime(string keyName)
{
	unsigned int time = 0;

	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (keyName == _viSound->keyName)
		{
			for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
			{
				if (_channel[index].keyName == keyName)
				{
					_channel[index].channel->getPosition(&time, FMOD_TIMEUNIT_MS);
					break;
				}
			}
			break;
		}
	}

	return time;
}

void soundManager::setPlayTime(string keyName, unsigned int time)
{
	for (_viSound = _vSound.begin(); _viSound != _vSound.end(); ++_viSound)
	{
		if (keyName == _viSound->keyName)
		{
			for (int index = 0; index < TOTALSOUNDBUFFER; ++index)
			{
				if (_channel[index].keyName == keyName)
				{
					_channel[index].channel->setPosition(time, FMOD_TIMEUNIT_MS);
					break;
				}
			}
			break;
		}
	}
}

int  soundManager::singleChannelPlayTime(void)
{
	unsigned int time = 0;

	_singleChannel->getPosition(&time, FMOD_TIMEUNIT_MS);

	return time;	
}

void soundManager::singleChannelSetPlayTime(unsigned int time)
{
	_singleChannel->setPosition(time, FMOD_TIMEUNIT_MS);
}