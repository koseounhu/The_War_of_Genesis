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
		//�ζ��ڵ� ���� ������
		_frame++;
		if (_frame > 23)_frame = 0;

	}
	if (_BgAlpha > 0)_BgAlpha--;


	if (KEYMANAGER->isOnceKeyDown(VK_F1)) SCENEMANAGER->changScene("����2");
}


// IMAGEMANAGER->findImage("�ζ�")->render(getMemDC(), 550, 200);
// IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 370, 150);
// IMAGEMANAGER->findImage("����")->render(getMemDC(), -80, 80);

void firstCutScene::render(void)
{
	_da->render();

	IMAGEMANAGER->findImage("�ƽŹ��")->render(getMemDC());
	IMAGEMANAGER->findImage("�ζ�����")->frameRender(getMemDC(), 180, 430, 0,0);

	IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _BgAlpha);
	// ���̾�α� ����
	// 1�� ���̾�α�
	if (_BgAlpha == 0 && !_da->getDialogueEnd(1))
	{
		IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// ����Ʈ �̸�
		_da->drawTextNoSkip(0, 130, 550, 100, 100, 30, 54, 255, 159);
		// ����Ʈ ���
		_da->drawTextNoSkip(1, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(1)&& !_da->getDialogueEnd(3))
	{
		IMAGEMANAGER->findImage("����")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// ���� �̸�
		_da->drawTextNoSkip(2, 130, 550, 100, 100, 30, 54, 255, 159);
		// ����Ʈ ���
		_da->drawTextNoSkip(3, 130, 580, 200, 100, 25, 255, 255, 255);

	}
	if (_da->getDialogueEnd(3) && !_da->getDialogueEnd(5))
	{
		IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// ���� �̸�
		_da->drawTextNoSkip(4, 130, 550, 100, 100, 30, 54, 255, 159);
		// ����Ʈ ���
		_da->drawTextNoSkip(5, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(5) && !_da->getDialogueEnd(7))
	{
		IMAGEMANAGER->findImage("�ζ�")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(6, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(7, 130, 580, 200, 100, 25, 255, 255, 255);
	}
	
	if (_da->getDialogueEnd(7) && !_da->getDialogueEnd(9))
	{
		IMAGEMANAGER->findImage("����")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(8, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(9, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(9) && !_da->getDialogueEnd(11))
	{
		IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(10, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(11, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(11) && !_da->getDialogueEnd(13))
	{
		IMAGEMANAGER->findImage("�ζ�")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(12, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(13, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(13) && !_da->getDialogueEnd(15))
	{
		IMAGEMANAGER->findImage("����")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(14, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(15, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(15) && !_da->getDialogueEnd(17))
	{
		IMAGEMANAGER->findImage("����Ʈ")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(16, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(17, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(5) && !_da->getDialogueEnd(7))
	{
		IMAGEMANAGER->findImage("�ζ�")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(6, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(7, 130, 580, 200, 100, 25, 255, 255, 255);
	}

	if (_da->getDialogueEnd(5) && !_da->getDialogueEnd(7))
	{
		IMAGEMANAGER->findImage("�ζ�")->render(getMemDC(), 370, 150);
		RECT _text;
		_text = RectMakeCenter(WINSIZE_X / 2, WINSIZE_Y / 2 + 250, 800, 180);
		IMAGEMANAGER->findImage("���̾�α�â")->alphaRender(getMemDC(), _text.left, _text.top, 155);
		// �ζ� �̸�
		_da->drawTextNoSkip(6, 130, 550, 100, 100, 30, 54, 255, 159);
		// �ζ� ���
		_da->drawTextNoSkip(7, 130, 580, 200, 100, 25, 255, 255, 255);
	}


}
