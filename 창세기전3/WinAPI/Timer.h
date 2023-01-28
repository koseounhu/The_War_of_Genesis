#pragma once

#pragma region Ÿ�̸�
/*
	�� Ÿ�̸�
	- ������ ����� API ���� �Լ�(���������δ� ȿ���� ���� ���� ...)
	 �� GetTickCount ();
	 �� GetTickCount64();

	- �ð��� �����ϴ� �Լ����� �⺻������ �����찡 ���۵� ���� ���� �ð��� �и����� ������
	  ��ȯ�Ѵ�.
	- �и� �����庸�� ���� ������ Ÿ�̸Ӹ� ���Ѵٸ� ���� Ÿ�̸Ӹ� �����ؾ� �Ѵ�.
	- ���� Ÿ�̸Ӹ� ���� �� ���� 2������ �������
�١ڡ١�		�� 1. �ػ�		�١ڡ١ڡ١ڡ١�
�١ڡ١�		�� 2. Ŭ��(������)�١ڡ١ڡ١ڡ١�

	�� �ػ�
	- �پ��� �ð� �Լ����� �ð��� �����ϱ����� Tick �������� �ִ�.
		�� ���� 1���� �������� �󸶳� ���� ���������� ���� �� �մ��� ���
	- 1�е��� �󸶳� ���� Tick���� ������ �ð��� ��Ȯ���� ���̴��İ� ���ػ󵵿� ���ػ���
	  ���������� �Ǵ� ���� (���ػ� 1�ʿ� ���� , ���ػ� 1�ʿ� 92���)

	�� clock
	- Ÿ�̸ӿ��� ���ϴ� Ŭ���� ���� CPUŬ���� �ǹ��Ѵ�.
	- Ŭ���̶�?
	�� Ŭ���� ������ ȸ���� ������ �������̸� Hz������ ǥ��
	�� ex : 1�ʿ� 1hz�� ��ȣ�� �ѹ��ش�.(0 �Ǵ� 1) -> 1�ʿ� ��Ʈ �ϳ��� �ű���ִ�.
	�� 1Ghz�� 10�� 9���� -> 10���

	- Ÿ�̸� ����
	- Milli Second
	- 10  Milli Second
	- 100 Milli Second

	�١ڡ١�
	�� ���� Ÿ�̸��� ��� ��ø�� ��Ű�� ��ø�� ��Ų��ŭ ȿ���� �ö󰣴�. �������� �ö����� cpu�� gpu�� �����ϰ��ɸ���.



*/
#pragma endregion
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
	// const = ����Լ��� ���ȭ�� �ǹ��Ѵ�
	// �� �Լ������� ��� ������ �� ������ ���´�.
	// �� ��� ������ ���� �� �� �մ� ��ȸ�� ���� ������ ���� ���� ���� �Ұ�
	// �� ������ �Ұ�
	// ���� FPS
	unsigned long getFrameRate(char* str = nullptr) const;	

	// ������ �ð��� ���� �ð��� �����
	inline float getElapsedTime(void) const { return _timeElapsed; }

	//��ü ����ð�
	inline float getWorldTime(void) const { return _worldTime; }
	



	Timer() {}
	~Timer() {}
};

