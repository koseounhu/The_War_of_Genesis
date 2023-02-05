#include "Stdafx.h"
#include "Vermouth.h"

HRESULT Vermouth::init(void)
{
    _ve._x = 0;
    _ve._y = 0;
    _ve.frame = 0;
    _ve.skill = 0;


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
        _ve.frame++;
        if (_ve.frame > IMAGEMANAGER->findImage("����_���")->getMaxFrameX())_ve.frame = 0;
    }


	if(KEYMANAGER->isOnceKeyDown('I'))
    _ve._state = 0;
    if (KEYMANAGER->isOnceKeyDown('J'))
        _ve._state = 1;

    if (KEYMANAGER->isOnceKeyDown('K'))
        _ve._state = 2;



}

void Vermouth::render(void)
{

    // �׸���
    IMAGEMANAGER->findImage("�׸���")->alphaRender(getMemDC(), _ve._x - 3, _ve._y + 10, 100);
#pragma region ��������

    // state = ����
   // view = �ٶ� ��
    switch (_ve._state)
    {
        // ��� ����
    case 0:
        IMAGEMANAGER->findImage("����Ʈ_���")->frameRender(getMemDC(), _ve._x - 20, _ve._y - 60, _ve.frame, _ve._view);
        break;

        // �ȱ�
    case 1:
        IMAGEMANAGER->findImage("����Ʈ_�ȱ�")->frameRender(getMemDC(), _ve._x - 30, _ve._y - 50, _ve.frame, _ve._view);
        break;

        // ����
    case 2:
        IMAGEMANAGER->findImage("����Ʈ_����")->frameRender(getMemDC(), _ve._x - 50, _ve._y - 75, _ve.frame, _ve._view);
        break;

    default:
        break;
    }

#pragma endregion

}
