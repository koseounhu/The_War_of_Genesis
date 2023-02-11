#include "Stdafx.h"
#include "Openning.h"

HRESULT Openning::init(void)
{
    // ������ ��� ���� �ʱ�ȭ
    _BGalpha = 0;

    // �Ҳ� �ʱ�ȭ
    _fireAlpha = 0;
    _fireFame = 0;
    
    // ƽ
    _count = 0;

    //�ؽ�Ʈ x������
    _textFrame = 0;

    // �ؽ�Ʈ �̹��� ���� �ʱ�ȭ
    _textImage.reset();
    _textImage.set(1,1);

    int _Height=0;
    // ����â ������ ���� ��Ʈ �ʱ�ȭ
    for (int i = 1; i < 5; i++)
    {
        _rc[i] = RectMake(280, 500+ _Height, IMAGEMANAGER->findImage("�����׼���â1")->getFrameWidth(), IMAGEMANAGER->findImage("�����׼���â1")->getFrameHeight());
        _Height += IMAGEMANAGER->findImage("�����׼���â1")->getFrameHeight();
    }

    // �ӽ� ��� ��Ʈ
    _rc[0] = RectMakeCenter(500, 410, 10,10);


    SOUNDMANAGER->play("���ӽ���", 1.0f);

    return S_OK;
}

void Openning::release(void)
{}

void Openning::update(void)
{
    _count++;
    if (_count % 5 == 0)
    {
        // ���
        if (_BGalpha < 255)_BGalpha++;

        // ��� �ؽ�Ʈ
        if (_textFrame < IMAGEMANAGER->findImage("�����ױ۾�1")->getMaxFrameX() && _textImage[6] ==0)
        {
            _textFrame++;
        }

        // �Ҳ� ������
        if (_textImage[6] == 1)
        {
            _textFrame++;
            if (_textFrame > IMAGEMANAGER->findImage("�����׺Ҳ�")->getMaxFrameX()) _textFrame = 0;
        }
    }
    //�Ҳ� ��������
    if (!_fire)
    {
        _fireAlpha++;

        if (_fireAlpha == 255)
        {
            _fire = true;
        }
    }
    else
    {
        _fireAlpha--;
        if (_fireAlpha < 100)_fire = false;
    }
       
      
    
}

void Openning::render(void)
{
    IMAGEMANAGER->findImage("�����׹��")->alphaRender(getMemDC(), _BGalpha);

    if (_textImage[1] == 1)
    {
        IMAGEMANAGER->findImage("�����ױ۾�1")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("�����ױ۾�1")->getMaxFrameX())
        {
           _textFrame = 0;
           _textImage.reset();
            _textImage.set(2, 1);
        }
    }
    else if (_textImage[2] == 1)
    {
       IMAGEMANAGER->findImage("�����ױ۾�2")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
       if (_textFrame == IMAGEMANAGER->findImage("�����ױ۾�1")->getMaxFrameX())
       {
           _textFrame = 0;
           _textImage.reset();
           _textImage.set(3, 1);
       }
    }
    else if (_textImage[3] == 1)
    {
        IMAGEMANAGER->findImage("�����ױ۾�3")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("�����ױ۾�1")->getMaxFrameX())
        {
            _textFrame = 0;
            _textImage.reset();
            _textImage.set(4, 1);
        }
    }
    else if (_textImage[4] == 1)
    {
        IMAGEMANAGER->findImage("�����ױ۾�4")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("�����ױ۾�1")->getMaxFrameX())
        {
            _textFrame = 0;
            _textImage.reset();
            _textImage.set(5, 1);
        }
    }
    else if (_textImage[5] == 1)
    {
        IMAGEMANAGER->findImage("�����ױ۾�5")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("�����ױ۾�1")->getMaxFrameX())
        {
            _textFrame = 0;
            _textImage.reset();
            _textImage.set(6, 1);
        }
    }
    // ������ �����°� ������ ���ӽ���ȭ��
    else if (_textImage[6] == 1)
    {
        IMAGEMANAGER->findImage("�����׺Ҳ�")->alphaFrameRender(getMemDC(), 350, 270, _fireAlpha, _textFrame, 0);

        IMAGEMANAGER->findImage("�����׷ΰ�")->render(getMemDC(), 80,200);
        IMAGEMANAGER->findImage("�����׼���â1")->render(getMemDC(), 280, 500);


        // ����â ���콺 �浹 �� ��ȭ
        if (PtInRect(&_rc[1], _ptMouse))
        {
            IMAGEMANAGER->findImage("�����׼���â2")->frameRender(getMemDC(), _rc[1].left, _rc[1].top, 0, 0);
            if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
                SOUNDMANAGER->play("���μ���", 1.0f);
                _next = true;
            }
        }
        else if (PtInRect(&_rc[2], _ptMouse))
        {
            IMAGEMANAGER->findImage("�����׼���â2")->frameRender(getMemDC(), _rc[2].left, _rc[2].top, 0, 1);
        }
        else if (PtInRect(&_rc[3], _ptMouse))
        {
            IMAGEMANAGER->findImage("�����׼���â2")->frameRender(getMemDC(), _rc[3].left, _rc[3].top, 0, 2);
        }
        else if (PtInRect(&_rc[4], _ptMouse))
        {
            IMAGEMANAGER->findImage("�����׼���â2")->frameRender(getMemDC(), _rc[4].left, _rc[4].top, 0, 3);
        }
    }

    if (_next)
    {
        _nextAlpha+=5;
        IMAGEMANAGER->findImage("��������")->alphaRender(getMemDC(), _nextAlpha);
        if(_nextAlpha>250) SCENEMANAGER->changScene("�ε�","�ó�����");
    }
}
