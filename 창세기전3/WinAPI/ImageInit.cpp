#include "Stdafx.h"
#include "MainGame.h"

#define BG "Resources/Images/Background/"
#define OBJ "Resources/Images/Object/"
#define OPEN "Resources/Images/Openning/"
#define SCE "Resources/Images/Scenario/"
#define BAT "Resources/Images/Battle/"
#define PL "Resources/Images/Player/"
#define WM "Resources/Images/WorldMap/"
#define MAZEN RGB(255, 0, 255)
#define RGBRED RGB(255, 0, 0)
#define RGBBL RGB(4, 0, 4)



void MainGame::ImageInit(void)
{
	// 임시 1.5배씩 더해줌
	IMAGEMANAGER->addImage("임시1", SCE"임시1.bmp", 176, 111,true,RGB(168,208,168));
	IMAGEMANAGER->addImage("임시2", SCE"임시2.bmp", 98, 108, true, RGB(168, 208, 168));

	// 통합
	IMAGEMANAGER->addImage("검정알파", BG"blackness.bmp", WINSIZE_X, WINSIZE_Y);

	//플레이어
	IMAGEMANAGER->addFrameImage("살라딘_걷기", PL"살라딘_walk.bmp", 720, 360, 6, 4, true,MAZEN );
	IMAGEMANAGER->addFrameImage("살라딘_대기", PL"살라딘_idle.bmp", 240, 400, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_공격", PL"살라딘_atk.bmp", 700, 440, 5, 4, true, MAZEN);

	IMAGEMANAGER->addFrameImage("버몬트_걷기", PL"버몬트_WALK.bmp", 900, 360, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("버몬트_대기", PL"버몬트_IDLE.bmp", 270, 360, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("버몬트_공격", PL"버몬트_ATK.bmp", 900, 480, 6, 4, true, MAZEN);
	
	
	// 오프닝
	IMAGEMANAGER->addImage("오프닝배경", OPEN"OpeningBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("오프닝로고", OPEN"OpeningLogo.bmp", 902, 234,true, MAZEN);
	IMAGEMANAGER->addFrameImage("오프닝글씨1", OPEN"Opening_1.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("오프닝글씨2", OPEN"Opening_2.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("오프닝글씨3", OPEN"Opening_3.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("오프닝글씨4", OPEN"Opening_4.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("오프닝글씨5", OPEN"Opening_5.bmp", 5865, 218, 23, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("오프닝선택창1", OPEN"OpeningBtn1.bmp", 460, 217, 1, 4, true, RGBRED);
	IMAGEMANAGER->addFrameImage("오프닝선택창2", OPEN"OpeningBtn2.bmp", 460, 217, 1, 4, true, RGBRED);
	IMAGEMANAGER->addFrameImage("오프닝불꽃", OPEN"OpeningFire.bmp", 11160, 256, 36, 1, true, RGB(0,0,0));
	IMAGEMANAGER->addFrameImage("오프닝넥스트", OPEN"OpeningNext.bmp", 4335, 254, 17, 1, true, RGB(0,0,0));

	// 시나리오
	IMAGEMANAGER->addImage("시나리오배경", SCE"SceneBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("컷신배경", SCE"ScenarioBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("시나리오형제", SCE"brother.bmp", 120, 45,true,MAZEN);


	// 전투맵
	IMAGEMANAGER->addImage("전투맵", BAT"BattleMap.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("전투맵2", BAT"BattleMap2.bmp", 1800, 1696);


	// UI
	IMAGEMANAGER->addFrameImage("마우스", OBJ"mouse.bmp", 228, 24, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그림자", OBJ"Shadow.bmp", 50, 25, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("블루타일", OBJ"blueTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("레드타일", OBJ"redTile.bmp", 40, 32);

	// WorldMap
	IMAGEMANAGER->addImage("월드맵배경", WM"WorldBG.bmp", 1446, 1074, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("월드맵파도", WM"Wave.bmp", WINSIZE_X*2, WINSIZE_Y*2);
	IMAGEMANAGER->addImage("월드맵지역", WM"Location.bmp", 240, 101,true,MAZEN);
	IMAGEMANAGER->addFrameImage("월드맵버튼", WM"Button.bmp", 332, 48,2,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("월드맵거점", WM"TeamRect.bmp", 1160, 150,10,1,true,MAZEN);

}