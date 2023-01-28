#pragma once

class Animation;

class GImage
{
public:
	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE=0,LOAD_FILE,	//리소스로 로딩, 파일로 로딩
		LOAD_EMPTY, LOAD_END		//빈 비트맵 로딩
	};
	
	typedef struct tagImage
	{
		DWORD		resID;			//리소스 ID
		HDC			hMemDc;			//메모리 DC
		HBITMAP		hBit;			//비트맵
		HBITMAP		hOBit;			//올드 비트맵
		float		x;				//이미지 x좌표(레프트)
		float		y;				//이미지 y좌표(탑)
		int			width;			//이미지 가로크기
		int			height;			//이미지 세로크기
		int			currentFrameX;	//현재 프레임 X 좌표
		int			currentFrameY;	//현재 프레임 Y 좌표
		int			maxFrameX;		//최대 프레임 X 좌표
		int			maxFrameY;		//최대 프레임 Y 좌표
		int			frameWidth;		//1 프레임 가로
		int			frameHeight;	//1 프레임 세로
		BYTE		loadType;		//이미지 로드 타입

		
		tagImage()
		{
			resID = 0;
			hMemDc = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
			x = y = 0;
			width = 0;
			height = 0;
			currentFrameX=0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}
	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;		//이미지 정보
	char*			 _fileName;		//이미지 이름
	bool			_isTrans;		//배경색
	COLORREF		_transColor;	//배경색 없앨 RGB (RGB(255,0,255))

	BLENDFUNCTION _blendFunc;		//알파 블렌드 기능
	LPIMAGE_INFO _blendImage;		//알파 블렌드 이미지
	
public:
	//WinAPI 자료형이 혼합된 형태
	//ㄴ 함수 오버로딩 규칙 조심
	HRESULT init(int width, int height);
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	//프레임 이미지 파일로 초기화
	HRESULT init(const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0)); //단일이미지
	HRESULT init(const char* fileName, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(const char* fileName, float x, float y, int width, int height, int maxFrameX, int maxFrameY, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));

	HRESULT initForAlphaBlend(void);

	void setTransColor(bool isTrans, COLORREF transColor);
	
	void release(void);
	
	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);

	//클리핑
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	void alphaRender(HDC hdc, BYTE alpha); //배경 알파블렌드
	void alphaRender(HDC hdc, int destX, int destY, BYTE alpha); //원하는 위치에 알파블렌드
	void alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha); //스킬 이펙트용


	void frameRender(HDC hdc, int destX, int destY);
	void frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY);

	void loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void aniRender(HDC hdc, int destX, int destY, Animation* ani);

	void alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha, int currentFrameX, int currentFrameY);


	//===============
	//# 인라인 함수 #
	//===============
	inline HDC getMemDC(void) { return _imageInfo->hMemDc; }
	// 이미지 x좌표
	inline float getX(void) { return _imageInfo->x; }
	inline void setX(float x) { _imageInfo->x = x; }
	// 이미지 y좌표
	inline float getY(void) { return _imageInfo->y; }
	inline void setY(float y) { _imageInfo->y = y; }

	// 이미지 센터좌표
	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = x - (_imageInfo->height / 2);
	}

	// 이미지 가로, 세로 크기
	inline int getWidth(void) { return _imageInfo->width; }
	inline int getHeight(void) { return _imageInfo->height; }
	
	// 바운딩 박스(충돌용 렉트)
	inline RECT boundingBox(void)
	{
		RECT rc =
		{
			(int) _imageInfo->x,
			(int) _imageInfo->y,
			(int) _imageInfo->x + _imageInfo->width,
			(int) _imageInfo->y + _imageInfo->height,
		};

		return rc;
	}

	// 프레임 X
	inline int getFrameX(void) { return _imageInfo->currentFrameX; }
	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;
		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	// 프레임 Y
	inline int getFrameY(void) { return _imageInfo->currentFrameY; }
	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;
		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	// 이미지 1 프레임 가로, 세로
	inline int getFrameWidth(void) { return _imageInfo->frameWidth; }
	inline int getFrameHeight(void) { return _imageInfo->frameHeight; }

	// 최대 프레임 X,Y갯수
	inline int getMaxFrameX(void) { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY(void) { return _imageInfo->maxFrameY; }

	GImage();
	~GImage() {}
};

