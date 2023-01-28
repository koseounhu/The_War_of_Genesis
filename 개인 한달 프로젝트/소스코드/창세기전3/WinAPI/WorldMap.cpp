#include "Stdafx.h"
#include "WorldMap.h"

HRESULT WorldMap::init(void)
{
    _tick = _loopX = _loopY = 0;
    _bgX= _bgY = 0;

    return S_OK;
}

void WorldMap::release(void)
{

}

void WorldMap::update(void)
{

    if (_ptMouse.y < 50 && _bgY < 0)_bgY += 3;
    else if (_ptMouse.y > WINSIZE_Y - 50 && _bgY > -315)_bgY -= 3;
    else if (_ptMouse.x < 50 && _bgX<0)_bgX += 3;
    else if (_ptMouse.x > WINSIZE_X - 50&& _bgX >-420)_bgX -= 3;



    _tick++;
    if (_tick % 10 == 0)
    {
        _loopX++;
        _loopY--;
    }
}

void WorldMap::render(void)
{
    RECT _rc;
    _rc = RectMake(0, 0, WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->findImage("¿ùµå¸ÊÆÄµµ")->loopRender(getMemDC(), &_rc, _loopX, _loopY);
    IMAGEMANAGER->findImage("¿ùµå¸Ê¹è°æ")->render(getMemDC(),_bgX,_bgY);
    IMAGEMANAGER->findImage("¿ùµå¸ÊÁö¿ª")->render(getMemDC(),0,0);
    IMAGEMANAGER->findImage("¿ùµå¸Ê¹öÆ°")->frameRender(getMemDC(), WINSIZE_X - 170, WINSIZE_Y / 2, 0, 0);



    IMAGEMANAGER->findImage("¿ùµå¸Ê°ÅÁ¡")->frameRender(getMemDC(), WINSIZE_X/2, WINSIZE_Y / 2, 0, 0);


    
}
