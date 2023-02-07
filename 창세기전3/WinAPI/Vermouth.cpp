#include "Stdafx.h"
#include "Vermouth.h"

HRESULT Vermouth::init(void)
{
    _ve._x = 0;
    _ve._y = 0;
    _ve.frame = 0;
    _ve._xCount = _ve._yCount = 0;

	return S_OK;
}

void Vermouth::release(void)
{
}

void Vermouth::update(void)
{

    _ve.tick++;
    if (_ve.tick % 13 == 0)
    {
        if (_ve._state == 0)
        {
            _ve.frame++;
            if (_ve.frame > 3)  _ve.frame = 0;
        }
        else
        {
            _ve.frame++;
            if (_ve.frame > 6)  _ve.frame = 0;
        }
       
    }

    if (_ve.tick % 7 == 0 && _ve._state==3)
    {
        _atked++;
        if (_atked > 12)
        {
            _atked = 0;
            _ve._state = 0;
        }
    }

}

void Vermouth::render(void)
{

    // �׸���
    IMAGEMANAGER->findImage("�׸���")->alphaRender(getMemDC(), _ve._x-5, _ve._y + 15, 100);
#pragma region ��������

    // state = ����
   // view = �ٶ� ��
    switch (_ve._state)
    {
        // ��� ����
    case 0:
        IMAGEMANAGER->findImage("����Ʈ_���")->frameRender(getMemDC(), _ve._x-25, _ve._y-50, _ve.frame, _ve._view);
        break;

        // �ȱ�
    case 1:
        IMAGEMANAGER->findImage("����Ʈ_�ȱ�")->frameRender(getMemDC(), _ve._x-50, _ve._y-50, _ve.frame, _ve._view);
        break;

        // ����
    case 2:
        IMAGEMANAGER->findImage("����Ʈ_����")->frameRender(getMemDC(), _ve._x-55, _ve._y-85, _ve.frame, _ve._view);
        if (_ve._state == 2 && _ve.frame >=6)  _ve._state = 0;
        break;

        // �ǰ�
    case 3:
        
        IMAGEMANAGER->findImage("����Ʈ_�ǰ�")->frameRender(getMemDC(), _ve._x +10, _ve._y-30, _atked, _ve._view);
        break;

    default:
        break;
    }

#pragma endregion

}
