#include "Stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init(void)
{
    _tick = _enemyFrame=  _enemyX = _enemyY = 0;

    return S_OK;
}

void Enemy::release(void)
{
}

void Enemy::update(void)
{
    _tick++;
    if(_tick%10==0)  _enemyFrame++;
    if (_enemyFrame > 3)_enemyFrame = 0;
}

void Enemy::render(float x, float y, int state)
{
    _enemyX = x;
    _enemyY = y;
    IMAGEMANAGER->findImage("그림자")->alphaRender(getMemDC(), x+15, y+60, 100);
    IMAGEMANAGER->findImage("적1")->frameRender(getMemDC(), x, y, _enemyFrame,state);
}
