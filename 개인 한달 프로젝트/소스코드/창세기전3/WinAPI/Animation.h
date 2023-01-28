#pragma once
class Animation
{
private:
	typedef vector<POINT> _vFrameList;
	typedef vector<int> _vPlayList;





private:
	_vFrameList _frameList;
	_vPlayList _playList;

	int _frameNum;						// 프레임수
	int _frameWidth;					// 프레임 가로크기
	int _frameHeight;					// 프레임 세로크기
	int _frameNumWidth;					// 가로 프레임 총 갯수
	int _frameNumHeight;				// 세로 프레임 총 갯수

	float _frameUpdateSec;				// 초당 프레임 업데이트 수
	float _elapsedSec;					// 프레임과 프레임 사이의 시간

	bool _isPlay;						// 현재 플레이 중인가
	bool _loop;							// 현재 반복 중인가
	DWORD _nowPlayIdx;					// 현재 플레이 중인 인덱스



public:
	HRESULT init(int totalW, int totalH, int frameW, int frameH);
	void release(void);

	void setDefPlayFrame(bool reverse = false, bool loop = false);
	void setPlayFrame(int* playArr = nullptr, int arrLen = 0, bool loop = false);		// playArr -> list // 원하는 프레임만 찍어주기위한 함수
	void setPlayFrame(int start , int end, bool reverse = false, bool loop = false);

	void setFPS(int framePerSec);
	void frameUpdate(float elapsedTime);
	void aniStart(void);
	void aniStop(void);
	void aniPaus(void);
	void aniResume(void);
	
	// 플레이 중인가?
	inline bool isPlay(void) { return _isPlay; }

	// 프레임 위치를 얻어온다.	// 보통 캐릭터가 죽을때 사용한다.
	inline POINT getFramePos(void) { return _frameList[_playList[_nowPlayIdx]]; }

	// 현재 애니메이션의 프레임 순서를 얻어온다.
	inline int getFrameIdx(void)
	{
		POINT ptPos = getFramePos();
		int frameX = ptPos.x / _frameWidth;
		int frameY = ptPos.y / _frameHeight;

		return frameX + frameY * _frameNumWidth;
	}

	// 프레임 가로 크기를 얻는다
	inline int getFrameWidth(void) { return _frameWidth; }
	// 프레임 세로 크기를 얻는다.
	inline int getFrameHeight(void) { return _frameHeight; }
	// 현재 몇번째 프레임 순서인지 얻는다.
	inline DWORD getNowPlayIdx(void) { return _nowPlayIdx; }








	Animation(void);
	~Animation() {}
};

