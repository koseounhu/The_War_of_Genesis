#pragma once
#include "SingletonBase.h"

#pragma region FMOD
/*
FMOD
- Sound Engine ���̺귯��
- �𸮾�� ����Ƽ���� ���̼��� ������� �⺻ ����Ǿ��ִ�.
	�� �̿��� ��κ��� �÷��������� ����ϱ����� ���� �غ� �ʿ��ϴ�.
	�� EX : CoCos2DX

- FMOD�� �̿��� ��ǥ���� ����
	�� �Ϳ�, ���̿� ��ũ ���
*/
#pragma endregion

/*
	�� constexpr (Const Expresstion)
	- C++ 11���� �߰��� Ű����
	- ��ü�� �Լ� �տ� ���� �� �ִ� Ű����� �ش� ��ü�� �Լ��� ���ϰ��� "������" Ÿ�ӿ� �� �� �ִ�.
	- �ֽž�� 17
	- C++ 17 ���ٽĿ� ���� ����
	- ������ Ÿ�ӿ� ���� �����ǹǷ� �Լ� ȣ�Ⱓ�� ���ø� ���ڷ� �Ѱ��ֱ� ���� ����.
	- const VS constexpr �������� �ʱ�ȭ ���ο� ������ �߰� �ñ�
	- constexpr ����Ұ�, const�� ���� �������������� ������ ������ �����ִ�.
*/












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


	System* _system;			// FMOD�� �ִ� �ý��� ���忡 ���õ� ��� ��� ���� , �ܼ��� ���ְ� ���ִ� ���
	Sound** _sound;				// ���带 ���߰ų� ����ϰų� �ݺ��ϰų� �ѱ�ų� �ϴ� ���
	Channel** _channel;			// ������ ä���� �����ϱ����� ��� , �޸� ���۸� �����ֱ� ���� ���, ��� ���尡 �鸱�� �����ֱ� ����
	// ���� ������ , ȸ���� �ڻ��� �Ǵ� �κ��� cpp�� �����J�⶧���� ���������͸� ����Ͽ� �Ѿ�� ���

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

	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);




	SoundManager();
	~SoundManager() {}
};

