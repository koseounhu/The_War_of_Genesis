#include "Stdafx.h"
#include "WorldMap.h"

HRESULT WorldMap::init(void)
{
    _tick = _loopX = _loopY = 0;
    _pointFrame=_bgX= _bgY = 0;
    _selectFrame = 0;
    _profileFrame = 0;
    _alpha = 0;
    _point = RectMakeCenter(465, 337, IMAGEMANAGER->findImage("����ʰ���")->getFrameWidth(), IMAGEMANAGER->findImage("����ʰ���")->getFrameHeight());
    
    int temp = 0;
    for (int i = 0; i < 4; i++)
    {
        _buttonNum[i] = 0;
        _button[i] = RectMake(830, 123 + temp, IMAGEMANAGER->findImage("����ʹ�ư")->getFrameWidth(), IMAGEMANAGER->findImage("����ʹ�ư")->getFrameHeight());
        temp += IMAGEMANAGER->findImage("����ʹ�ư")->getFrameHeight() + 20;
    }


    return S_OK;
}

void WorldMap::release(void)
{
}

void WorldMap::update(void)
{
    
#pragma region ī�޶� ����


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
#pragma region 1ƽ ��

    _tick++;
    if (_tick % 10 == 0)
    {
       
        _loopX++;
        _loopY--;
        _pointFrame++;
        if (_pointFrame > IMAGEMANAGER->findImage("����ʰ���")->getMaxFrameX())_pointFrame = 0;
        if (_selectFrame > 25)_selectFrame = 0;
        _profileFrame++;
        if (_profileFrame > 5)_profileFrame = 0;
    }
    if (_tick % 5 == 0)
    {
      
        _selectFrame++;
    }
    if(_move) _alpha++;
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

        // UI ����
        if (PtInRect(&_button[3], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) SCENEMANAGER->changScene("������");
        if (PtInRect(&_button[i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _ui = true;
    }
  

}

void WorldMap::render(void)
{
    RECT _rc;
    _rc = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->findImage("������ĵ�")->loopRender(getMemDC(), &_rc, _loopX, _loopY);
    IMAGEMANAGER->findImage("����ʹ��")->render(getMemDC(),_bgX,_bgY);
    IMAGEMANAGER->findImage("����ʰ���")->alphaFrameRender(getMemDC(), _point.left, _point.top, 150,_pointFrame, 0);
    IMAGEMANAGER->findImage("����ʰ�����ũ")->alphaRender(getMemDC(), _point.left+30, _point.top+20,150);

    RECT _Profile;
    _Profile = RectMake(_point.right, _point.top - 100, 100, 100);

    RECT _warPoint;
    _warPoint = RectMake(_point.left + 535, _point.top + 160, 100, 100);
    if (_ui && PtInRect(&_warPoint, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
    {
        _move = true;
    }


    //else 
    IMAGEMANAGER->findImage("�����������")->frameRender(getMemDC(),_Profile.left,_Profile.top, _profileFrame,0);
    FONTMANAGER->drawText(getMemDC(), _Profile.left + 110, _Profile.top+30, 15, 255, 255, 255, "����",true, "1 ��");


    RECT temp;
    temp = RectMake(_point.left + 535, _point.top + 160, 100, 100);
    IMAGEMANAGER->findImage("�����������ũ")->render(getMemDC(), _point.left+535, _point.top+160);

    IMAGEMANAGER->findImage("���������")->render(getMemDC(),0,0);
    FONTMANAGER->drawText(getMemDC(), 40, 35, 20, 255, 255, 255, "����ü", true, "������");
    FONTMANAGER->drawText(getMemDC(), 140, 80, 15, 255, 255, 255, "����ü", false, "655�� 180��");

    // ���� ��ư UI
    if (!_ui)
    {
        for (int i = 0; i < 4; i++)
        {
            IMAGEMANAGER->findImage("����ʹ�ư")->frameRender(getMemDC(), _button[i].left, _button[i].top, _buttonNum[i], 0);
        }
        FONTMANAGER->drawText(getMemDC(), _button[0].left + 50, _button[0].top + 10, 25, 255, 255, 255, "����", true, "�� ��");
        FONTMANAGER->drawText(getMemDC(), _button[1].left + 50, _button[1].top + 10, 25, 255, 255, 255, "����", true, "�� ��");
        FONTMANAGER->drawText(getMemDC(), _button[3].left + 30, _button[3].top + 10, 25, 255, 255, 255, "����", true, "����ȭ��");
    }


    if (PtInRect(&temp, _ptMouse))
    {
        IMAGEMANAGER->findImage("����ʼ���")->alphaFrameRender(getMemDC(), temp.left, temp.top, 140, _selectFrame, 0);

        HPEN hpen;
        HPEN oldpen;

        hpen = CreatePen(PS_SOLID, 5, RGB(92, 106, 215));
        oldpen = (HPEN)::SelectObject(getMemDC(), hpen);
        LineMake(getMemDC(), _point.left + (_point.right-_point.left)/2, _point.top+(_point.top-_point.bottom)/2+150, _point.left + 550, _point.top + 185);
        SelectObject(getMemDC(), oldpen);
        DeleteObject(hpen);
    }


    //����ȯ
    if (_move)
    {
        IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _alpha);
        if (_alpha > 250)SCENEMANAGER->changScene("�ó������ƾ�");
    }

}
