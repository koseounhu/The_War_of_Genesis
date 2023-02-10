#include "Stdafx.h"
#include "WeaponShop.h"

HRESULT WeaponShop::init(void)
{
#pragma region ��ǥ ����
    _button[0].x = 60;
    _button[0].y = 110;
    _button[0].rc = RectMake(_button[0].x, _button[0].y, 90, 26);
    _button[0].click = true;
   
    _button[1].x = 150;
    _button[1].y = 110;
    _button[1].rc = RectMake(_button[1].x, _button[1].y, 90, 26);

    _button[2].x = 450;
    _button[2].y = 530;
    _button[2].rc = RectMake(_button[2].x, _button[2].y, 90, 26);

    _button[3].x = 910;
    _button[3].y = 720;
    _button[3].rc = RectMake(_button[3].x, _button[3].y, 90, 26);
    
    // ������ �̹���
    int temp = 0;
    for (int i = 0; i < _countof(_itemIMAGE); i++)
    {
        _itemIMAGE[i].x = 70;
        _itemIMAGE[i].y = 150 + temp;
        temp += 36;
    }

    // ���ٿ� ��ư
    temp = 0;
    for (int i = 0; i < 7; i++)
    {
        _updown[i].x = 420;
        _updown[i].y = 158+temp;
        _updown[i].rc = RectMake(_updown[i].x, _updown[i].y, 20, 26);
        _updown[i].count = 0;
        temp += 36;
    }
    temp = 0;
    for (int i = 7; i < 14; i++)
    {
        _updown[i].x = 480;
        _updown[i].y = 158 + temp;
        _updown[i].rc = RectMake(_updown[i].x, _updown[i].y, 20, 26);
        _updown[i].count = 0;
        temp += 36;
    }

    // ���ٿ� ��ư ���� ���� ��Ʈ
    temp = 0;
    for (int i = 0; i < _countof(_buyCount); i++)
    {
        _buyCount[i].x = 446;
        _buyCount[i].y = 158 + temp;
        temp += 36;
    }

#pragma endregion

#pragma region �ݺ�
    // �������� �����ϰ��ִ� ������ ���� ����
    temp = 0;
    for (int i = 0; i < _countof(_shopAmount); i++)
    {
        _shopAmount[i].x = 380;
        _shopAmount[i].y = 160+temp;
        _shopAmount[i].amount = RND->getFromIntTo(0, 5);
        temp += 36;
    }
#pragma endregion




    _dia = new Dialogue;
    _dia->init(3);


    _item = new Item;
    _item->init();




    return S_OK;
}

void WeaponShop::release(void)
{
    SAFE_DELETE(_dia);
    SAFE_DELETE(_item);
}

void WeaponShop::update(void)
{
    _dia->update();
    _item->update();

   
    if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        // �̴� ��ư
        if (PtInRect(&_button[0].rc, _ptMouse))
        {
            _button[0].click = true;
            _button[1].click = false;
        }
        else if (PtInRect(&_button[1].rc, _ptMouse))
        {
            _button[0].click = false;
            _button[1].click = true;
        }
        for (int i = 2; i < _countof(_button); i++)
        {
            if (PtInRect(&_button[i].rc, _ptMouse))
            {
                _button[i].click = true;
            }
        }
        //-------------------------------------------------------------------------

        // ���ٿ� ��ư ��ȭ + ������ ������ ���� ��ȭ
        for (int i = 0; i < _countof(_updown); i++)
        {
            if (PtInRect(&_updown[i].rc, _ptMouse))
            {
                // ���ٿ� ��ư �����Ӻ�ȭ
                _updown[i].yFrame = true;

                // ���� �� ���� ��ȭ
                if (i < 7 && _buyCount[i].count< _shopAmount[i].amount)
                    _buyCount[i].count++;
                else if (i >= 7 && _buyCount[i-7].count>0)
                    _buyCount[i - 7].count--;
            }
        }
        //-------------------------------------------------------------------------
        
    }
    else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
    {
        // �̴Ϲ�ư
        for (int i = 2; i < _countof(_button); i++)
        {
            if (PtInRect(&_button[i].rc, _ptMouse))
            {
                _button[i].click = false;
            }
        }

        // ���ٿ� ��ư ��ȭ
        for (int i = 0; i < _countof(_updown); i++)
        {
            if (PtInRect(&_updown[i].rc, _ptMouse))
            {
                _updown[i].yFrame = false;
            }
        }
    }


}

