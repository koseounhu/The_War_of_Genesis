#include "Stdafx.h"
#include "Store.h"

HRESULT Store::init(void)
{
	// ���� �޴� �ʱ�ȭ
	_menu.x = 800;
	_menu.y = 70;
	int temp=0;
	for (int i = 0; i < 4; i++)
	{
		_menu.rc[i]= RectMake(_menu.x, _menu.y+temp, 200, 50);
		temp += 70;
	}
	// ���۽� ���� �̹Ƿ� true����
	_main = true;



	return S_OK;
}

void Store::release(void)
{
}

void Store::update(void)
{
}

void Store::render(void)
{
	// ���� ���� ����
	IMAGEMANAGER->findImage("�������")->render(getMemDC());

	// ���� �޴�
	if (_main)
	{
		IMAGEMANAGER->findImage("����Ÿ��Ʋ")->render(getMemDC());
		IMAGEMANAGER->findImage("�����ٴھ�")->render(getMemDC(), 0, 570);

		// ���� ��ư ����
		for (int i = 0; i < _countof(_menu.rc); i++)
		{
			// �̹��� ����
			IMAGEMANAGER->findImage("�������θ޴���ư")->alphaFrameRender(getMemDC(), _menu.rc[i].left - 10, _menu.rc[i].top, 125, _menu.rcFrameCheck[i], 0);
			IMAGEMANAGER->findImage("�����޴��ǹ��̹���")->frameRender(getMemDC(), _menu.rc[i].left, _menu.rc[i].top, i, 0);

			// ���ι�ư ���콺 �浹
			if (PtInRect(&_menu.rc[i], _ptMouse))			_menu.rcFrameCheck[i] = true;
			else 			_menu.rcFrameCheck[i] = false;

			// �������� ����
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (PtInRect(&_menu.rc[i], _ptMouse))
				{
					SCENEMANAGER->changScene("�������");
				}
			}
		}

		// ���λ��� �ؽ�Ʈ
		FONTMANAGER->drawText(getMemDC(), _menu.rc[0].left + 60, _menu.rc[0].top + 12, 25, 255, 255, 255, "����", true, "���� ����");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[1].left + 60, _menu.rc[1].top + 12, 25, 255, 255, 255, "����", true, "���� ����");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[2].left + 60, _menu.rc[2].top + 12, 25, 255, 255, 255, "����", true, "�뺴 ����");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[3].left + 60, _menu.rc[3].top + 12, 25, 255, 255, 255, "����", true, "  ��  �� ");
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X/2-90, 16, 30, 255, 223, 0, "����", true, "  �� �� �� ");


	} // ����== true



}
