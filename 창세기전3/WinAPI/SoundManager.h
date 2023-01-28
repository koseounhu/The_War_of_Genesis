#pragma once
#include "SingletonBase.h"

#pragma region FMOD
/*
FMOD
- Sound Engine 라이브러리
- 언리얼과 유니티에는 라이센스 계약으로 기본 내장되어있다.
	ㄴ 이외의 대부분의 플랫포에서는 사용하기위한 선행 준비가 필요하다.
	ㄴ EX : CoCos2DX

- FMOD를 이용한 대표적인 게임
	ㄴ 와우, 바이오 쇼크 등등
*/
#pragma endregion

/*
	▶ constexpr (Const Expresstion)
	- C++ 11에서 추가된 키워드
	- 객체나 함수 앞에 붙일 수 있는 키워드로 해당 객체나 함수의 리턴값을 "컴파일" 타임에 알 수 있다.
	- 최신언어 17
	- C++ 17 람다식에 적용 가능
	- 컴파일 타임에 값이 결정되므로 함수 호출간에 템플릿 인자로 넘겨주기 아주 좋다.
	- const VS constexpr 차이점은 초기화 여부와 오류의 발견 시기
	- constexpr 변경불가, const는 변경 가능하지만따라서 완전한 상수라고 볼수있다.
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


	System* _system;			// FMOD에 있는 시스템 사운드에 관련된 모든 기능 관리 , 단순히 켜주고 꺼주는 기능
	Sound** _sound;				// 사운드를 멈추거나 재생하거나 반복하거나 넘기거나 하는 기능
	Channel** _channel;			// 서라운드 채널을 지원하기위해 사용 , 메모리 버퍼를 맞춰주기 위해 사용, 어디서 사운드가 들릴지 정해주기 위함
	// 더블 포인터 , 회사의 자산이 되는 부분인 cpp는 가려놧기때문에 더블포인터를 사용하여 넘어가서 사용

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

