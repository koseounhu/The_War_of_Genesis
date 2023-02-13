#include "Stdafx.h"
#include "Enemy2.h"

HRESULT Enemy2::init(void)
{
    // �� �ʱ�ȭ
    _em.astar = false;
    _em.frame = _em.x = _em.y = _em.indexX = _em.indexY = _em.state = _em.view = _em.xCount = _em.yCount = 0;

    //��ü ƽ
    _tick = 0;



    return S_OK;
}

void Enemy2::release(void)
{
}

void Enemy2::update(void)
{
    if (_tick % 5 == 0)_em.frame++;
    if (_em.frame > 6)_em.frame = 0;



    if (KEYMANAGER->isOnceKeyDown('Q'))
        _em.state = 0;
    if(KEYMANAGER->isOnceKeyDown('W'))
        _em.state = 1;
    if(KEYMANAGER->isOnceKeyDown('E'))
        _em.state = 2;
    if(KEYMANAGER->isOnceKeyDown('R'))
        _em.view = 0;
    if(KEYMANAGER->isOnceKeyDown('A'))
        _em.view = 1;
    if(KEYMANAGER->isOnceKeyDown('S'))
        _em.view = 2;
    if(KEYMANAGER->isOnceKeyDown('D'))
        _em.view = 3;



}

void Enemy2::render(void)
{
    switch (_em.state)
    {
    case 0: // ���
        IMAGEMANAGER->findImage("��2_���")->frameRender(getMemDC(), _em.x, _em.y + 100, _em.frame, _em.view);
        break;

    case 1: // �ȱ�
        IMAGEMANAGER->findImage("��2_�ȱ�")->frameRender(getMemDC(), _em.x, _em.y + 200, _em.frame, _em.view);
        break;
        
    case 2: // ����
        IMAGEMANAGER->findImage("��2_����")->frameRender(getMemDC(), _em.x, _em.y + 300, _em.frame, _em.view);
        break;

    default:
        break;
    }












}
