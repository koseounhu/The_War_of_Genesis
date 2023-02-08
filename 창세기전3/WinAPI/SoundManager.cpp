#include "Stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager() : _system(nullptr),_channel(nullptr),_sound(nullptr)
{}




HRESULT SoundManager::init(void)
{
	System_Create(&_system);
	_system->init(totalSoundChannel,FMOD_INIT_NORMAL, 0);

	_sound = new Sound*[totalSoundChannel];
	_channel = new Channel * [totalSoundChannel];

	// 메모리 한번 밀자
	memset(_sound, 0, sizeof(Sound*) * (totalSoundChannel));
	memset(_channel, 0, sizeof(Channel*) * (totalSoundChannel));

	return S_OK;
}

void SoundManager::release(void)
{
	if (_channel != nullptr || _sound != nullptr)
	{
		for (int i = 0; i < totalSoundChannel; i++)
		{
			if (_channel != nullptr)
			{
				if (_channel[i])_channel[i]->stop();
			}

			
			if (_sound != nullptr)
			{
				if (_sound != nullptr) _sound[i]->release();
			}
		}
	}


	SAFE_DELETE_ARRAY(_channel);
	SAFE_DELETE_ARRAY(_sound);

	// 시스템 해제
	if (_system != nullptr)
	{
		_system->release();
		_system->close();					
	}
}

void SoundManager::update(void)
{
	_system->update();

}

void SoundManager::addSound(string keyName, string soundName, bool backGround, bool loop)
{

	if (loop)													// 반복 중인지
	{
		if (backGround)											// 배경음악
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);			// 1대1 매칭

		}
		else													// 효과음
		{
			// 동시에 여러개 음원 재생 가능
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);			// 안정성은 떨어지지만 동시 다발성으로 사용한다. 잘못된 참조를 사용하면 터진다.
		}
	}
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);

	}

	// 맵에 사운드를 키값과 함께 넣어준다.
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

}


// 프로그래스바 + 사운드 + 이펙트 + 애니메이션 계열
void SoundManager::play(string keyName, float volume)
{
	arrSoundIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			// _system->playSound(FMOD_CHANNEL_FREE, _sound[count], false, &_channel[count]);
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);
			_channel[count]->setVolume(volume);

			break;
		}
	}
}

void SoundManager::stop(string keyName)
{
	arrSoundIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->stop();

			break;
		}
	}
}

void SoundManager::pause(string keyName)
{
	arrSoundIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(true);

			break;
		}
	}
}

void SoundManager::resume(string keyName)
{
	arrSoundIter iter = _mTotalSounds.begin();
	int count = 0;
	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->setPaused(false);

			break;
		}
	}
}

unsigned int SoundManager::getPosition(string keyName)
{
	
	arrSoundIter iter = _mTotalSounds.begin();

	int count=0;
	unsigned int position;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getPosition(&position, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return position;
}

unsigned int SoundManager::getLength(string keyName)
{
	Sound* currentSound = nullptr;

	int count = 0;
	arrSoundIter iter = _mTotalSounds.begin();

	unsigned int length;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->getCurrentSound(&currentSound);
			currentSound->getLength(&length, FMOD_TIMEUNIT_MS);
			break;
		}
	}

	return length;

}

bool SoundManager::isPlaySound(string keyName)
{
	bool isplay;
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isplay);
			break;
		}
	}
	return isplay;
}

bool SoundManager::isPauseSound(string keyName)
{

	bool isPause;
	int count = 0;

	arrSoundIter iter = _mTotalSounds.begin();

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			_channel[count]->isPlaying(&isPause);
			break;
		}
	}




	return isPause;
}



void SoundManager::stopAllSound(void)
{
	arrSoundIter iter = _mTotalSounds.begin();

	int count = 0;

	for (iter; iter != _mTotalSounds.end(); ++iter, count++)
	{
		_channel[count]->stop();
	}
}
