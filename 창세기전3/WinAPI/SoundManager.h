#pragma once
#include "SingletonBase.h"


constexpr auto soundBuffer = 10;
constexpr auto extraSoundChannel = 5;
constexpr auto totalSoundChannel = soundBuffer + extraSoundChannel;


using namespace FMOD;


class SoundManager : public SingletonBase <SoundManager>
{
private:

	typedef map<string, Sound**> arrSounds;
	typedef map<string, Sound**>::iterator arrSoundIter;
	typedef map<string, Channel**> arrChannels;
	typedef map<string, Channel**>::iterator arrChannelIter;


	System* _system;		
	Sound** _sound;			
	Channel** _channel;		

	arrSounds _mTotalSounds;


public:
	HRESULT init(void);
	void release(void);
	void update(void);

	void addSound(string keyName, string soundName, bool backGround, bool loop);

	void play(string keyName, float volume);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);

	unsigned int getPosition(string keyName);
	unsigned int getLength(string keyName);


	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);




	SoundManager();
	~SoundManager() {}
};

