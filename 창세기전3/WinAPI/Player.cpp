#include "Stdafx.h"
#include "Player.h"

HRESULT Player::init(void)
{
    _pl._x = 0;
    _pl._y = 0;
    _frame = 0;
    _pl.skill = 0;
    _atked = 0; // 피격시
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
        if (_frame > IMAGEMANAGER->findImage("살라딘_대기")->getMaxFrameX())_frame = 0;
    }
    if (_tick % 5 == 0&& _pl._state ==4)
    {
        _atked++;
        if (_frame > IMAGEMANAGER->findImage("살라딘_피격좌")->getMaxFrameX())_atked = 0;
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
    // 그림자
    IMAGEMANAGER->findImage("그림자")->alphaRender(getMemDC(), _pl._x-3, _pl._y + 10, 100);
#pragma region 상태패턴

    // state = 상태
   // view = 바라볼 곳
    switch (_pl._state)
    {
        // 대기 상태
    case 0:
        IMAGEMANAGER->findImage("살라딘_대기")->frameRender(getMemDC(), _pl._x - 20, _pl._y -60, _frame, _pl._view);
        break;
        
        // 걷기
    case 1:
        IMAGEMANAGER->findImage("살라딘_걷기")->frameRender(getMemDC(), _pl._x - 30, _pl._y -50,_frame, _pl._view);
        break;

        // 공격
    case 2:
        if (!_atkSound)
        {
            _atkSound = true;
            SOUNDMANAGER->play("살라딘공격", 0.5f);
        }
        IMAGEMANAGER->findImage("살라딘_공격")->frameRender(getMemDC(), _pl._x - 50, _pl._y - 75, _atk , _pl._view);
        break;

        // 스킬
    case 3:        
        IMAGEMANAGER->findImage("살라딘_스킬")->frameRender(getMemDC(), _pl._x-30, _pl._y - 50, _pl.skill, _pl._view);
        break;

        // 피격
    case 4:

        if (_pl._view == 1)
        {
            IMAGEMANAGER->findImage("살라딘_피격우")->frameRender(getMemDC(), _pl._x - 30, _pl._y - 50, _atked, _pl._view);
        }
        else
        {
            IMAGEMANAGER->findImage("살라딘_피격좌")->frameRender(getMemDC(), _pl._x - 30, _pl._y - 50, _atked, _pl._view);
        }

        if (_pl._state == 4 && _atked >= 12) _pl._state = 0;
        break;

    default:
        break;
    }

#pragma endregion
   
   
}
