#include "Stdafx.h"
#include "Enemy2.h"

HRESULT Enemy2::init(void)
{
    // �� �ʱ�ȭ
    _em.astar = false;
    _em.idleFrame=_em.walkFrame=_em.atkFrame = _em.x = _em.y = _em.indexX = _em.indexY = _em.state = _em.view = _em.xCount = _em.yCount = 0;
    _em.atkedFrame = 0;
    
    //��ü ƽ
    _tick = 0;



    return S_OK;
}

void Enemy2::release(void)
{
}

void Enemy2::update(void)
{
    // ��ü ƽ
    _tick++;

    if (_em.state != 2) _em.atkFrame = 0;

    switch (_em.state)
    {
    case 0: // ���
        if (_tick % 12 == 0)_em.idleFrame++;
        if (_em.idleFrame > IMAGEMANAGER->findImage("��2_���")->getMaxFrameX())_em.idleFrame = 0;
        break;

    case 1: // �ȱ�
        if (_tick % 8 == 0)_em.walkFrame++;
        if (_em.walkFrame > IMAGEMANAGER->findImage("��2_�ȱ�")->getMaxFrameX())_em.walkFrame = 0;
        break;

    case 2: // ����
        if (!SOUNDMANAGER->isPlaySound("��2����") && _em.atkFrame == 0)SOUNDMANAGER->play("��2����", 1.0f);
        if (_tick % 10 == 0)_em.atkFrame++;
        if (_em.atkFrame > IMAGEMANAGER->findImage("��2_����")->getMaxFrameX())
        {
            _em.atkFrame = 0;
            _em.state = 0;
        }
        break;

    case 3: // �ǰ�
        if (_tick % 5 == 0) _em.atkedFrame++;
        if(_em.atkedFrame>IMAGEMANAGER->findImage("��2_�ǰ�")->getMaxFrameX())
        {
            _em.atkedFrame = 0;
            _em.state = 0;
        }


        break;

    default:
        break;
    }


}

void Enemy2::render(void)
{
    IMAGEMANAGER->findImage("�׸���")->alphaRender(getMemDC(), _em.x-5, _em.y+10, 100);
    switch (_em.state)
    {
    case 0: // ���
        IMAGEMANAGER->findImage("��2_���")->frameRender(getMemDC(), _em.x-25, _em.y-43, _em.idleFrame, _em.view);
        break;

    case 1: // �ȱ�
        IMAGEMANAGER->findImage("��2_�ȱ�")->frameRender(getMemDC(), _em.x-25, _em.y-63, _em.walkFrame, _em.view);
        break;
        
    case 2: // ����
        IMAGEMANAGER->findImage("��2_����")->frameRender(getMemDC(), _em.x-47, _em.y-74, _em.atkFrame, _em.view);
        break;

    case 3: //�ǰ�
        IMAGEMANAGER->findImage("��2_�ǰ�")->frameRender(getMemDC(), _em.x - 25, _em.y - 43, _em.atkedFrame, _em.view);

        break;
    default:
        break;
    }












}
