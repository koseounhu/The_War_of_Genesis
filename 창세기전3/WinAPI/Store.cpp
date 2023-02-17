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

	if(SOUNDMANAGER->getPosition("�������")==0) SOUNDMANAGER->play("�������", 1.0f);


	_exitX = 910;
	_exitY = 720;
	_exitRC = RectMake(_exitX, _exitY, 90, 26);


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
					SOUNDMANAGER->play("��ư", 1.0f);
					SCENEMANAGER->changScene("�������");
				}
				if (PtInRect(&_exitRC, _ptMouse)) SCENEMANAGER->changScene("�ε�","�����");
				
			}
		}

		// ���λ��� �ؽ�Ʈ
		FONTMANAGER->drawText(getMemDC(), _menu.rc[0].left + 60, _menu.rc[0].top + 12, 25, 255, 255, 255, "����", true, "���� ����");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[1].left + 60, _menu.rc[1].top + 12, 25, 255, 255, 255, "����", true, "���� ����");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[2].left + 60, _menu.rc[2].top + 12, 25, 255, 255, 255, "����", true, "�뺴 ����");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[3].left + 60, _menu.rc[3].top + 12, 25, 255, 255, 255, "����", true, "  ��  �� ");
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X/2-90, 16, 30, 255, 223, 0, "����", true, "  �� �� �� ");


	} // ����== true

	// ������ ��ư
	IMAGEMANAGER->findImage("����������ư")->frameRender(getMemDC(), _exitX, _exitY,0,0);
	FONTMANAGER->drawText(getMemDC(), _exitX + 18, _exitY + 3, 17, 255, 255, 255, "����", true, "E X I T");

#pragma region ���콺
	ShowCursor(false);
	_Mrc = RectMake(_ptMouse.x, _ptMouse.y, 16, 24);
	_frame++;
	IMAGEMANAGER->findImage("�Ϲݸ��콺")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frame, 0);
	if (_frame > 12)_frame = 0;
#pragma endregion


}
