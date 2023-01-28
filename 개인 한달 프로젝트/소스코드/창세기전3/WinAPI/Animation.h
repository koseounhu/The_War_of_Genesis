#pragma once
class Animation
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;





private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;						// �����Ӽ�
	int _frameWidth;					// ������ ����ũ��
	int _frameHeight;					// ������ ����ũ��
	int _frameNumWidth;					// ���� ������ �� ����
	int _frameNumHeight;				// ���� ������ �� ����

	float _frameUpdateSec;				// �ʴ� ������ ������Ʈ ��
	float _elapsedSec;					// �����Ӱ� ������ ������ �ð�

	bool _isPlay;						// ���� �÷��� ���ΰ�
	bool _loop;							// ���� �ݺ� ���ΰ�
	DWORD _nowPlayIdx;					// ���� �÷��� ���� �ε���



public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);		// playArr -> list // ���ϴ� �����Ӹ� ����ֱ����� �Լ�
	void setPlayFrame(int start , int end, bool reverse = false, bool loop = false);

	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);
	void aniStart(void);
	void aniStop(void);
	void aniPaus(void);
	void aniResume(void);
	
	// �÷��� ���ΰ�?
	inline bool isPlay(void) { return _isPlay; }

	// ������ ��ġ�� ���´�.	// ���� ĳ���Ͱ� ������ ����Ѵ�.
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	// ���� �ִϸ��̼��� ������ ������ ���´�.
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	// ������ ���� ũ�⸦ ��´�
	inline int getFrameWidth(void) { return _frameWidth; }
	// ������ ���� ũ�⸦ ��´�.
	inline int getFrameHeight(void) { return _frameHeight; }
	// ���� ���° ������ �������� ��´�.
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }








	Animation(void);
	~Animation() {}
};

