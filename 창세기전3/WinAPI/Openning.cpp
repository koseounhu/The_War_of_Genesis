#include "Stdafx.h"
#include "Openning.h"

HRESULT Openning::init(void)
{
    // 오프닝 배경 알파 초기화
    _BGalpha = 0;

    // 불꽃 초기화
    _fireAlpha = 0;
    _fireFame = 0;
    
    // 틱
    _count = 0;

    //텍스트 x프레임
    _textFrame = 0;

    // 텍스트 이미지 판정 초기화
    _textImage.reset();
    _textImage.set(1,1);

    int _Height=0;
    // 선택창 판정을 위한 렉트 초기화
    for (int i = 1; i < 5; i++)
    {
        _rc[i] = RectMake(280, 500+ _Height, IMAGEMANAGER->findImage("오프닝선택창1")->getFrameWidth(), IMAGEMANAGER->findImage("오프닝선택창1")->getFrameHeight());
        _Height += IMAGEMANAGER->findImage("오프닝선택창1")->getFrameHeight();
    }

    // 임시 사용 렉트
    _rc[0] = RectMakeCenter(500, 410, 10,10);


    SOUNDMANAGER->play("게임시작", 1.0f);

    return S_OK;
}

void Openning::release(void)
{}

void Openning::update(void)
{
    _count++;
    if (_count % 5 == 0)
    {
        // 배경
        if (_BGalpha < 255)_BGalpha++;

        // 가운데 텍스트
        if (_textFrame < IMAGEMANAGER->findImage("오프닝글씨1")->getMaxFrameX() && _textImage[6] ==0)
        {
            _textFrame++;
        }

        // 불꽃 프레임
        if (_textImage[6] == 1)
        {
            _textFrame++;
            if (_textFrame > IMAGEMANAGER->findImage("오프닝불꽃")->getMaxFrameX()) _textFrame = 0;
        }
    }
    //불꽃 알파증가
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
    IMAGEMANAGER->findImage("오프닝배경")->alphaRender(getMemDC(), _BGalpha);

    if (_textImage[1] == 1)
    {
        IMAGEMANAGER->findImage("오프닝글씨1")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("오프닝글씨1")->getMaxFrameX())
        {
           _textFrame = 0;
           _textImage.reset();
            _textImage.set(2, 1);
        }
    }
    else if (_textImage[2] == 1)
    {
       IMAGEMANAGER->findImage("오프닝글씨2")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
       if (_textFrame == IMAGEMANAGER->findImage("오프닝글씨1")->getMaxFrameX())
       {
           _textFrame = 0;
           _textImage.reset();
           _textImage.set(3, 1);
       }
    }
    else if (_textImage[3] == 1)
    {
        IMAGEMANAGER->findImage("오프닝글씨3")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("오프닝글씨1")->getMaxFrameX())
        {
            _textFrame = 0;
            _textImage.reset();
            _textImage.set(4, 1);
        }
    }
    else if (_textImage[4] == 1)
    {
        IMAGEMANAGER->findImage("오프닝글씨4")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("오프닝글씨1")->getMaxFrameX())
        {
            _textFrame = 0;
            _textImage.reset();
            _textImage.set(5, 1);
        }
    }
    else if (_textImage[5] == 1)
    {
        IMAGEMANAGER->findImage("오프닝글씨5")->frameRender(getMemDC(), 380, 300, _textFrame, 0);
        if (_textFrame == IMAGEMANAGER->findImage("오프닝글씨1")->getMaxFrameX())
        {
            _textFrame = 0;
            _textImage.reset();
            _textImage.set(6, 1);
        }
    }
    // 프레임 돌리는거 끝나고 게임시작화면
    else if (_textImage[6] == 1)
    {
        IMAGEMANAGER->findImage("오프닝불꽃")->alphaFrameRender(getMemDC(), 350, 270, _fireAlpha, _textFrame, 0);

        IMAGEMANAGER->findImage("오프닝로고")->render(getMemDC(), 80,200);
        IMAGEMANAGER->findImage("오프닝선택창1")->render(getMemDC(), 280, 500);


        // 선택창 마우스 충돌 시 변화
        if (PtInRect(&_rc[1], _ptMouse))
        {
            IMAGEMANAGER->findImage("오프닝선택창2")->frameRender(getMemDC(), _rc[1].left, _rc[1].top, 0, 0);
            if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
            {
                SOUNDMANAGER->play("메인선택", 1.0f);
                _next = true;
            }
        }
        else if (PtInRect(&_rc[2], _ptMouse))
        {
            IMAGEMANAGER->findImage("오프닝선택창2")->frameRender(getMemDC(), _rc[2].left, _rc[2].top, 0, 1);
        }
        else if (PtInRect(&_rc[3], _ptMouse))
        {
            IMAGEMANAGER->findImage("오프닝선택창2")->frameRender(getMemDC(), _rc[3].left, _rc[3].top, 0, 2);
        }
        else if (PtInRect(&_rc[4], _ptMouse))
        {
            IMAGEMANAGER->findImage("오프닝선택창2")->frameRender(getMemDC(), _rc[4].left, _rc[4].top, 0, 3);
        }
    }

    if (_next)
    {
        _nextAlpha+=5;
        IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), _nextAlpha);
        if(_nextAlpha>250) SCENEMANAGER->changScene("로딩","시나리오");
    }
}
