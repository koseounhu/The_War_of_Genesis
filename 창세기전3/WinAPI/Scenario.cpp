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
  IMAGEMANAGER->findImage("�ó��������")->render(getMemDC(),0,0);

  if (PtInRect(&_rc, _ptMouse))
  {
      IMAGEMANAGER->findImage("�ó���������")->render(getMemDC(), _rc.left + 30, _rc.top);
      if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON)) _next = true;
     
  }
  if (_next)
  {
      _tick++;
      _alpha++;
      IMAGEMANAGER->alphaRender("��������", getMemDC(), _alpha);

      if (_tick % 8 == 0)
      {
          _fireAlpha++;
          if (_fireAlpha > IMAGEMANAGER->findImage("�����׳ؽ�Ʈ")->getMaxFrameX())_fireAlpha = 0;
      }
      if (_alpha > 250)SCENEMANAGER->changScene("�ó������ƾ�");
      
      IMAGEMANAGER->alphaFrameRender("�����׳ؽ�Ʈ", getMemDC(), WINSIZE_X / 2 - 150, WINSIZE_Y / 2 - 150, 150, _fireAlpha, 0);

  }
}

// ������ �ؽ�Ʈ �Ҳ� ������
// �̹��� �߰��؇J��
// ���ĺ��� ���� ���� �غ���ɵ�
