#include "Stdafx.h"
#include "WeaponShop.h"

HRESULT WeaponShop::init(void)
{
#pragma region 좌표 설정
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
    
    // 아이템 이미지
    int temp = 0;
    for (int i = 0; i < _countof(_itemIMAGE); i++)
    {
        _itemIMAGE[i].x = 70;
        _itemIMAGE[i].y = 150 + temp;
        temp += 36;
    }

    // 업다운 버튼
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

    // 업다운 버튼 사이 수량 렉트
    temp = 0;
    for (int i = 0; i < _countof(_buyCount); i++)
    {
        _buyCount[i].x = 446;
        _buyCount[i].y = 158 + temp;
        temp += 36;
    }

#pragma endregion

#pragma region 반복
    // 상점에서 보유하고있는 아이템 랜덤 갯수
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
        // 미니 버튼
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

        // 업다운 버튼 변화 + 구매할 아이템 수량 변화
        for (int i = 0; i < _countof(_updown); i++)
        {
            if (PtInRect(&_updown[i].rc, _ptMouse))
            {
                // 업다운 버튼 프레임변화
                _updown[i].yFrame = true;

                // 구매 할 수량 변화
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
        // 미니버튼
        for (int i = 2; i < _countof(_button); i++)
        {
            if (PtInRect(&_button[i].rc, _ptMouse))
            {
                _button[i].click = false;
            }
        }

        // 업다운 버튼 변화
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

// 이미지 =============================================================================================
    IMAGEMANAGER->findImage("상점배경")->render(getMemDC());
    IMAGEMANAGER->findImage("무기상점여자")->render(getMemDC(), 580, 80);
    IMAGEMANAGER->findImage("상점다이얼로그")->render(getMemDC(), 0, 574);
    IMAGEMANAGER->findImage("무기리스트배경")->render(getMemDC(), 50, 90);
    IMAGEMANAGER->findImage("무기상점타이틀")->render(getMemDC(), 10, 10);
    IMAGEMANAGER->findImage("무기구매")->render(getMemDC(), 180, 440);
    IMAGEMANAGER->findImage("스크롤")->alphaRender(getMemDC(), 520, 120,230);

    // 수량 업다운 버튼   
    for (int i = 0; i < _countof(_updown)/2; i++)
    {
        IMAGEMANAGER->findImage("위아래버튼")->frameRender(getMemDC(), _updown[i].x,_updown[i].y,0,_updown[i].yFrame);
    }
    for (int i = _countof(_updown) / 2; i < _countof(_updown); i++)
    {
        IMAGEMANAGER->findImage("위아래버튼")->frameRender(getMemDC(), _updown[i].x, _updown[i].y, 1, _updown[i].yFrame);
    }

    // 구매카운트
    for (int i = 0; i <_countof(_buyCount); i++)
    {
        IMAGEMANAGER->findImage("구매카운트")->render(getMemDC(), _buyCount[i].x, _buyCount[i].y);
    }

    // 구입,판매,결정, 나가기 버튼
    for (int i = 0; i < _countof(_button); i++)
    {
        IMAGEMANAGER->findImage("상점작은버튼")->frameRender(getMemDC(), _button[i].rc.left, _button[i].rc.top,_button[i].click,0);
    }

    // 아이템 이미지
    for (int i = 0; i < _countof(_itemIMAGE); i++)
    {
        IMAGEMANAGER->findImage("무기아이콘")->frameRender(getMemDC(), _itemIMAGE[i].x, _itemIMAGE[i].y, 0, i);
    }

// 폰트=============================================================================================
    FONTMANAGER->drawText(getMemDC(), 60, 32, 21, 255, 255, 255, "굴림",true, "파워드 무기상점");
    FONTMANAGER->drawText(getMemDC(), _button[0].rc.left+23, _button[0].rc.top+3, 17, 255, 255, 255, "굴림",true, "구  입");
    FONTMANAGER->drawText(getMemDC(), _button[1].rc.left+23, _button[1].rc.top+3, 17, 255, 255, 255, "굴림",true, "판  매");
    FONTMANAGER->drawText(getMemDC(), _button[2].rc.left+23, _button[2].rc.top+3, 17, 255, 255, 255, "굴림",true, "결  정");
    FONTMANAGER->drawText(getMemDC(), _button[3].rc.left+18, _button[3].rc.top+3, 17, 255, 255, 255, "굴림",true, "E X I T");

    for (int i = 0; i < _countof(_buyCount); i++)
    {
        FONTMANAGER->drawInt(getMemDC(), _buyCount[i].x+10, _buyCount[i].y+5, 17, 255, 215, 0,
                                "굴림", false, (char*)_buyCount[i].count);
    }

    _dia->drawTextNoSkip(0, 15, 574, 300, 300, 25, 255, 255, 255);

    // json 아이템 내역
    int temp = 0;
    for (int i = 0; i < 7; i++)
    {
        _item->rendItem(i, 130, 158+temp, 18, 255, 255, 255, true);
        temp += 36;
    }
    
    // 상점 아이템 보유 수량
    for (int i = 0; i < _countof(_shopAmount); i++)
    {
        FONTMANAGER->drawText(getMemDC(), _shopAmount[i].x - 20, _shopAmount[i].y, 17, 255, 255, 255,
                                         "굴림", false, "(     )");
        FONTMANAGER->drawInt(getMemDC(), _shopAmount[i].x, _shopAmount[i].y, 17, 255, 255, 255, 
                                            "굴림", false, (char*)_shopAmount[i].amount);
    }

    // 구매창
    FONTMANAGER->drawText(getMemDC(), 200, 450, 17, 255, 255, 255, "굴림", true, "소지금액");
    FONTMANAGER->drawText(getMemDC(), 200, 490, 17, 255, 255, 255, "굴림", true, "물품총액");
    FONTMANAGER->drawText(getMemDC(), 200, 530, 17, 255, 255, 255, "굴림", true, "잔    액");
    FONTMANAGER->drawText(getMemDC(), 400, 450, 17, 255, 255, 255, "굴림", true, "Eld");
    FONTMANAGER->drawText(getMemDC(), 400, 490, 17, 255, 255, 255, "굴림", true, "Eld");
    FONTMANAGER->drawText(getMemDC(), 400, 530, 17, 255, 255, 255, "굴림", true, "Eld");

}
