#include "Stdafx.h"
#include "MainGame.h"

#define BG "Resources/Images/Background/"
#define OBJ "Resources/Images/Object/"
#define OPEN "Resources/Images/Openning/"
#define SCE "Resources/Images/Scenario/"
#define BAT "Resources/Images/Battle/"
#define PL "Resources/Images/Player/"
#define WM "Resources/Images/WorldMap/"
#define UI "Resources/Images/UI/"
#define SOUND "Resources/Sounds/"
#define MAZEN RGB(255, 0, 255)
#define RGBRED RGB(255, 0, 0)
#define RGBBL RGB(4, 0, 4)
#define SKILL RGB(255, 239, 214)


void MainGame::ImageInit(void)
{
	// 임시 1.5배씩 더해줌
	IMAGEMANAGER->addFrameImage("셰라죽음", SCE"셰라죽음.bmp", 5520, 150,23,1,true,MAZEN);
	IMAGEMANAGER->addImage("임시2", SCE"임시2.bmp", 250, 250, true,MAZEN);
	IMAGEMANAGER->addImage("버몬트", SCE"버몬트.bmp", 390, 640, true,MAZEN);
	IMAGEMANAGER->addImage("살라딘", SCE"살라딘.bmp", 600, 680, true,MAZEN);
	IMAGEMANAGER->addImage("셰라", SCE"셰라.bmp", 625, 622, true,MAZEN);

	// 통합
	IMAGEMANAGER->addImage("검정알파", BG"blackness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("하얀알파", BG"whitness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("빨강알파", BG"redness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("시나리오클리어", BG"clear.bmp", WINSIZE_X, 100);
	IMAGEMANAGER->addImage("클리어광원", BG"clear광원.bmp", WINSIZE_X, 100,true,MAZEN);
	IMAGEMANAGER->addImage("클리어텍스트", BG"cleartxt.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("클리어텍스트광원", BG"cleartxt광원.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("다이얼로그창", SCE"Dialogue.bmp", 818, 178);
	IMAGEMANAGER->addImage("어빌리티창", OBJ"SkillBox.bmp", 208, 91);
	IMAGEMANAGER->addImage("블루타일", OBJ"blueTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("오랑타일", OBJ"redTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("노랑타일", OBJ"orangeTile.bmp", 40, 32);
	IMAGEMANAGER->addFrameImage("스킬UI", OBJ"PersonalBox.bmp", 416, 60,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("마우스타일", OBJ"MoveCursor.bmp", 240, 32,6,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("어빌리티버튼", OBJ"abilityButton.bmp", 34, 17,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("마우스", OBJ"mouse.bmp", 228, 24, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("그림자", OBJ"Shadow.bmp", 50, 25, true, RGB(255, 0, 255));

	// UI
	IMAGEMANAGER->addImage("UI스테이터창", UI"state.bmp", 218, 384);



	//플레이어
	IMAGEMANAGER->addFrameImage("살라딘_걷기", PL"살라딘_walk.bmp", 720, 360, 6, 4, true,MAZEN );
	IMAGEMANAGER->addFrameImage("살라딘_대기", PL"살라딘_idle.bmp", 240, 400, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_공격", PL"살라딘_atk.bmp", 700, 440, 5, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_스킬", PL"살라딘_스킬.bmp", 800, 100, 8, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_피격좌", PL"피격좌.bmp", 1224, 80, 12, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_피격우", PL"피격우.bmp", 1224, 80, 12, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("버몬트_걷기", PL"버몬트_WALK.bmp", 900, 360, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("버몬트_대기", PL"버몬트_IDLE.bmp", 270, 360, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("버몬트_공격", PL"버몬트_ATK.bmp", 900, 480, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("버몬트_피격", PL"버몬트_피격.bmp", 600, 132, 12, 2, true, MAZEN);

	// 적
	IMAGEMANAGER->addFrameImage("적1", PL"적1.bmp", 240, 160, 3, 2, true, MAZEN);


	// 스킬
	IMAGEMANAGER->addFrameImage("스킬구", PL"스킬구.bmp", 6325, 192, 25, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥1", PL"불기둥1.bmp", 1600, 230, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("스킬불기둥1_1", PL"불기둥1_1.bmp", 1600, 230, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("스킬불기둥2", PL"불기둥2.bmp", 1600, 300, 30, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("스킬불기둥2_1", PL"불기둥2_1.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("스킬불기둥3", PL"불기둥3.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("스킬불기둥3_1", PL"불기둥3_1.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("스킬이펙트1", PL"이펙트2.bmp", 7000, 250, 28, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트2", PL"이펙트1.bmp", 6400, 160, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트3", PL"이펙트3.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트3_1", PL"이펙트3_1.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트3_1", PL"이펙트3_1.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트4", PL"이펙트4.bmp", 3600, 150, 24, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트5", PL"이펙트5.bmp", 1200, 150, 8, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("스킬파티클1", PL"파티클1.bmp", 300, 20, 15, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬파티클2", PL"파티클2.bmp", 450, 30, 15, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬파티클3", PL"파티클3.bmp", 750, 50, 15, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("스킬바닥불", PL"바닥불.bmp", 1800, 150, 12, 1, true, MAZEN);

	// 광원
	IMAGEMANAGER->addFrameImage("스킬구광원", PL"스킬구광원.bmp", 6325, 192, 25, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥1광원", PL"불기둥1광원.bmp", 1600, 230, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥1_1광원", PL"불기둥1_1광원.bmp", 1600, 230, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥2광원", PL"불기둥2광원.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥2_1광원", PL"불기둥2_1광원.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥3광원", PL"불기둥3광원.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬불기둥3_1광원", PL"불기둥3_1광원.bmp", 1600, 300, 32, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("스킬바닥불광원", PL"바닥불광원.bmp", 1800, 150, 12, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("스킬이펙트1광원", PL"이펙트2광원.bmp", 7000, 250, 28, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트2광원", PL"이펙트1광원.bmp", 6400, 160, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트3광원", PL"이펙트3광원.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트3_1광원", PL"이펙트3_1광원.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("스킬이펙트5광원", PL"이펙트5광원.bmp", 1200, 150, 8, 1, true, MAZEN);

	
	
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

	// 1번 시나리오
	IMAGEMANAGER->addImage("시나리오배경", SCE"SceneBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("컷신배경", SCE"ScenarioBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("시나리오형제", SCE"brother.bmp", 120, 45,true,MAZEN);

	// 2번 시나리오
	IMAGEMANAGER->addImage("2_0", SCE"2_0.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_1", SCE"2_1.bmp", WINSIZE_X, WINSIZE_Y+30);
	IMAGEMANAGER->addImage("2_2", SCE"2_2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_3", SCE"2_3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_4", SCE"2_4.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_5", SCE"2_5.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_6", SCE"2_6.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_7", SCE"2_7.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_8", SCE"2_8.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_9", SCE"2_9.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2_10", SCE"2_10.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("3_1", SCE"3_1.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("4_1", SCE"4_1.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("4_2", SCE"4_2.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("4_3", SCE"4_3.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("4_4", SCE"4_4.bmp", WINSIZE_X, WINSIZE_Y);

	IMAGEMANAGER->addImage("살라딘칼", SCE"살라딘칼찌름.bmp", 220, 90,true,MAZEN);
	IMAGEMANAGER->addImage("버몬트칼찔림", SCE"버몬트칼찔림.bmp", 90, 90,true,MAZEN);
	IMAGEMANAGER->addImage("살라딘_목걸이", SCE"살라딘_목걸이.bmp", 90, 120,true,MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_휘파람", SCE"살라딘_휘파람.bmp", 180, 110,2,1,true,MAZEN);
	IMAGEMANAGER->addImage("목걸이뺏김", SCE"목걸이뺏김.bmp", 90, 100,true,MAZEN);

	// 전투맵
	IMAGEMANAGER->addImage("전투맵", BAT"BattleMap.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("전투맵2", BAT"BattleMap2.bmp", 2200, 2000);
	IMAGEMANAGER->addImage("픽충배경", BAT"픽충배경.bmp", 1800, 1696);




	// WorldMap
	IMAGEMANAGER->addImage("월드맵배경", WM"WorldBG.bmp", 1446, 1074, true, MAZEN);
	IMAGEMANAGER->addImage("월드맵전투마크", WM"WarMark.bmp", 70, 70, true, MAZEN);
	IMAGEMANAGER->addImage("월드맵거점마크", WM"TeamDesign.bmp", 50, 50, true, MAZEN);
	IMAGEMANAGER->addImage("월드맵파도", WM"Wave.bmp", WINSIZE_X*2, WINSIZE_Y*2);
	IMAGEMANAGER->addImage("월드맵지역", WM"Location.bmp", 240, 101,true,MAZEN);
	IMAGEMANAGER->addFrameImage("월드맵버튼", WM"Button.bmp", 332, 48,2,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("월드맵거점", WM"TeamRect.bmp", 2088, 150,18,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("월드맵선택", WM"circle.bmp", 1450, 47,25,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("월드맵프로필", WM"Profile.bmp", 800, 148,5,1,true,MAZEN);




	// 사운드
	SOUNDMANAGER->addSound("스킬구", SOUND"스킬구.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트_죽여라", SOUND"버몬트_죽여라.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트_그것만은", SOUND"버몬트_그것만은.mp3", false, false);
}