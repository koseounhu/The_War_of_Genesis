#pragma once

#pragma region 타이머
/*
	▶ 타이머
	- 기존에 사용한 API 공용 함수(게임쪽으로는 효율이 아주 별로 ...)
	 ㄴ GetTickCount ();
	 ㄴ GetTickCount64();

	- 시간을 측정하는 함수들은 기본적으로 윈도우가 시작된 이후 지난 시간을 밀리세컨 단위로
	  반환한다.
	- 밀리 세컨드보다 좀더 정밀한 타이머를 원한다면 고성능 타이머를 구현해야 한다.
	- 보통 타이머를 구현 할 때는 2가지를 기억하자
☆★☆★		ㄴ 1. 해상도		☆★☆★☆★☆★
☆★☆★		ㄴ 2. 클럭(진동수)☆★☆★☆★☆★

	▷ 해상도
	- 다양한 시간 함수들은 시간을 측정하기위한 Tick 계산로직이 있다.
		ㄴ 보통 1분을 기준으로 얼마나 많은 프레임으로 나눌 수 잇는지 계산
	- 1분동안 얼마나 많은 Tick으로 나눠서 시간의 정확도를 높이느냐가 고해상도와 저해상도의
	  차이점이자 판단 기준 (저해상도 1초에 만번 , 고해상도 1초에 92억번)

	▷ clock
	- 타이머에서 말하는 클럭은 보통 CPU클럭을 의미한다.
	- 클럭이란?
	ㄴ 클럭은 디지털 회로의 전기적 진동수이며 Hz단위로 표기
	ㄴ ex : 1초에 1hz면 신호를 한번준다.(0 또는 1) -> 1초에 비트 하나를 옮길수있다.
	ㄴ 1Ghz는 10에 9제곱 -> 10억번

	- 타이머 단위
	- Milli Second
	- 10  Milli Second
	- 100 Milli Second

	☆★☆★
	※ 고성능 타이머의 경우 중첩을 시키면 중첩을 시킨만큼 효율이 올라간다. 프레임은 올라가지만 cpu와 gpu는 과부하가걸린다.



*/
#pragma endregion
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
	// const = 멤버함수의 상수화를 의미한다
	// ㄴ 함수내에서 멤버 변수의 값 변경을 막는다.
	// ㄴ 멤버 변수가 변경 될 수 잇는 기회를 주지 않으면 변수 역시 변경 불가
	// ㄴ 포인터 불가
	// 현재 FPS
	unsigned long getFrameRate(char* str = nullptr) const;	

	// 마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }

	//전체 경과시간
	inline float getWorldTime(void) const { return _worldTime; }
	



	Timer() {}
	~Timer() {}
};

