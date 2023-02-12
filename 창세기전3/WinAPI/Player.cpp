#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    _pl._x = 0;
    _pl._y = 0;
    _frame = 0;
    _pl.skill = 0;
    _atked = 0; // �ǰݽ�
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
    if (_tick % 5 == 0&& _pl._state ==4)
    {
        _atked++;
        if (_frame > IMAGEMANAGER->findImage("����_�ǰ���")->getMaxFrameX())_atked = 0;
    }
    else if (_pl._state !=4)
    {
        _atked = 0;
    }
    if (_tick % 15 == 0 && _pl._state == 2)
    {
        _atk++;
        if (_atk > 5)
        {
            _atk = 0;
            _pl._state=0;
            _atkSound = false;
        }
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
        if (!_atkSound)
        {
            _atkSound = true;
            SOUNDMANAGER->play("�������", 0.5f);
        }
        IMAGEMANAGER->findImage("����_����")->frameRender(getMemDC(), _pl._x - 50, _pl._y - 75, _atk , _pl._view);
        break;

        // ��ų
    case 3:        
        IMAGEMANAGER->findImage("����_��ų")->frameRender(getMemDC(), _pl._x-30, _pl._y - 50, _pl.skill, _pl._view);
        break;

        // �ǰ�
    case 4:

        if (_pl._view == 1)
        {
            IMAGEMANAGER->findImage("����_�ǰݿ�")->frameRender(getMemDC(), _pl._x - 30, _pl._y - 50, _atked, _pl._view);
        }
        else
        {
            IMAGEMANAGER->findImage("����_�ǰ���")->frameRender(getMemDC(), _pl._x - 30, _pl._y - 50, _atked, _pl._view);
        }

        if (_pl._state == 4 && _atked >= 12) _pl._state = 0;
        break;

    default:
        break;
    }

#pragma endregion
   
   
}
