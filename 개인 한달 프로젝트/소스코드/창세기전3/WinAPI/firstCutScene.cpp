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


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changScene("����2");
}

void firstCutScene::render(void)
{
	IMAGEMANAGER->findImage("�ƽŹ��")->render(getMemDC());
	IMAGEMANAGER->findImage("�ӽ�1")->render(getMemDC(), 180, 430);
	IMAGEMANAGER->findImage("�ӽ�2")->render(getMemDC(), 230, 600);


	IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _BgAlpha);
}
