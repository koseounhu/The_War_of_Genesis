#pragma once

class Timer
{
private:
	float	 _timeScale;				// 경과시간 조절
	float	 _timeElapsed;				// 마지막 시간과 현재시간의 경과값
	bool	_isHardware;				// 고성능타이머 지원 여부
		






	// 64비트 이하의 컴퓨터에서 64비트로 강제 시동시켜준다
	__int64 _curTime;				// 현재 시간
	__int64 _lastTime;				// 이전 시간
	__int64 _periodFrequency;		// 시간 주기

	unsigned long _frameRate;		// FPS(초당 프레임 수)
	unsigned long _FPSFrameCount;	// FPS 카운트
	float _FPSTimeElapsed;			// FPS 시간 경과량
	float _worldTime;				// 게임이 시작된 후 경과된 전체시간



public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	
	unsigned long getFrameRate(char* str = nullptr) const;	

	// 마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }

	//전체 경과시간
	inline float getWorldTime(void) const { return _worldTime; }
	



	Timer() {}
	~Timer() {}
};