void WeaponShop::render(void)
{
    _dia->render();
    _item->render();

// �̹��� =============================================================================================
    IMAGEMANAGER->findImage("�������")->render(getMemDC());
    IMAGEMANAGER->findImage("�����������")->render(getMemDC(), 580, 80);
    IMAGEMANAGER->findImage("�������̾�α�")->render(getMemDC(), 0, 574);
    IMAGEMANAGER->findImage("���⸮��Ʈ���")->render(getMemDC(), 50, 90);
    IMAGEMANAGER->findImage("�������Ÿ��Ʋ")->render(getMemDC(), 10, 10);
    IMAGEMANAGER->findImage("���ⱸ��")->render(getMemDC(), 180, 440);
    IMAGEMANAGER->findImage("��ũ��")->alphaRender(getMemDC(), 520, 120,230);

    // ���� ���ٿ� ��ư   
    for (int i = 0; i < _countof(_updown)/2; i++)
    {
        IMAGEMANAGER->findImage("���Ʒ���ư")->frameRender(getMemDC(), _updown[i].x,_updown[i].y,0,_updown[i].yFrame);
    }
    for (int i = _countof(_updown) / 2; i < _countof(_updown); i++)
    {
        IMAGEMANAGER->findImage("���Ʒ���ư")->frameRender(getMemDC(), _updown[i].x, _updown[i].y, 1, _updown[i].yFrame);
    }

    // ����ī��Ʈ
    for (int i = 0; i <_countof(_buyCount); i++)
    {
        IMAGEMANAGER->findImage("����ī��Ʈ")->render(getMemDC(), _buyCount[i].x, _buyCount[i].y);
    }

    // ����,�Ǹ�,����, ������ ��ư
    for (int i = 0; i < _countof(_button); i++)
    {
        IMAGEMANAGER->findImage("����������ư")->frameRender(getMemDC(), _button[i].rc.left, _button[i].rc.top,_button[i].click,0);
    }

    // ������ �̹���
    for (int i = 0; i < _countof(_itemIMAGE); i++)
    {
        IMAGEMANAGER->findImage("���������")->frameRender(getMemDC(), _itemIMAGE[i].x, _itemIMAGE[i].y, 0, i);
    }

// ��Ʈ=============================================================================================
    FONTMANAGER->drawText(getMemDC(), 60, 32, 21, 255, 255, 255, "����",true, "�Ŀ��� �������");
    FONTMANAGER->drawText(getMemDC(), _button[0].rc.left+23, _button[0].rc.top+3, 17, 255, 255, 255, "����",true, "��  ��");
    FONTMANAGER->drawText(getMemDC(), _button[1].rc.left+23, _button[1].rc.top+3, 17, 255, 255, 255, "����",true, "��  ��");
    FONTMANAGER->drawText(getMemDC(), _button[2].rc.left+23, _button[2].rc.top+3, 17, 255, 255, 255, "����",true, "��  ��");
    FONTMANAGER->drawText(getMemDC(), _button[3].rc.left+18, _button[3].rc.top+3, 17, 255, 255, 255, "����",true, "E X I T");

    for (int i = 0; i < _countof(_buyCount); i++)
    {
        FONTMANAGER->drawInt(getMemDC(), _buyCount[i].x+10, _buyCount[i].y+5, 17, 255, 215, 0,
                                "����", false, (char*)_buyCount[i].count);
    }

    _dia->drawTextNoSkip(0, 15, 574, 300, 300, 25, 255, 255, 255);

    // json ������ ����
    int temp = 0;
    for (int i = 0; i < 7; i++)
    {
        _item->rendItem(i, 130, 158+temp, 18, 255, 255, 255, true);
        temp += 36;
    }
    
    // ���� ������ ���� ����
    for (int i = 0; i < _countof(_shopAmount); i++)
    {
        FONTMANAGER->drawText(getMemDC(), _shopAmount[i].x - 20, _shopAmount[i].y, 17, 255, 255, 255,
                                         "����", false, "(     )");
        FONTMANAGER->drawInt(getMemDC(), _shopAmount[i].x, _shopAmount[i].y, 17, 255, 255, 255, 
                                            "����", false, (char*)_shopAmount[i].amount);
    }

    // ����â
    FONTMANAGER->drawText(getMemDC(), 200, 450, 17, 255, 255, 255, "����", true, "�����ݾ�");
    FONTMANAGER->drawText(getMemDC(), 200, 490, 17, 255, 255, 255, "����", true, "��ǰ�Ѿ�");
    FONTMANAGER->drawText(getMemDC(), 200, 530, 17, 255, 255, 255, "����", true, "��    ��");
    FONTMANAGER->drawText(getMemDC(), 400, 450, 17, 255, 255, 255, "����", true, "Eld");
    FONTMANAGER->drawText(getMemDC(), 400, 490, 17, 255, 255, 255, "����", true, "Eld");
    FONTMANAGER->drawText(getMemDC(), 400, 530, 17, 255, 255, 255, "����", true, "Eld");

}
