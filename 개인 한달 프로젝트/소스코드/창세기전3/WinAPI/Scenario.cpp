#include "Stdafx.h"
#include "Scenario.h"

HRESULT Scenario::init(void)
{
    _rc = RectMake(100, 660, 200, 50);
    

    _alpha = 0;

    _tick= _fireAlpha = 0;

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
      if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _next = true;
     
  }
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
      if (_alpha > 250)SCENEMANAGER->changScene("시나리오컷씬");
      
      IMAGEMANAGER->alphaFrameRender("오프닝넥스트", getMemDC(), WINSIZE_X / 2 - 150, WINSIZE_Y / 2 - 150, 150, _fireAlpha, 0);

  }
}

// 오프닝 넥스트 불꽃 만들면됨
// 이미지 추가해놧고
// 알파변수 만들어서 렌더 해보면될듯
