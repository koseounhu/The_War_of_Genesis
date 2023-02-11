#pragma once
#include "GImage.h"


static GImage* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{
private:
	HDC _hdc;
	bool _managerInit;

public:
	// HRESULT: 함수가 성공적으로 실행되었는지 체크
	// ㄴ 32비트 signed 정수(음수가 아닌 값들은 성공을 의미하며 음수값들은 실패를 의미한다.)
	virtual HRESULT init(void);
	virtual HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	GImage* getBackBuffer(void) { return _backBuffer; }

	//메모리 DC 얻기
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	//HDC 얻기(화면 DC)
	HDC getHDC() { return _hdc; }

	LRESULT MainProc(HWND hWnd, UINT IMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}
};

