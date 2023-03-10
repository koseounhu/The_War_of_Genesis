#include "Stdafx.h"
#include "Scenario.h"

HRESULT Scenario::init(void)
{
    _rc = RectMake(100, 660, 200, 50);
    

    _alpha = 0;

    _tick= _fireAlpha = 0;

    SOUNDMANAGER->play("시나리오선택", 0.5f);
    return S_OK;
}

void Scenario::release(void)
{
}

void Scenario::update(void)
{

   

}

void Scenario::render(void)
{
  IMAGEMANAGER->findImage("시나리오배경")->render(getMemDC(),0,0);

  if (PtInRect(&_rc, _ptMouse))
  {
      IMAGEMANAGER->findImage("시나리오형제")->render(getMemDC(), _rc.left + 30, _rc.top);
      if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
      {
          SOUNDMANAGER->play("버튼", 1.0f);
        _next = true;
      }
     
  }
#pragma region 마우스
  ShowCursor(false);
  _Mrc = RectMake(_ptMouse.x, _ptMouse.y, 16, 24);
  _frame++;
  IMAGEMANAGER->findImage("일반마우스")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frame, 0);
  if (_frame > 12)_frame = 0;
#pragma endregion

  if (_next)
  {
      _tick++;
      _alpha++;
      IMAGEMANAGER->alphaRender("검정알파", getMemDC(), _alpha);

      if (_tick % 8 == 0)
      {
          _fireAlpha++;
          if (_fireAlpha > IMAGEMANAGER->findImage("오프닝넥스트")->getMaxFrameX())_fireAlpha = 0;
      }
      if (_alpha > 250)SCENEMANAGER->changScene("로딩","월드맵");
      
      IMAGEMANAGER->alphaFrameRender("오프닝넥스트", getMemDC(), WINSIZE_X / 2 - 150, WINSIZE_Y / 2 - 150, 150, _fireAlpha, 0);

  }
}
