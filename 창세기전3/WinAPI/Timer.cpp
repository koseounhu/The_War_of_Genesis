#include "Stdafx.h"
#include "Timer.h"

HRESULT Timer::init(void)
{//	QueryPerformanceFrequency() : 1초당 진동수를 체크하며
	// 고성능 타이머를 지원하면 t / 아니라면 f반환
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency))
	{
		_isHardware = true;
		// QueryPerformanceCounter () : 특정 시점에 몇번을 진동했는지 체크하는 함수
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		// 초당 시간을 계산 할 수 있는 시간 주기
		_timeScale = 1.0f / _periodFrequency;

	}
	// 고성능 타이머를 지원하지 않는다면
	else
	{
		_isHardware = false;
		// timeGetTime() : 보통 멀티미디어 타이머라고 불린다.
		// 운영체제가 시작되고 현재까지 흐른 시간을 밀리세컨 단위로 반환
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSFrameCount = 0;
	_FPSTimeElapsed = 0.0f;
	_worldTime = 0.0f;

	return S_OK;
}

// 현재시간 계산
// lock을 풀면 프레임 무조건 올라간다 ★☆★☆★☆★☆★☆★☆
void Timer::tick(float lockFPS)
{
	if (_isHardware)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	// 마지막 시간과 현재 시간의 경과량 측정
	_timeElapsed = (_curTime - _lastTime) * _timeScale;

	if (lockFPS > 0.0f)
	{
		while (_timeElapsed <(1.0f / lockFPS))
		{ 
			if (_isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else _curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSFrameCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSFrameCount;
		_FPSFrameCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::getFrameRate(char* str) const
{
	if (str != nullptr)
	{
		wsprintf(str, "FPS : %d", _frameRate);
	}
	return _frameRate;
}
