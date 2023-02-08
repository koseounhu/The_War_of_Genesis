#include "Stdafx.h"
#include "Loading.h"

HRESULT Loading::init(void)
{
    SOUNDMANAGER->stopAllSound();

    // �ε� ĳ���� �̹��� �ҷ�����
    IMAGEMANAGER->addFrameImage("LoadingCharacter", ROUTE_L"LoadingCharacter.bmp", 
        12400, 200, 31, 1, true, RGB(255, 0, 255));

    // �ð� üũ�� ƽ �ʱ�ȭ
    _tick = 0;

    // �ε� ĳ���� �̹����� ���� ���� �� ���� �ʱ�ȭ
    _loadingImgRanNum = RND->getFromIntTo(0, 30);

    return S_OK;
}

void Loading::release(void)
{
}

void Loading::update(void)
{
    // �ð� üũ�� ƽ ������Ʈ
    _tick++;

    // ���� ƽ�� �ö󰡸� ���� ������ ��ȯ
   if (_tick > 300) SCENEMANAGER->changScene(SCENEMANAGER->getReservationScene());
}

void Loading::render(void)
{
    IMAGEMANAGER->frameRender("LoadingCharacter", getMemDC(), 
        (WINSIZE_X - IMAGEMANAGER->findImage("LoadingCharacter")->getFrameWidth()) / 2,
        (WINSIZE_Y - IMAGEMANAGER->findImage("LoadingCharacter")->getFrameHeight()) / 2,
         _loadingImgRanNum, 0);
}