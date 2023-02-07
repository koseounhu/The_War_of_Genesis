#include "Stdafx.h"
#include "WorldMap.h"

HRESULT WorldMap::init(void)
{

    _tick = _loopX = _loopY = 0;
    _pointFrame=_bgX= _bgY = 0;
    _selectFrame = 0;
    _profileFrame = 0;
    _alpha = 0;
    _point = RectMakeCenter(465, 337, IMAGEMANAGER->findImage("월드맵거점")->getFrameWidth(), IMAGEMANAGER->findImage("월드맵거점")->getFrameHeight());
    
    int temp = 0;
    for (int i = 0; i < 4; i++)
    {
        _buttonNum[i] = 0;
        _button[i] = RectMake(830, 123 + temp, IMAGEMANAGER->findImage("월드맵버튼")->getFrameWidth(), IMAGEMANAGER->findImage("월드맵버튼")->getFrameHeight());
        temp += IMAGEMANAGER->findImage("월드맵버튼")->getFrameHeight() + 20;
    }


    return S_OK;
}

void WorldMap::release(void)
{
}

void WorldMap::update(void)
{
    
#pragma region 카메라 제어


    if (_ptMouse.y < 50 && _bgY < 0)
    {
        _bgY += 3;
        _point.top += 3;
        _point.bottom += 3;
    }
    else if (_ptMouse.y > WINSIZE_Y - 50 && _bgY > -315)
    {
        _bgY -= 3;
        _point.top -= 3;
        _point.bottom -= 3;
    }
    else if (_ptMouse.x < 50 && _bgX < 0)
    {
        _bgX += 3;
        _point.left += 3;
        _point.right += 3;

    }
    else if (_ptMouse.x > WINSIZE_X - 50 && _bgX > -420)
    {
        _bgX -= 3;
        _point.left -= 3;
        _point.right -= 3;
    }
#pragma endregion
#pragma region 1틱 당

    _tick++;
    if (_tick % 10 == 0)
    {
       
        _loopX++;
        _loopY--;
        _pointFrame++;
        if (_pointFrame > IMAGEMANAGER->findImage("월드맵거점")->getMaxFrameX())_pointFrame = 0;
        if (_selectFrame > 25)_selectFrame = 0;
        _profileFrame++;
        if (_profileFrame > 5)_profileFrame = 0;
    }
    if (_tick % 5 == 0)
    {
      
        _selectFrame++;
    }
    if(_move||_move2) _alpha++;
#pragma endregion
    for (int i = 0; i < 4; i++)
    {
        if (PtInRect(&_button[i], _ptMouse))
        {
            _buttonNum[i] = 1;
        }
        else
        {
            _buttonNum[i] = 0;
        }

        // UI 판정
        if (PtInRect(&_button[3], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) SCENEMANAGER->changScene("오프닝");
        if (PtInRect(&_button[i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _ui = true;
    }
  

}

void WorldMap::render(void)
{

    RECT _rc;
    _rc = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->findImage("월드맵파도")->loopRender(getMemDC(), &_rc, _loopX, _loopY);
    IMAGEMANAGER->findImage("월드맵배경")->render(getMemDC(),_bgX,_bgY);
    IMAGEMANAGER->findImage("월드맵거점")->alphaFrameRender(getMemDC(), _point.left, _point.top, 150,_pointFrame, 0);
    IMAGEMANAGER->findImage("월드맵거점마크")->alphaRender(getMemDC(), _point.left+30, _point.top+20,150);

    RECT _Profile;
    _Profile = RectMake(_point.right, _point.top - 100, 100, 100);

    RECT _warPoint;
    _warPoint = RectMake(_point.left + 535, _point.top + 160, 100, 100);
    if (_ui && PtInRect(&_warPoint, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _move = true;
        _selectPoint = 1;
    }

    if (_alpha > 250)
    {
        _selectPoint = 2;
    }
    RECT temp;
    temp = RectMake(_point.left + 535, _point.top + 160, 100, 100);

    RECT tempA;
    tempA = RectMake(_point.left + 230, _point.top + 500, 100, 100);

    if (PtInRect(&temp, _ptMouse))
    {
        IMAGEMANAGER->findImage("월드맵선택")->alphaFrameRender(getMemDC(), temp.left, temp.top, 140, _selectFrame, 0);
        HPEN hpen;
        HPEN oldpen;

        hpen = CreatePen(PS_SOLID, 5, RGB(92, 106, 215));
        oldpen = (HPEN)::SelectObject(getMemDC(), hpen);
        LineMake(getMemDC(), _point.left + (_point.right - _point.left) / 2, _point.top + (_point.top - _point.bottom) / 2 + 150, _point.left + 550, _point.top + 185);
        SelectObject(getMemDC(), oldpen);
        DeleteObject(hpen);
    }
    else if (PtInRect(&tempA, _ptMouse))
    {
        IMAGEMANAGER->findImage("월드맵선택")->alphaFrameRender(getMemDC(), tempA.left + 20, tempA.top + 20, 140, _selectFrame, 0);
        HPEN hpen;
        HPEN oldpen;

        hpen = CreatePen(PS_SOLID, 5, RGB(92, 106, 215));
        oldpen = (HPEN)::SelectObject(getMemDC(), hpen);
        LineMake(getMemDC(), temp.left + 30, temp.bottom - 50, _point.left + 290, _point.top + 500);
        SelectObject(getMemDC(), oldpen);
        DeleteObject(hpen);
    }
    if (_ui && PtInRect(&tempA, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _move2 = true;
        _selectPoint = 3;
    }
    if (_selectPoint == 0)
    {
        IMAGEMANAGER->findImage("월드맵프로필")->frameRender(getMemDC(), _Profile.left, _Profile.top, _profileFrame, 0);
        FONTMANAGER->drawText(getMemDC(), _Profile.left + 110, _Profile.top + 30, 15, 255, 255, 255, "굴림", true, "1 팀");

        IMAGEMANAGER->findImage("월드맵전투마크")->render(getMemDC(), temp.left, temp.top);
    }
    else if (_selectPoint == 1)
    {
        IMAGEMANAGER->findImage("월드맵프로필")->frameRender(getMemDC(), temp.left+50, temp.top-150, _profileFrame, 0);
        FONTMANAGER->drawText(getMemDC(), temp.left + 160, temp.top -120, 15, 255, 255, 255, "굴림", true, "1 팀");
        IMAGEMANAGER->findImage("월드맵전투마크")->render(getMemDC(), temp.left, temp.top);

    }
    else if (_selectPoint == 2)
    {
        IMAGEMANAGER->findImage("월드맵프로필")->frameRender(getMemDC(), temp.left + 50, temp.top - 150, _profileFrame, 0);
        FONTMANAGER->drawText(getMemDC(), temp.left + 160, temp.top - 120, 15, 255, 255, 255, "굴림", true, "1 팀");

        IMAGEMANAGER->findImage("월드맵전투마크")->render(getMemDC(), tempA.left, tempA.top);
    }
    else if (_selectPoint == 3)
    {
        IMAGEMANAGER->findImage("월드맵프로필")->frameRender(getMemDC(), tempA.left + 50, tempA.top - 150, _profileFrame, 0);
        FONTMANAGER->drawText(getMemDC(), tempA.left + 160, tempA.top - 120, 15, 255, 255, 255, "굴림", true, "1 팀");

        IMAGEMANAGER->findImage("월드맵전투마크")->render(getMemDC(), tempA.left, tempA.top);
    }


    IMAGEMANAGER->findImage("월드맵지역")->render(getMemDC(),0,0);
    FONTMANAGER->drawText(getMemDC(), 40, 35, 20, 255, 255, 255, "굴림체", true, "시지아");
    FONTMANAGER->drawText(getMemDC(), 140, 80, 15, 255, 255, 255, "굴림체", false, "655년 180일");

    // 우측 버튼 UI
    if (!_ui)
    {
        for (int i = 0; i < 4; i++)
        {
            if (i == 2)continue;
            IMAGEMANAGER->findImage("월드맵버튼")->frameRender(getMemDC(), _button[i].left, _button[i].top, _buttonNum[i], 0);
        }
        FONTMANAGER->drawText(getMemDC(), _button[0].left + 50, _button[0].top + 10, 25, 255, 255, 255, "굴림", true, "이 동");
        FONTMANAGER->drawText(getMemDC(), _button[1].left + 50, _button[1].top + 10, 25, 255, 255, 255, "굴림", true, "진 입");
        FONTMANAGER->drawText(getMemDC(), _button[3].left + 30, _button[3].top + 10, 25, 255, 255, 255, "굴림", true, "메인화면");
    }




    //씬전환
    if (_move)
    {
        IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), _alpha);
        if (_alpha > 250)
        {
            _ui = false;
            _move = false;
            SCENEMANAGER->changScene("시나리오컷씬");
        }
    }
    else if (_move2)
    {
        IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), _alpha);
        if (_alpha > 250)
        {
            _ui = false;
            _move2 = false;
            SCENEMANAGER->changScene("전투");
        }
    }

}
