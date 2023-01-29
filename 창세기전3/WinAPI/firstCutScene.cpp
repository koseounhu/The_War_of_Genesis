#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_BgAlpha = 255;
	_frame = 0;
	_tick = 0;


	return S_OK;
}

void firstCutScene::release(void)
{
}

void firstCutScene::update(void)
{
	_tick++;
	if (_tick % 10 == 0)
	{
		//¼Î¶óÀÚµå Á×À½ ÇÁ·¹ÀÓ
		_frame++;
		if (_frame > 23)_frame = 0;

	}
	if (_BgAlpha > 0)_BgAlpha--;


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changScene("¿ùµå¸Ê");
}

void firstCutScene::render(void)
{
	IMAGEMANAGER->findImage("ÄÆ½Å¹è°æ")->render(getMemDC());
	IMAGEMANAGER->findImage("¼Î¶óÁ×À½")->frameRender(getMemDC(), 180, 430, _frame,0);


	IMAGEMANAGER->findImage("»ì¶óµò")->render(getMemDC(), -80, 80);


	// IMAGEMANAGER->findImage("¼Î¶ó")->render(getMemDC(), 550, 200);

	// IMAGEMANAGER->findImage("¹ö¸óÆ®")->render(getMemDC(), 370, 150);


	IMAGEMANAGER->findImage("°ËÁ¤¾ËÆÄ")->alphaRender(getMemDC(), _BgAlpha);
}
