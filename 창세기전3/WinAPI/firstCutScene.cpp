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
		//�ζ��ڵ� ���� ������
		_frame++;
		if (_frame > 23)_frame = 0;

	}
	if (_BgAlpha > 0)_BgAlpha--;


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changScene("�����");
}

void firstCutScene::render(void)
{
	IMAGEMANAGER->findImage("�ƽŹ��")->render(getMemDC());
	IMAGEMANAGER->findImage("�ζ�����")->frameRender(getMemDC(), 180, 430, _frame,0);


	IMAGEMANAGER->findImage("����")->render(getMemDC(), -80, 80);


	// IMAGEMANAGER->findImage("�ζ�")->render(getMemDC(), 550, 200);

	// IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 370, 150);


	IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _BgAlpha);
}
