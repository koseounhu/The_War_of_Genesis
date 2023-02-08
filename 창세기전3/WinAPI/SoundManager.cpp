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

	// �޸� �ѹ� ����
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

	// �ý��� ����
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

	if (loop)													// �ݺ� ������
	{
		if (backGround)											// �������
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);			// 1��1 ��Ī

		}
		else													// ȿ����
		{
			// ���ÿ� ������ ���� ��� ����
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSounds.size()]);			// �������� ���������� ���� �ٹ߼����� ����Ѵ�. �߸��� ������ ����ϸ� ������.
		}
	}
	else
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSounds.size()]);

	}

	// �ʿ� ���带 Ű���� �Բ� �־��ش�.
	_mTotalSounds.insert(make_pair(keyName, &_sound[_mTotalSounds.size()]));

}


// ���α׷����� + ���� + ����Ʈ + �ִϸ��̼� �迭
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
