#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_BgAlpha = 255;
	_frame = 0;
	_tick = 0;
	_da = new Dialogue;
	_da->init();


	return S_OK;
}

void firstCutScene::release(void)
{
	SAFE_DELETE(_da);
}

void firstCutScene::update(void)
{
	_da->update();

	_tick++;
	if (_tick % 10 == 0)
	{
		//셰라자드 죽음 프레임
		_frame++;
		if (_frame > 23)_frame = 0;

	}
	if (_BgAlpha > 0)_BgAlpha--;


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changScene("전투2");
}


// IMAGEMANAGER->findImage("셰라")->render(getMemDC(), 550, 200);
// IMAGEMANAGER->findImage("버몬트")->render(getMemDC(), 370, 150);
// IMAGEMANAGER->findImage("살라딘")->render(getMemDC(), -80, 80);

void firstCutScene::render(void)
{
	_da->render();

	IMAGEMANAGER->findImage("컷신배경")->render(getMemDC());
	IMAGEMANAGER->findImage("셰라죽음")->frameRender(getMemDC(), 180, 430, 0,0);

	IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), _BgAlpha);
	// 다이얼로그 시작
	// 1번 다이얼로그
	if (_BgAlpha == 0 && !_da->getDialogueEnd(1))
	{
		IMAGEMANAGER->findImage("버몬트")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 버몬트 이름
		_da->drawTextNoSkip(0, 130, 550, 100, 100, 30, 54, 255, 159);
		// 버몬트 대사
		_da->drawTextNoSkip(1, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(1)&& !_da->getDialogueEnd(3))
	{
		IMAGEMANAGER->findImage("살라딘")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 살라딘 이름
		_da->drawTextNoSkip(2, 130, 550, 100, 100, 30, 54, 255, 159);
		// 버몬트 대사
		_da->drawTextNoSkip(3, 130, 580, 200, 100, 25, 255, 255, 255);

	}
	if (_da->getDialogueEnd(3) && !_da->getDialogueEnd(5))
	{
		IMAGEMANAGER->findImage("버몬트")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 살라딘 이름
		_da->drawTextNoSkip(4, 130, 550, 100, 100, 30, 54, 255, 159);
		// 버몬트 대사
		_da->drawTextNoSkip(5, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(5) && !_da->getDialogueEnd(7))
	{
		IMAGEMANAGER->findImage("셰라")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(6, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(7, 130, 580, 200, 100, 25, 255, 255, 255);
	}
	
	if (_da->getDialogueEnd(7) && !_da->getDialogueEnd(9))
	{
		IMAGEMANAGER->findImage("살라딘")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(8, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(9, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(9) && !_da->getDialogueEnd(11))
	{
		IMAGEMANAGER->findImage("버몬트")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(10, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(11, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(11) && !_da->getDialogueEnd(13))
	{
		IMAGEMANAGER->findImage("셰라")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(12, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(13, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(13) && !_da->getDialogueEnd(15))
	{
		IMAGEMANAGER->findImage("살라딘")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(14, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(15, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(15) && !_da->getDialogueEnd(17))
	{
		IMAGEMANAGER->findImage("버몬트")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(16, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(17, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(5) && !_da->getDialogueEnd(7))
	{
		IMAGEMANAGER->findImage("셰라")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(6, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(7, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(5) && !_da->getDialogueEnd(7))
	{
		IMAGEMANAGER->findImage("셰라")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("다이얼로그창")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// 셰라 이름
		_da->drawTextNoSkip(6, 130, 550, 100, 100, 30, 54, 255, 159);
		// 셰라 대사
		_da->drawTextNoSkip(7, 130, 580, 200, 100, 25, 255, 255, 255);
	}


}
