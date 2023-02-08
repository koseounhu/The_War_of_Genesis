#include "Stdafx.h"
#include "Loading.h"

HRESULT Loading::init(void)
{
    SOUNDMANAGER->stopAllSound();

    // 로딩 캐릭터 이미지 불러오기
    IMAGEMANAGER->addFrameImage("LoadingCharacter", ROUTE_L"LoadingCharacter.bmp", 
        12400, 200, 31, 1, true, RGB(255, 0, 255));

    // 시간 체크용 틱 초기화
    _tick = 0;

    // 로딩 캐릭터 이미지용 임의 숫자 및 알파 초기화
    _loadingImgRanNum = RND->getFromIntTo(0, 30);

    return S_OK;
}

void Loading::release(void)
{
}

void Loading::update(void)
{
    // 시간 체크용 틱 업데이트
    _tick++;

    // 일정 틱이 올라가면 예약 씬으로 전환
   if (_tick > 300) SCENEMANAGER->changScene(SCENEMANAGER->getReservationScene());
}

void Loading::render(void)
{
    IMAGEMANAGER->frameRender("LoadingCharacter", getMemDC(), 
        (WINSIZE_X - IMAGEMANAGER->findImage("LoadingCharacter")->getFrameWidth()) / 2,
        (WINSIZE_Y - IMAGEMANAGER->findImage("LoadingCharacter")->getFrameHeight()) / 2,
         _loadingImgRanNum, 0);
}