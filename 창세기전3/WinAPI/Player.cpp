#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    _pl._x = 0;
    _pl._y = 0;
    _frame = 0;
    _pl.skill = 0;

    return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
    _tick++;
    if (_tick % 13 == 0)
    {
        _frame++;
        if (_frame > IMAGEMANAGER->findImage("����_���")->getMaxFrameX())_frame = 0;
    }
   
}

void Player::render(void)
{
    // �׸���
    IMAGEMANAGER->findImage("�׸���")->alphaRender(getMemDC(), _pl._x-3, _pl._y + 10, 100);
#pragma region ��������

    // state = ����
   // view = �ٶ� ��

    switch (_pl._state)
    {
        // ��� ����
    case 0:
        IMAGEMANAGER->findImage("����_���")->frameRender(getMemDC(), _pl._x - 20, _pl._y -60, _frame, _pl._view);
        break;
        
        // �ȱ�
    case 1:
        IMAGEMANAGER->findImage("����_�ȱ�")->frameRender(getMemDC(), _pl._x - 30, _pl._y -50,_frame, _pl._view);
        break;

        // ����
    case 2:
        IMAGEMANAGER->findImage("����_����")->frameRender(getMemDC(), _pl._x - 50, _pl._y-75, _frame, _pl._view);
        break;

        // ��ų
    case 3:        
        IMAGEMANAGER->findImage("����_��ų")->frameRender(getMemDC(), _pl._x-30, _pl._y - 50, _pl.skill, _pl._view);
        break;
    default:
        break;
    }

#pragma endregion
   
   
}
