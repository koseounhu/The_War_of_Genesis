#include "Stdafx.h"
#include "Enemy2.h"

HRESULT Enemy2::init(void)
{
    // 적 초기화
    _em.astar = false;
    _em.idleFrame=_em.walkFrame=_em.atkFrame = _em.x = _em.y = _em.indexX = _em.indexY = _em.state = _em.view = _em.xCount = _em.yCount = 0;

    //전체 틱
    _tick = 0;



    return S_OK;
}

void Enemy2::release(void)
{
}

void Enemy2::update(void)
{
    // 전체 틱
    _tick++;

    // 공격상태
    if(!_em.isAtk)  _em.atkFrame = 0;


    switch (_em.state)
    {
    case 0: // 대기
        if (_tick % 12 == 0)_em.idleFrame++;
        if (_em.idleFrame > IMAGEMANAGER->findImage("적2_대기")->getMaxFrameX())_em.idleFrame = 0;
        break;

    case 1: // 걷기
        if (_tick % 8 == 0)_em.walkFrame++;
        if (_em.walkFrame > IMAGEMANAGER->findImage("적2_걷기")->getMaxFrameX())_em.walkFrame = 0;
        break;

    case 2: // 공격
        _em.isAtk = true;
        if (_tick % 15 == 0)_em.atkFrame++;
        if (_em.atkFrame >= IMAGEMANAGER->findImage("적2_공격")->getMaxFrameX())
        {
            _em.isAtk = false;
            _em.state = 0;
        }
        break;

    default:
        break;
    }


}

void Enemy2::render(void)
{
    IMAGEMANAGER->findImage("그림자")->alphaRender(getMemDC(), _em.x-5, _em.y+10, 100);
    switch (_em.state)
    {
    case 0: // 대기
        IMAGEMANAGER->findImage("적2_대기")->frameRender(getMemDC(), _em.x-25, _em.y-43, _em.idleFrame, _em.view);
        break;

    case 1: // 걷기
        IMAGEMANAGER->findImage("적2_걷기")->frameRender(getMemDC(), _em.x-25, _em.y-63, _em.walkFrame, _em.view);
        break;
        
    case 2: // 공격
        IMAGEMANAGER->findImage("적2_공격")->frameRender(getMemDC(), _em.x-47, _em.y-74, _em.atkFrame, _em.view);
        break;

    default:
        break;
    }












}
