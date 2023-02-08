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
	// ÀÓ½Ã 1.5¹è¾¿ ´õÇØÁÜ
	IMAGEMANAGER->addFrameImage("¼Î¶óÁ×À½", SCE"¼Î¶óÁ×À½.bmp", 5520, 150,23,1,true,MAZEN);
	IMAGEMANAGER->addImage("ÀÓ½Ã2", SCE"ÀÓ½Ã2.bmp", 250, 250, true,MAZEN);
	IMAGEMANAGER->addImage("¹ö¸óÆ®", SCE"¹ö¸óÆ®.bmp", 390, 640, true,MAZEN);
	IMAGEMANAGER->addImage("»ì¶óµò", SCE"»ì¶óµò.bmp", 600, 680, true,MAZEN);
	IMAGEMANAGER->addImage("¼Î¶ó", SCE"¼Î¶ó.bmp", 625, 622, true,MAZEN);

	// ÅëÇÕ
	IMAGEMANAGER->addImage("°ËÁ¤¾ËÆÄ", BG"blackness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("ÇÏ¾á¾ËÆÄ", BG"whitness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("»¡°­¾ËÆÄ", BG"redness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("½Ã³ª¸®¿ÀÅ¬¸®¾î", BG"clear.bmp", WINSIZE_X, 100);
	IMAGEMANAGER->addImage("Å¬¸®¾î±¤¿ø", BG"clear±¤¿ø.bmp", WINSIZE_X, 100,true,MAZEN);
	IMAGEMANAGER->addImage("Å¬¸®¾îÅØ½ºÆ®", BG"cleartxt.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("Å¬¸®¾îÅØ½ºÆ®±¤¿ø", BG"cleartxt±¤¿ø.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("´ÙÀÌ¾ó·Î±×Ã¢", SCE"Dialogue.bmp", 818, 178);
	IMAGEMANAGER->addImage("¾îºô¸®Æ¼Ã¢", OBJ"SkillBox.bmp", 208, 91);
	IMAGEMANAGER->addImage("ºí·çÅ¸ÀÏ", OBJ"blueTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("¿À¶ûÅ¸ÀÏ", OBJ"redTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("³ë¶ûÅ¸ÀÏ", OBJ"orangeTile.bmp", 40, 32);
	IMAGEMANAGER->addFrameImage("½ºÅ³UI", OBJ"PersonalBox.bmp", 416, 60,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸¶¿ì½ºÅ¸ÀÏ", OBJ"MoveCursor.bmp", 240, 32,6,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¾îºô¸®Æ¼¹öÆ°", OBJ"abilityButton.bmp", 34, 17,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("¸¶¿ì½º", OBJ"mouse.bmp", 228, 24, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("±×¸²ÀÚ", OBJ"Shadow.bmp", 50, 25, true, RGB(255, 0, 255));

	// UI
	IMAGEMANAGER->addImage("UI½ºÅ×ÀÌÅÍÃ¢", UI"state.bmp", 218, 384);



	//ÇÃ·¹ÀÌ¾î
	IMAGEMANAGER->addFrameImage("»ì¶óµò_°È±â", PL"»ì¶óµò_walk.bmp", 720, 360, 6, 4, true,MAZEN );
	IMAGEMANAGER->addFrameImage("»ì¶óµò_´ë±â", PL"»ì¶óµò_idle.bmp", 240, 400, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("»ì¶óµò_°ø°Ý", PL"»ì¶óµò_atk.bmp", 700, 440, 5, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("»ì¶óµò_½ºÅ³", PL"»ì¶óµò_½ºÅ³.bmp", 800, 100, 8, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("»ì¶óµò_ÇÇ°ÝÁÂ", PL"ÇÇ°ÝÁÂ.bmp", 1224, 80, 12, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("»ì¶óµò_ÇÇ°Ý¿ì", PL"ÇÇ°Ý¿ì.bmp", 1224, 80, 12, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("¹ö¸óÆ®_°È±â", PL"¹ö¸óÆ®_WALK.bmp", 900, 360, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("¹ö¸óÆ®_´ë±â", PL"¹ö¸óÆ®_IDLE.bmp", 270, 360, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("¹ö¸óÆ®_°ø°Ý", PL"¹ö¸óÆ®_ATK.bmp", 900, 480, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("¹ö¸óÆ®_ÇÇ°Ý", PL"¹ö¸óÆ®_ÇÇ°Ý.bmp", 600, 132, 12, 2, true, MAZEN);

	// Àû
	IMAGEMANAGER->addFrameImage("Àû1", PL"Àû1.bmp", 240, 160, 3, 2, true, MAZEN);


	// ½ºÅ³
	IMAGEMANAGER->addFrameImage("½ºÅ³±¸", PL"½ºÅ³±¸.bmp", 6325, 192, 25, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ1", PL"ºÒ±âµÕ1.bmp", 1600, 230, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ1_1", PL"ºÒ±âµÕ1_1.bmp", 1600, 230, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ2", PL"ºÒ±âµÕ2.bmp", 1600, 300, 30, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ2_1", PL"ºÒ±âµÕ2_1.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ3", PL"ºÒ±âµÕ3.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ3_1", PL"ºÒ±âµÕ3_1.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®1", PL"ÀÌÆåÆ®2.bmp", 7000, 250, 28, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®2", PL"ÀÌÆåÆ®1.bmp", 6400, 160, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®3", PL"ÀÌÆåÆ®3.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®3_1", PL"ÀÌÆåÆ®3_1.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®3_1", PL"ÀÌÆåÆ®3_1.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®4", PL"ÀÌÆåÆ®4.bmp", 3600, 150, 24, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®5", PL"ÀÌÆåÆ®5.bmp", 1200, 150, 8, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("½ºÅ³ÆÄÆ¼Å¬1", PL"ÆÄÆ¼Å¬1.bmp", 300, 20, 15, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÆÄÆ¼Å¬2", PL"ÆÄÆ¼Å¬2.bmp", 450, 30, 15, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÆÄÆ¼Å¬3", PL"ÆÄÆ¼Å¬3.bmp", 750, 50, 15, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("½ºÅ³¹Ù´ÚºÒ", PL"¹Ù´ÚºÒ.bmp", 1800, 150, 12, 1, true, MAZEN);

	// ±¤¿ø
	IMAGEMANAGER->addFrameImage("½ºÅ³±¸±¤¿ø", PL"½ºÅ³±¸±¤¿ø.bmp", 6325, 192, 25, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ1±¤¿ø", PL"ºÒ±âµÕ1±¤¿ø.bmp", 1600, 230, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ1_1±¤¿ø", PL"ºÒ±âµÕ1_1±¤¿ø.bmp", 1600, 230, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ2±¤¿ø", PL"ºÒ±âµÕ2±¤¿ø.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ2_1±¤¿ø", PL"ºÒ±âµÕ2_1±¤¿ø.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ3±¤¿ø", PL"ºÒ±âµÕ3±¤¿ø.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ºÒ±âµÕ3_1±¤¿ø", PL"ºÒ±âµÕ3_1±¤¿ø.bmp", 1600, 300, 32, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("½ºÅ³¹Ù´ÚºÒ±¤¿ø", PL"¹Ù´ÚºÒ±¤¿ø.bmp", 1800, 150, 12, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®1±¤¿ø", PL"ÀÌÆåÆ®2±¤¿ø.bmp", 7000, 250, 28, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®2±¤¿ø", PL"ÀÌÆåÆ®1±¤¿ø.bmp", 6400, 160, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®3±¤¿ø", PL"ÀÌÆåÆ®3±¤¿ø.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®3_1±¤¿ø", PL"ÀÌÆåÆ®3_1±¤¿ø.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("½ºÅ³ÀÌÆåÆ®5±¤¿ø", PL"ÀÌÆåÆ®5±¤¿ø.bmp", 1200, 150, 8, 1, true, MAZEN);

	
	
	// ¿ÀÇÁ´×
	IMAGEMANAGER->addImage("¿ÀÇÁ´×¹è°æ", OPEN"OpeningBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("¿ÀÇÁ´×·Î°í", OPEN"OpeningLogo.bmp", 902, 234,true, MAZEN);
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×±Û¾¾1", OPEN"Opening_1.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×±Û¾¾2", OPEN"Opening_2.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×±Û¾¾3", OPEN"Opening_3.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×±Û¾¾4", OPEN"Opening_4.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×±Û¾¾5", OPEN"Opening_5.bmp", 5865, 218, 23, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×¼±ÅÃÃ¢1", OPEN"OpeningBtn1.bmp", 460, 217, 1, 4, true, RGBRED);
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×¼±ÅÃÃ¢2", OPEN"OpeningBtn2.bmp", 460, 217, 1, 4, true, RGBRED);
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×ºÒ²É", OPEN"OpeningFire.bmp", 11160, 256, 36, 1, true, RGB(0,0,0));
	IMAGEMANAGER->addFrameImage("¿ÀÇÁ´×³Ø½ºÆ®", OPEN"OpeningNext.bmp", 4335, 254, 17, 1, true, RGB(0,0,0));

	// 1¹ø ½Ã³ª¸®¿À
	IMAGEMANAGER->addImage("½Ã³ª¸®¿À¹è°æ", SCE"SceneBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("ÄÆ½Å¹è°æ", SCE"ScenarioBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("½Ã³ª¸®¿ÀÇüÁ¦", SCE"brother.bmp", 120, 45,true,MAZEN);

	// 2¹ø ½Ã³ª¸®¿À
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

	IMAGEMANAGER->addImage("»ì¶óµòÄ®", SCE"»ì¶óµòÄ®Âî¸§.bmp", 220, 90,true,MAZEN);
	IMAGEMANAGER->addImage("¹ö¸óÆ®Ä®Âñ¸²", SCE"¹ö¸óÆ®Ä®Âñ¸².bmp", 90, 90,true,MAZEN);
	IMAGEMANAGER->addImage("»ì¶óµò_¸ñ°ÉÀÌ", SCE"»ì¶óµò_¸ñ°ÉÀÌ.bmp", 90, 120,true,MAZEN);
	IMAGEMANAGER->addFrameImage("»ì¶óµò_ÈÖÆÄ¶÷", SCE"»ì¶óµò_ÈÖÆÄ¶÷.bmp", 180, 110,2,1,true,MAZEN);
	IMAGEMANAGER->addImage("¸ñ°ÉÀÌ»¯±è", SCE"¸ñ°ÉÀÌ»¯±è.bmp", 90, 100,true,MAZEN);
	IMAGEMANAGER->addFrameImage("¹ö¸óÆ®»ì¶óµò¿£µù", SCE"¹ö¸óÆ®»ì¶óµò¿£µù.bmp", 720, 120,6,1,true,MAZEN);

	// ÀüÅõ¸Ê
	IMAGEMANAGER->addImage("ÀüÅõ¸Ê", BAT"BattleMap.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("ÀüÅõ¸Ê2", BAT"BattleMap2.bmp", 2200, 2000);
	IMAGEMANAGER->addImage("ÇÈÃæ¹è°æ", BAT"ÇÈÃæ¹è°æ.bmp", 1800, 1696);

	// WorldMap
	IMAGEMANAGER->addImage("¿ùµå¸Ê¹è°æ", WM"WorldBG.bmp", 1446, 1074, true, MAZEN);
	IMAGEMANAGER->addImage("¿ùµå¸ÊÀüÅõ¸¶Å©", WM"WarMark.bmp", 70, 70, true, MAZEN);
	IMAGEMANAGER->addImage("¿ùµå¸Ê°ÅÁ¡¸¶Å©", WM"TeamDesign.bmp", 50, 50, true, MAZEN);
	IMAGEMANAGER->addImage("¿ùµå¸ÊÆÄµµ", WM"Wave.bmp", WINSIZE_X*2, WINSIZE_Y*2);
	IMAGEMANAGER->addImage("¿ùµå¸ÊÁö¿ª", WM"Location.bmp", 240, 101,true,MAZEN);
	IMAGEMANAGER->addFrameImage("¿ùµå¸Ê¹öÆ°", WM"Button.bmp", 332, 48,2,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("¿ùµå¸Ê°ÅÁ¡", WM"TeamRect.bmp", 2088, 150,18,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("¿ùµå¸Ê¼±ÅÃ", WM"circle.bmp", 1450, 47,25,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("¿ùµå¸ÊÇÁ·ÎÇÊ", WM"Profile.bmp", 800, 148,5,1,true,MAZEN);

	// Loading
	IMAGEMANAGER->addFrameImage("LoadingCharacter", "Resources/Images/Loading/LoadingCharacter.bmp", 12400, 200, 31, 1);
	IMAGEMANAGER->addImage("LoadingBlack", "Resources/Images/Loading/LoadingBlack.bmp", WINSIZE_X,WINSIZE_Y);

	//=========
	// »ç¿îµå
	// ========

	// 1¹ø ½Ã³ª¸®¿À
	SOUNDMANAGER->addSound("±â´Ù¸®°íÀÕ¾ù´Ù", SOUND"±â´Ù¸®°íÀÕ¾ù´Ù.mp3", false, false);
	SOUNDMANAGER->addSound("Áö³­¹ø¿£", SOUND"Áö³­¹ø¿£.mp3", false, false);
	SOUNDMANAGER->addSound("¼Î¶ó-»ì¶óµò", SOUND"¼Î¶ó-»ì¶óµò.mp3", false, false);
	SOUNDMANAGER->addSound("¼Î¶óÀÚµå°ÆÁ¤¸¶½Ã¿À", SOUND"¼Î¶óÀÚµå°ÆÁ¤¸¶½Ã¿À.mp3", false, false);
	SOUNDMANAGER->addSound("ÁÁ´ÙÄ®¹ö¸²", SOUND"ÁÁ´ÙÄ®¹ö¸².mp3", false, false);
	SOUNDMANAGER->addSound("¿ä»õµÎ°³", SOUND"¿ä»õµÎ°³.mp3", false, false);
	SOUNDMANAGER->addSound("¼Î¶ó°³ÀÇÄ¡", SOUND"¼Î¶ó°³ÀÇÄ¡.mp3", false, false);
	SOUNDMANAGER->addSound("»ì¶óµò¼³¸¶", SOUND"»ì¶óµò¼³¸¶.mp3", false, false);
	SOUNDMANAGER->addSound("¹ö¸óÆ®¿©¼úÅº", SOUND"¹ö¸óÆ®¿©¼úÅº.mp3", false, false);
	SOUNDMANAGER->addSound("»ì¶óµò¿Ö±×·±Áþ", SOUND"»ì¶óµò¿Ö±×·±Áþ.mp3", false, false);
	SOUNDMANAGER->addSound("¹ö¸óÆ®º¹¼ö´Ù", SOUND"¹ö¸óÆ®º¹¼ö´Ù.mp3", false, false);
	SOUNDMANAGER->addSound("»ì¶óµòÄ®¹ö¸²", SOUND"»ì¶óµòÄ®¹ö¸².mp3", false, false);

	
	// 2¹ø ½Ã³ª¸®¿À
	SOUNDMANAGER->addSound("¹ö¸óÆ®_Á×¿©¶ó", SOUND"¹ö¸óÆ®_Á×¿©¶ó.mp3", false, false);
	SOUNDMANAGER->addSound("¹ö¸óÆ®_±×°Í¸¸Àº", SOUND"¹ö¸óÆ®_±×°Í¸¸Àº.mp3", false, false);
	
	// ½ºÅ³
	SOUNDMANAGER->addSound("½ºÅ³±¸", SOUND"½ºÅ³±¸.mp3", false, false);
	SOUNDMANAGER->addSound("Å¬¸®¾î¼Ò¸®", SOUND"Å¬¸®¾î¼Ò¸®.mp3", false, false);
	SOUNDMANAGER->addSound("¸¶Áö¸·ÅÍÁú¶§", SOUND"¸¶Áö¸·ÅÍÁú¶§.mp3", false, false);
	SOUNDMANAGER->addSound("ÂïÀ»¶§", SOUND"ÂïÀ»¶§.mp3", false, false);
	SOUNDMANAGER->addSound("È­¿°±¸ÅÍÁú¶§", SOUND"È­¿°±¸ÅÍÁú¶§.mp3", false, false);
	SOUNDMANAGER->addSound("ÀûºÒ±âµÕ¶§", SOUND"ÀûºÒ±âµÕ¶§.mp3", false, false);
	SOUNDMANAGER->addSound("´ë°¢¼±ºÒ±âµÕ", SOUND"´ë°¢¼±ºÒ±âµÕ.mp3", false, false);
}