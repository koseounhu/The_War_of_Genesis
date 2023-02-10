#include "Stdafx.h"
#include "Store.h"

HRESULT Store::init(void)
{
	// 메인 메뉴 초기화
	_menu.x = 800;
	_menu.y = 70;
	int temp=0;
	for (int i = 0; i < 4; i++)
	{
		_menu.rc[i]= RectMake(_menu.x, _menu.y+temp, 200, 50);
		temp += 70;
	}
	// 시작시 메인 이므로 true설정
	_main = true;



	return S_OK;
}

void Store::release(void)
{
}

void Store::update(void)
{
}

void Store::render(void)
{
	// 상점 공통 렌더
	IMAGEMANAGER->findImage("상점배경")->render(getMemDC());

	// 메인 메뉴
	if (_main)
	{
		IMAGEMANAGER->findImage("상점타이틀")->render(getMemDC());
		IMAGEMANAGER->findImage("상점바닥얼굴")->render(getMemDC(), 0, 570);

		// 메인 버튼 조작
		for (int i = 0; i < _countof(_menu.rc); i++)
		{
			// 이미지 렌더
			IMAGEMANAGER->findImage("상점메인메뉴버튼")->alphaFrameRender(getMemDC(), _menu.rc[i].left - 10, _menu.rc[i].top, 125, _menu.rcFrameCheck[i], 0);
			IMAGEMANAGER->findImage("상점메뉴건물이미지")->frameRender(getMemDC(), _menu.rc[i].left, _menu.rc[i].top, i, 0);

			// 메인버튼 마우스 충돌
			if (PtInRect(&_menu.rc[i], _ptMouse))			_menu.rcFrameCheck[i] = true;
			else 			_menu.rcFrameCheck[i] = false;

			// 상점으로 진입
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (PtInRect(&_menu.rc[i], _ptMouse))
				{
					SCENEMANAGER->changScene("무기상점");
				}
			}
		}

		// 메인상점 텍스트
		FONTMANAGER->drawText(getMemDC(), _menu.rc[0].left + 60, _menu.rc[0].top + 12, 25, 255, 255, 255, "굴림", true, "무기 상점");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[1].left + 60, _menu.rc[1].top + 12, 25, 255, 255, 255, "굴림", true, "도구 상점");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[2].left + 60, _menu.rc[2].top + 12, 25, 255, 255, 255, "굴림", true, "용병 대기소");
		FONTMANAGER->drawText(getMemDC(), _menu.rc[3].left + 60, _menu.rc[3].top + 12, 25, 255, 255, 255, "굴림", true, "  주  점 ");
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X/2-90, 16, 30, 255, 223, 0, "굴림", true, "  자 비 단 ");


	} // 메인== true



}
