#pragma once

class Timer
{
private:
	float	 _timeScale;				// ����ð� ����
	float	 _timeElapsed;				// ������ �ð��� ����ð��� �����
	bool	_isHardware;				// ����Ÿ�̸� ���� ����
		






	// 64��Ʈ ������ ��ǻ�Ϳ��� 64��Ʈ�� ���� �õ������ش�
	__int64 _curTime;				// ���� �ð�
	__int64 _lastTime;				// ���� �ð�
	__int64 _periodFrequency;		// �ð� �ֱ�

	unsigned long _frameRate;		// FPS(�ʴ� ������ ��)
	unsigned long _FPSFrameCount;	// FPS ī��Ʈ
	float _FPSTimeElapsed;			// FPS �ð� �����
	float _worldTime;				// ������ ���۵� �� ����� ��ü�ð�



public:
	HRESULT init(void);
	void tick(float lockFPS = 0.0f);
	
	unsigned long getFrameRate(char* str = nullptr) const;	

	// ������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }

	//��ü ����ð�
	inline float getWorldTime(void) const { return _worldTime; }
	



	Timer() {}
	~Timer() {}
};

