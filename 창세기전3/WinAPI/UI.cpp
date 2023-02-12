#include "Stdafx.h"
#include "UI.h"
#include "Player.h"

HRESULT UI::init(void)
{
    return S_OK;
}

void UI::release(void)
{
}

void UI::update(void)
{
	if (_ui || _ability || _skillOn || _tileOn || _state || _tigerOn)
	{
		_total = true;
	}
	else _total = false;

	
}

void UI::render(Player* _pl)
{
#pragma region UI
	// ��ų UI â
	if (_ui && !_skillOn)
	{
		RECT _skillUI[4];
		_skillUI[0] = RectMakeCenter(_pl->getPL()._x - 80, _pl->getPL()._y - 40, IMAGEMANAGER->findImage("��ųUI")->getFrameWidth(), IMAGEMANAGER->findImage("��ųUI")->getFrameHeight());
		_skillUI[1] = RectMakeCenter(_pl->getPL()._x + 130, _pl->getPL()._y - 40, IMAGEMANAGER->findImage("��ųUI")->getFrameWidth(), IMAGEMANAGER->findImage("��ųUI")->getFrameHeight());
		_skillUI[2] = RectMakeCenter(_pl->getPL()._x - 80, _pl->getPL()._y, IMAGEMANAGER->findImage("��ųUI")->getFrameWidth(), IMAGEMANAGER->findImage("��ųUI")->getFrameHeight());
		_skillUI[3] = RectMakeCenter(_pl->getPL()._x + 130, _pl->getPL()._y, IMAGEMANAGER->findImage("��ųUI")->getFrameWidth(), IMAGEMANAGER->findImage("��ųUI")->getFrameHeight());



		IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[0].left, _skillUI[0].top, 0, 0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[0].left + 32, _skillUI[0].top + 7, 12, 255, 255, 255, "����", true, "�����Ƽ");

		IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[1].left, _skillUI[1].top, 1, 0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[1].left + 32, _skillUI[1].top + 7, 12, 255, 255, 255, "����", true, "�̵�");
		IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[2].left, _skillUI[2].top, 2, 0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[2].left + 32, _skillUI[2].top + 7, 12, 255, 255, 255, "����", true, "�Ϲݰ���");
		IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[3].left, _skillUI[3].top, 3, 0);
		FONTMANAGER->drawText(getMemDC(), _skillUI[3].left + 32, _skillUI[3].top + 7, 12, 255, 255, 255, "����", true, "����");

		if (PtInRect(&_skillUI[0], _ptMouse))
		{
			IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[0].left, _skillUI[0].top, 0, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[0].left + 32, _skillUI[0].top + 7, 13, 255, 255, 255, "����", true, "�����Ƽ");
		}

		if (PtInRect(&_skillUI[1], _ptMouse))
		{
			IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[1].left, _skillUI[1].top, 1, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[1].left + 32, _skillUI[1].top + 7, 13, 255, 255, 255, "����", true, "�̵�");
		}
		if (PtInRect(&_skillUI[2], _ptMouse))
		{
			IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[2].left, _skillUI[2].top, 2, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[2].left + 32, _skillUI[2].top + 7, 13, 255, 255, 255, "����", true, "�Ϲݰ���");
		}
		if (PtInRect(&_skillUI[3], _ptMouse))
		{
			IMAGEMANAGER->findImage("��ųUI")->frameRender(getMemDC(), _skillUI[3].left, _skillUI[3].top, 3, 1);
			FONTMANAGER->drawText(getMemDC(), _skillUI[3].left + 32, _skillUI[3].top + 7, 13, 255, 255, 255, "����", true, "����");
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("��ư", 1.0f);
			if (PtInRect(&_skillUI[0], _ptMouse))
			{
				_ui = false;
				_ability = true;
			}
			else if (PtInRect(&_skillUI[3], _ptMouse))
			{
				_ui = false;
				_state = true;
			}
			else if (PtInRect(&_skillUI[1], _ptMouse))
			{
				_ui = false;
				_tileOn = true;
			}
			else if (PtInRect(&_skillUI[2], _ptMouse))
			{
				_ui = false;
				_atk = true;
			}
		}
	}
#pragma endregion
#pragma region �����Ƽ
	if (_ability)
	{
		RECT _abilityA;
		_abilityA = RectMakeCenter(_pl->getPL()._x + 50, _pl->getPL()._y - 60, IMAGEMANAGER->findImage("�����Ƽâ")->getFrameWidth(), IMAGEMANAGER->findImage("�����Ƽâ")->getFrameHeight());

		IMAGEMANAGER->findImage("�����Ƽâ")->alphaRender(getMemDC(), _abilityA.left, _abilityA.top, 150);
		IMAGEMANAGER->findImage("�����Ƽ��ư")->frameRender(getMemDC(), _abilityA.left + 10, _abilityA.top + 10, 1, 0);
		IMAGEMANAGER->findImage("�����Ƽ��ư")->frameRender(getMemDC(), _abilityA.left + 10, _abilityA.top + 35, 1, 0);
		IMAGEMANAGER->findImage("�����Ƽ��ư")->frameRender(getMemDC(), _abilityA.left + 10, _abilityA.top + 60, 0, 0);
		IMAGEMANAGER->findImage("�����Ƽ��ư")->frameRender(getMemDC(), _abilityA.left + 10, _abilityA.top + 85, 0, 0);


		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 10, 15, 255, 255, 255, "����", true, "õ���Ŀ���");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 35, 15, 255, 255, 255, "����", true, "������õ");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 60, 15, 255, 255, 255, "����", true, "��");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 30, _abilityA.top + 85, 15, 255, 255, 255, "����", true, "��");


		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 130, _abilityA.top + 10, 15, 255, 0, 0, "����", true, "LV5");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 130, _abilityA.top + 35, 15, 255, 0, 0, "����", true, "LV3");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 130, _abilityA.top + 60, 15, 255, 0, 0, "����", true, "LV1");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 130, _abilityA.top + 85, 15, 255, 0, 0, "����", true, "LV1");

		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 170, _abilityA.top + 10, 15, 255, 215, 0, "����", true, "200");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 170, _abilityA.top + 35, 15, 255, 215, 0, "����", true, "150");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 170, _abilityA.top + 60, 15, 255, 215, 0, "����", true, "50");
		FONTMANAGER->drawText(getMemDC(), _abilityA.left + 170, _abilityA.top + 85, 15, 255, 215, 0, "����", true, "50");

		RECT _abilityB;
		_abilityB = RectMake(_abilityA.left + 5, _abilityA.top + 10, 150, 20);
		if (PtInRect(&_abilityB, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("��ư", 1.0f);
			_ui = _ability = false;
			_skillOn = true;
		}
		
		RECT _abilityC;
		_abilityC = RectMake(_abilityA.left + 5, _abilityA.top + 35, 150, 20);
		if (PtInRect(&_abilityC, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("��ư", 1.0f);
			_ui = _ability = false;
			_tigerOn = true;
		}
	}
#pragma endregion
#pragma region ����â
	if (_state)
	{
		IMAGEMANAGER->findImage("UI��������â")->alphaRender(getMemDC(),_pl->getPL()._x+100,_pl->getPL()._y-100,255);

	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		_ui = false;
		_ability = false;
		_state = false;
	}	


#pragma endregion 

}
