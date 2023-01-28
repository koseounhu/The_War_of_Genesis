#include "Stdafx.h"
#include "firstCutScene.h"

HRESULT firstCutScene::init(void)
{
	_BgAlpha = 255;



	return S_OK;
}

void firstCutScene::release(void)
{
}

void firstCutScene::update(void)
{
	if (_BgAlpha > 0)_BgAlpha--;


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changScene("전투2");
}

void firstCutScene::render(void)
{
	IMAGEMANAGER->findImage("컷신배경")->render(getMemDC());
	IMAGEMANAGER->findImage("임시1")->render(getMemDC(), 180, 430);
	IMAGEMANAGER->findImage("임시2")->render(getMemDC(), 230, 600);


	IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), _BgAlpha);
}
