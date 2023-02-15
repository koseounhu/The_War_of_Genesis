#include "Stdafx.h"
#include "MainGame.h"

#define BG "Resources/Images/Background/"
#define EM "Resources/Images/Enemy/"
#define OBJ "Resources/Images/Object/"
#define OPEN "Resources/Images/Openning/"
#define SCE "Resources/Images/Scenario/"
#define BAT "Resources/Images/Battle/"
#define PL "Resources/Images/Player/"
#define WM "Resources/Images/WorldMap/"
#define UI "Resources/Images/UI/"
#define ST "Resources/Images/Store/"
#define SK "Resources/Images/Skill/"
#define SOUND "Resources/Sounds/"
#define MAZEN RGB(255, 0, 255)
#define RGBRED RGB(255, 0, 0)
#define RGBBL RGB(4, 0, 4)
#define SKILL RGB(255, 239, 214)


void MainGame::ImageInit(void)
{
	// 큰 캐릭터 이미지
	IMAGEMANAGER->addImage("버몬트", SCE"버몬트.bmp", 390, 640, true,MAZEN);
	IMAGEMANAGER->addImage("살라딘", SCE"살라딘.bmp", 600, 680, true,MAZEN);
	IMAGEMANAGER->addImage("셰라", SCE"셰라.bmp", 625, 622, true,MAZEN);

#pragma region 통합 UI
	// 통합
	IMAGEMANAGER->addImage("검정알파", BG"blackness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("하얀알파", BG"whitness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("빨강알파", BG"redness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("시나리오클리어", BG"clear.bmp", WINSIZE_X, 100);
	IMAGEMANAGER->addImage("클리어광원", BG"clear광원.bmp", WINSIZE_X, 100,true,MAZEN);
	IMAGEMANAGER->addImage("클리어텍스트", BG"cleartxt.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("클리어텍스트광원", BG"cleartxt광원.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("다이얼로그창", SCE"Dialogue.bmp", 818, 178);
	IMAGEMANAGER->addImage("어빌리티창", OBJ"SkillBox.bmp", 208, 150);
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
	IMAGEMANAGER->addImage("MapInfo", UI"mapInfo.bmp", 230, 105);
	IMAGEMANAGER->addFrameImage("적턴", UI"적턴.bmp", 72, 11,8,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘턴", UI"살라딘턴.bmp", 72, 11,8,1,true,MAZEN);
#pragma endregion

#pragma region Unit

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

	// 적2
	IMAGEMANAGER->addFrameImage("적2_공격", EM"E2_attack.bmp", 1572, 392, 12, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("적2_걷기", EM"E2_run.bmp", 456, 368, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("적2_대기", EM"E2_idle.bmp", 270, 280, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("적2_피격", EM"E2_atked.bmp", 1080, 300, 12, 4, true, MAZEN);


#pragma endregion

#pragma region 상점

	IMAGEMANAGER->addImage("상점배경", ST"StoreBG.bmp", WINSIZE_X, WINSIZE_Y, true, MAZEN);
	IMAGEMANAGER->addImage("상점타이틀", ST"StoreTitle.bmp", 1024, 64, true, MAZEN);
	IMAGEMANAGER->addImage("상점바닥얼굴", ST"StoreFaceTitle.bmp", 1024, 192, true, MAZEN);
	IMAGEMANAGER->addFrameImage("상점메뉴건물이미지", ST"StoreMainBtnBuilding.bmp", 224, 56,4,1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("상점메인메뉴버튼", ST"StoreMainBtn.bmp", 672, 56,3,1, true, MAZEN);
	IMAGEMANAGER->addImage("무기상점여자", ST"storeGirl.bmp", 400, 490, true, MAZEN);
	IMAGEMANAGER->addImage("상점다이얼로그", ST"WeaponDialogue.bmp", 1024, 192, true, MAZEN);
	IMAGEMANAGER->addImage("무기리스트배경", ST"WeaponList.bmp", 501, 349, true, MAZEN);
	IMAGEMANAGER->addImage("무기상점타이틀", ST"StoreProfileBox2.bmp", 266, 66, true, MAZEN);
	IMAGEMANAGER->addFrameImage("상점작은버튼", ST"StoreMiniBtn.bmp", 180, 26, 2,1,true, MAZEN);
	IMAGEMANAGER->addFrameImage("위아래버튼", ST"WeaponArrowBtn.bmp", 40, 52, 2,2,true, MAZEN);
	IMAGEMANAGER->addImage("무기구매", ST"WeaponBuy.bmp", 373, 128,true, MAZEN);
	IMAGEMANAGER->addImage("스크롤", ST"WeaponScroll.bmp", 26, 286,true, MAZEN);
	IMAGEMANAGER->addImage("구매카운트", ST"WeaponCount.bmp", 28, 26,true, MAZEN);
	IMAGEMANAGER->addFrameImage("무기아이콘", ST"무기아이콘.bmp", 40, 280,1,7,true, MAZEN);



#pragma endregion

#pragma region 스킬
	#pragma region 천지파열무
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

	#pragma endregion
	#pragma region 혈랑마혼
		IMAGEMANAGER->addFrameImage("호랑이", SK"호랑이.bmp", 6500, 250, 26, 1, true, MAZEN);
		IMAGEMANAGER->addFrameImage("토탈번개", SK"토탈번개.bmp", 3375, 600, 15, 1, true, RGB(0,0,0));
		IMAGEMANAGER->addFrameImage("토탈번개광원", SK"토탈번개광원.bmp", 3375, 600, 15, 1, true, RGB(0,0,0));
		IMAGEMANAGER->addFrameImage("살라딘돌진기", SK"살라딘돌진기.bmp", 450, 600, 3, 4, true, MAZEN);
		IMAGEMANAGER->addFrameImage("돌진이펙트", SK"돌진이펙트.bmp", 1400, 800, 7, 4, true, MAZEN);
	#pragma endregion
#pragma endregion
	
#pragma region 오프닝
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
#pragma endregion

#pragma region 시나리오
	// 1번 시나리오
	IMAGEMANAGER->addImage("시나리오배경", SCE"SceneBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("컷신배경", SCE"ScenarioBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("2번전투시작전배경", SCE"2번전투시작전배경.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("셰라죽음배경", SCE"셰라죽음배경.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("셰라눈감음", SCE"셰라눈감음.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("시나리오형제", SCE"brother.bmp", 120, 45,true,MAZEN);
	IMAGEMANAGER->addFrameImage("셰라죽을때", SCE"셰라죽을때.bmp", 540, 120, 4, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("버몬트_걷기2", PL"버몬트_WALK.bmp", 1350, 540, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_걷기2", PL"살라딘_walk.bmp", 1080, 540, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("살라딘_대기2", PL"살라딘_idle.bmp", 360, 600, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("목걸이뺏기이펙트", SCE"목걸이뺏기이펙트.bmp", 900, 135, 5, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("목걸이", SCE"목걸이.bmp", 200, 20, 10, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("셰라죽음", SCE"셰라죽음.bmp", 5520, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("파티클", SCE"파티클.bmp", 18600, 450, 31, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("파티클광원", SCE"파티클광원.bmp", 18600, 450, 31, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("파티클광원2", SCE"파티클광원2.bmp", 18600, 450, 31, 1, true, MAZEN);


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
	IMAGEMANAGER->addFrameImage("버몬트살라딘엔딩", SCE"버몬트살라딘엔딩.bmp", 720, 120,6,1,true,MAZEN);
#pragma endregion

#pragma region 맵 + 상점

	// 전투맵
	IMAGEMANAGER->addImage("전투맵", BAT"BattleMap.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("전투맵2", BAT"BattleMap2.bmp", 2200, 2000);
	IMAGEMANAGER->addImage("전투맵3", BAT"BattleMap3.bmp", 2250, 1620);
	IMAGEMANAGER->addImage("픽충배경", BAT"픽충배경.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("배틀3기둥", BAT"Pillar.bmp", 120, 288,true, RGB(0,0,0));
	IMAGEMANAGER->addImage("배틀3픽충배경", BAT"배틀3픽충배경.bmp", 2250, 1620);

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

	// Loading
	IMAGEMANAGER->addFrameImage("LoadingCharacter", "Resources/Images/Loading/LoadingCharacter.bmp", 12400, 200, 31, 1);
	IMAGEMANAGER->addImage("LoadingBlack", "Resources/Images/Loading/LoadingBlack.bmp", WINSIZE_X,WINSIZE_Y);

#pragma  endregion

#pragma region 사운드

	// 게임시작
	SOUNDMANAGER->addSound("게임시작", SOUND"게임시작.mp3", false, false);
	SOUNDMANAGER->addSound("메인선택", SOUND"메인선택.mp3", false, false);
	SOUNDMANAGER->addSound("시나리오선택", SOUND"시나리오선택.mp3", false, false);

	// 월드맵
	SOUNDMANAGER->addSound("월드맵배경", SOUND"월드맵배경.mp3", false, false);

	// UI
	SOUNDMANAGER->addSound("버튼", SOUND"button.mp3", false, false);

	// 상점 배경
	SOUNDMANAGER->addSound("상점배경", SOUND"상점배경.mp3", false, false);


	// 1번 전투 배경
	SOUNDMANAGER->addSound("1번전투배경", SOUND"1번전투배경.mp3", false, false);

	// 2번 전투 배경
	SOUNDMANAGER->addSound("2번전투배경", SOUND"2번전투배경.mp3", false, false);

	// 3번 전투 배경
	SOUNDMANAGER->addSound("3번전투배경", SOUND"3번전투배경.mp3", false, false);
	SOUNDMANAGER->addSound("적2공격", SOUND"적2공격.mp3", false, false);



	// 1번 시나리오
	SOUNDMANAGER->addSound("기다리고잇엇다", SOUND"기다리고잇엇다.mp3", false, false);
	SOUNDMANAGER->addSound("지난번엔", SOUND"지난번엔.mp3", false, false);
	SOUNDMANAGER->addSound("셰라-살라딘", SOUND"셰라-살라딘.mp3", false, false);
	SOUNDMANAGER->addSound("셰라자드걱정마시오", SOUND"셰라자드걱정마시오.mp3", false, false);
	SOUNDMANAGER->addSound("좋다칼버림", SOUND"좋다칼버림.mp3", false, false);
	SOUNDMANAGER->addSound("요새두개", SOUND"요새두개.mp3", false, false);
	SOUNDMANAGER->addSound("셰라개의치", SOUND"셰라개의치.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘설마", SOUND"살라딘설마.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트여술탄", SOUND"버몬트여술탄.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘왜그런짓", SOUND"살라딘왜그런짓.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트복수다", SOUND"버몬트복수다.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘칼버림", SOUND"살라딘칼버림.mp3", false, false);
	SOUNDMANAGER->addSound("셰라안되요", SOUND"셰라안되요.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘투르인", SOUND"살라딘투르인.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트체포해라", SOUND"버몬트체포해라.mp3", false, false);
	SOUNDMANAGER->addSound("셰라자살", SOUND"셰라자살.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘안돼", SOUND"살라딘안돼.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트제길", SOUND"버몬트제길.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘이게무슨짓", SOUND"살라딘이게무슨짓.mp3", false, false);
	SOUNDMANAGER->addSound("셰라순결", SOUND"셰라순결.mp3", false, false);
	SOUNDMANAGER->addSound("셰라투르선택감사", SOUND"셰라투르선택감사.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘이젠늦엇소", SOUND"살라딘이젠늦엇소.mp3", false, false);
	SOUNDMANAGER->addSound("셰라언젠가말씀", SOUND"셰라언젠가말씀.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘죽으면안되오", SOUND"살라딘죽으면안되오.mp3", false, false);
	SOUNDMANAGER->addSound("셰라약속해줘", SOUND"셰라약속해줘.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘하지만녀석들", SOUND"살라딘하지만녀석들.mp3", false, false);
	SOUNDMANAGER->addSound("셰라마지막소원", SOUND"셰라마지막소원.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘어려운약속", SOUND"살라딘어려운약속.mp3", false, false);
	SOUNDMANAGER->addSound("셰라그런느낌", SOUND"셰라그런느낌.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘셰라자드", SOUND"살라딘셰라자드.mp3", false, false);
	SOUNDMANAGER->addSound("셰라안녕", SOUND"셰라안녕.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트다끝나셧나", SOUND"버몬트다끝나셧나.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘복수심에", SOUND"살라딘복수심에.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트각오해라", SOUND"버몬트각오해라.mp3", false, false);
	SOUNDMANAGER->addSound("살라딘좋은왕", SOUND"살라딘좋은왕.mp3", false, false);
	SOUNDMANAGER->addSound("울음", SOUND"울음.mp3", false, false);

	// 1번 시나리오 배경
	SOUNDMANAGER->addSound("배경셰라언젠가말할때", SOUND"배경셰라언젠가말할때.mp3", true, true);
	SOUNDMANAGER->addSound("dia18번배경", SOUND"dia18번배경.mp3", false, false);
	SOUNDMANAGER->addSound("1번시나리오배경음악", SOUND"1번시나리오배경음악.mp3", false, true);
	SOUNDMANAGER->addSound("휘파람", SOUND"휘파람.mp3", false, false);

	
	// 2번 시나리오
	SOUNDMANAGER->addSound("버몬트_죽여라", SOUND"버몬트_죽여라.mp3", false, false);
	SOUNDMANAGER->addSound("버몬트_그것만은", SOUND"버몬트_그것만은.mp3", false, false);
	SOUNDMANAGER->addSound("2번시나리오배경", SOUND"2번시나리오배경.mp3", false, false);
	SOUNDMANAGER->addSound("목걸이뺏기", SOUND"목걸이뺏기.mp3", false, false);
	
	// 스킬
	SOUNDMANAGER->addSound("스킬구", SOUND"스킬구.mp3", false, false);
	SOUNDMANAGER->addSound("클리어소리", SOUND"클리어소리.mp3", false, false);
	SOUNDMANAGER->addSound("마지막터질때", SOUND"마지막터질때.mp3", false, false);
	SOUNDMANAGER->addSound("찍을때", SOUND"찍을때.mp3", false, false);
	SOUNDMANAGER->addSound("화염구터질때", SOUND"화염구터질때.mp3", false, false);
	SOUNDMANAGER->addSound("적불기둥때", SOUND"적불기둥때.mp3", false, false);
	SOUNDMANAGER->addSound("대각선불기둥", SOUND"대각선불기둥.mp3", false, false);

	// 공격
	SOUNDMANAGER->addSound("살라딘공격", SOUND"살라딘공격.mp3", false, false);

#pragma endregion
}