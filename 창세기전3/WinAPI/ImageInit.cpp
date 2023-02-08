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
	// �ӽ� 1.5�辿 ������
	IMAGEMANAGER->addFrameImage("�ζ�����", SCE"�ζ�����.bmp", 5520, 150,23,1,true,MAZEN);
	IMAGEMANAGER->addImage("�ӽ�2", SCE"�ӽ�2.bmp", 250, 250, true,MAZEN);
	IMAGEMANAGER->addImage("����Ʈ", SCE"����Ʈ.bmp", 390, 640, true,MAZEN);
	IMAGEMANAGER->addImage("����", SCE"����.bmp", 600, 680, true,MAZEN);
	IMAGEMANAGER->addImage("�ζ�", SCE"�ζ�.bmp", 625, 622, true,MAZEN);

	// ����
	IMAGEMANAGER->addImage("��������", BG"blackness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�Ͼ����", BG"whitness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("��������", BG"redness.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�ó�����Ŭ����", BG"clear.bmp", WINSIZE_X, 100);
	IMAGEMANAGER->addImage("Ŭ�����", BG"clear����.bmp", WINSIZE_X, 100,true,MAZEN);
	IMAGEMANAGER->addImage("Ŭ�����ؽ�Ʈ", BG"cleartxt.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("Ŭ�����ؽ�Ʈ����", BG"cleartxt����.bmp", 480, 54,true,MAZEN);
	IMAGEMANAGER->addImage("���̾�α�â", SCE"Dialogue.bmp", 818, 178);
	IMAGEMANAGER->addImage("�����Ƽâ", OBJ"SkillBox.bmp", 208, 91);
	IMAGEMANAGER->addImage("���Ÿ��", OBJ"blueTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("����Ÿ��", OBJ"redTile.bmp", 40, 32);
	IMAGEMANAGER->addImage("���Ÿ��", OBJ"orangeTile.bmp", 40, 32);
	IMAGEMANAGER->addFrameImage("��ųUI", OBJ"PersonalBox.bmp", 416, 60,4,2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���콺Ÿ��", OBJ"MoveCursor.bmp", 240, 32,6,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("�����Ƽ��ư", OBJ"abilityButton.bmp", 34, 17,2,1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("���콺", OBJ"mouse.bmp", 228, 24, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("�׸���", OBJ"Shadow.bmp", 50, 25, true, RGB(255, 0, 255));

	// UI
	IMAGEMANAGER->addImage("UI��������â", UI"state.bmp", 218, 384);



	//�÷��̾�
	IMAGEMANAGER->addFrameImage("����_�ȱ�", PL"����_walk.bmp", 720, 360, 6, 4, true,MAZEN );
	IMAGEMANAGER->addFrameImage("����_���", PL"����_idle.bmp", 240, 400, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����_����", PL"����_atk.bmp", 700, 440, 5, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����_��ų", PL"����_��ų.bmp", 800, 100, 8, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����_�ǰ���", PL"�ǰ���.bmp", 1224, 80, 12, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����_�ǰݿ�", PL"�ǰݿ�.bmp", 1224, 80, 12, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("����Ʈ_�ȱ�", PL"����Ʈ_WALK.bmp", 900, 360, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����Ʈ_���", PL"����Ʈ_IDLE.bmp", 270, 360, 3, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����Ʈ_����", PL"����Ʈ_ATK.bmp", 900, 480, 6, 4, true, MAZEN);
	IMAGEMANAGER->addFrameImage("����Ʈ_�ǰ�", PL"����Ʈ_�ǰ�.bmp", 600, 132, 12, 2, true, MAZEN);

	// ��
	IMAGEMANAGER->addFrameImage("��1", PL"��1.bmp", 240, 160, 3, 2, true, MAZEN);


	// ��ų
	IMAGEMANAGER->addFrameImage("��ų��", PL"��ų��.bmp", 6325, 192, 25, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��1", PL"�ұ��1.bmp", 1600, 230, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("��ų�ұ��1_1", PL"�ұ��1_1.bmp", 1600, 230, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("��ų�ұ��2", PL"�ұ��2.bmp", 1600, 300, 30, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("��ų�ұ��2_1", PL"�ұ��2_1.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("��ų�ұ��3", PL"�ұ��3.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("��ų�ұ��3_1", PL"�ұ��3_1.bmp", 1600, 300, 32, 1, true, SKILL);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ1", PL"����Ʈ2.bmp", 7000, 250, 28, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ2", PL"����Ʈ1.bmp", 6400, 160, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ3", PL"����Ʈ3.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ3_1", PL"����Ʈ3_1.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ3_1", PL"����Ʈ3_1.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ4", PL"����Ʈ4.bmp", 3600, 150, 24, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ5", PL"����Ʈ5.bmp", 1200, 150, 8, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("��ų��ƼŬ1", PL"��ƼŬ1.bmp", 300, 20, 15, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų��ƼŬ2", PL"��ƼŬ2.bmp", 450, 30, 15, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų��ƼŬ3", PL"��ƼŬ3.bmp", 750, 50, 15, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("��ų�ٴں�", PL"�ٴں�.bmp", 1800, 150, 12, 1, true, MAZEN);

	// ����
	IMAGEMANAGER->addFrameImage("��ų������", PL"��ų������.bmp", 6325, 192, 25, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��1����", PL"�ұ��1����.bmp", 1600, 230, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��1_1����", PL"�ұ��1_1����.bmp", 1600, 230, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��2����", PL"�ұ��2����.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��2_1����", PL"�ұ��2_1����.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��3����", PL"�ұ��3����.bmp", 1600, 300, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų�ұ��3_1����", PL"�ұ��3_1����.bmp", 1600, 300, 32, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("��ų�ٴںұ���", PL"�ٴںұ���.bmp", 1800, 150, 12, 1, true, MAZEN);

	IMAGEMANAGER->addFrameImage("��ų����Ʈ1����", PL"����Ʈ2����.bmp", 7000, 250, 28, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ2����", PL"����Ʈ1����.bmp", 6400, 160, 32, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ3����", PL"����Ʈ3����.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ3_1����", PL"����Ʈ3_1����.bmp", 1150, 150, 23, 1, true, MAZEN);
	IMAGEMANAGER->addFrameImage("��ų����Ʈ5����", PL"����Ʈ5����.bmp", 1200, 150, 8, 1, true, MAZEN);

	
	
	// ������
	IMAGEMANAGER->addImage("�����׹��", OPEN"OpeningBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�����׷ΰ�", OPEN"OpeningLogo.bmp", 902, 234,true, MAZEN);
	IMAGEMANAGER->addFrameImage("�����ױ۾�1", OPEN"Opening_1.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("�����ױ۾�2", OPEN"Opening_2.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("�����ױ۾�3", OPEN"Opening_3.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("�����ױ۾�4", OPEN"Opening_4.bmp", 7650, 218, 30, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("�����ױ۾�5", OPEN"Opening_5.bmp", 5865, 218, 23, 1, true, RGB(0, 99, 0));
	IMAGEMANAGER->addFrameImage("�����׼���â1", OPEN"OpeningBtn1.bmp", 460, 217, 1, 4, true, RGBRED);
	IMAGEMANAGER->addFrameImage("�����׼���â2", OPEN"OpeningBtn2.bmp", 460, 217, 1, 4, true, RGBRED);
	IMAGEMANAGER->addFrameImage("�����׺Ҳ�", OPEN"OpeningFire.bmp", 11160, 256, 36, 1, true, RGB(0,0,0));
	IMAGEMANAGER->addFrameImage("�����׳ؽ�Ʈ", OPEN"OpeningNext.bmp", 4335, 254, 17, 1, true, RGB(0,0,0));

	// 1�� �ó�����
	IMAGEMANAGER->addImage("�ó��������", SCE"SceneBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�ƽŹ��", SCE"ScenarioBG.bmp", WINSIZE_X, WINSIZE_Y);
	IMAGEMANAGER->addImage("�ó���������", SCE"brother.bmp", 120, 45,true,MAZEN);

	// 2�� �ó�����
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

	IMAGEMANAGER->addImage("����Į", SCE"����Į�.bmp", 220, 90,true,MAZEN);
	IMAGEMANAGER->addImage("����ƮĮ��", SCE"����ƮĮ��.bmp", 90, 90,true,MAZEN);
	IMAGEMANAGER->addImage("����_�����", SCE"����_�����.bmp", 90, 120,true,MAZEN);
	IMAGEMANAGER->addFrameImage("����_���Ķ�", SCE"����_���Ķ�.bmp", 180, 110,2,1,true,MAZEN);
	IMAGEMANAGER->addImage("����̻���", SCE"����̻���.bmp", 90, 100,true,MAZEN);
	IMAGEMANAGER->addFrameImage("����Ʈ���򿣵�", SCE"����Ʈ���򿣵�.bmp", 720, 120,6,1,true,MAZEN);

	// ������
	IMAGEMANAGER->addImage("������", BAT"BattleMap.bmp", 1600, 1800);
	IMAGEMANAGER->addImage("������2", BAT"BattleMap2.bmp", 2200, 2000);
	IMAGEMANAGER->addImage("������", BAT"������.bmp", 1800, 1696);

	// WorldMap
	IMAGEMANAGER->addImage("����ʹ��", WM"WorldBG.bmp", 1446, 1074, true, MAZEN);
	IMAGEMANAGER->addImage("�����������ũ", WM"WarMark.bmp", 70, 70, true, MAZEN);
	IMAGEMANAGER->addImage("����ʰ�����ũ", WM"TeamDesign.bmp", 50, 50, true, MAZEN);
	IMAGEMANAGER->addImage("������ĵ�", WM"Wave.bmp", WINSIZE_X*2, WINSIZE_Y*2);
	IMAGEMANAGER->addImage("���������", WM"Location.bmp", 240, 101,true,MAZEN);
	IMAGEMANAGER->addFrameImage("����ʹ�ư", WM"Button.bmp", 332, 48,2,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("����ʰ���", WM"TeamRect.bmp", 2088, 150,18,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("����ʼ���", WM"circle.bmp", 1450, 47,25,1,true,MAZEN);
	IMAGEMANAGER->addFrameImage("�����������", WM"Profile.bmp", 800, 148,5,1,true,MAZEN);

	// Loading
	IMAGEMANAGER->addFrameImage("LoadingCharacter", "Resources/Images/Loading/LoadingCharacter.bmp", 12400, 200, 31, 1);
	IMAGEMANAGER->addImage("LoadingBlack", "Resources/Images/Loading/LoadingBlack.bmp", WINSIZE_X,WINSIZE_Y);

	//=========
	// ����
	// ========

	// 1�� �ó�����
	SOUNDMANAGER->addSound("��ٸ����վ���", SOUND"��ٸ����վ���.mp3", false, false);
	SOUNDMANAGER->addSound("��������", SOUND"��������.mp3", false, false);
	SOUNDMANAGER->addSound("�ζ�-����", SOUND"�ζ�-����.mp3", false, false);
	SOUNDMANAGER->addSound("�ζ��ڵ�������ÿ�", SOUND"�ζ��ڵ�������ÿ�.mp3", false, false);
	SOUNDMANAGER->addSound("����Į����", SOUND"����Į����.mp3", false, false);
	SOUNDMANAGER->addSound("����ΰ�", SOUND"����ΰ�.mp3", false, false);
	SOUNDMANAGER->addSound("�ζ���ġ", SOUND"�ζ���ġ.mp3", false, false);
	SOUNDMANAGER->addSound("���򼳸�", SOUND"���򼳸�.mp3", false, false);
	SOUNDMANAGER->addSound("����Ʈ����ź", SOUND"����Ʈ����ź.mp3", false, false);
	SOUNDMANAGER->addSound("����ֱ׷���", SOUND"����ֱ׷���.mp3", false, false);
	SOUNDMANAGER->addSound("����Ʈ������", SOUND"����Ʈ������.mp3", false, false);
	SOUNDMANAGER->addSound("����Į����", SOUND"����Į����.mp3", false, false);

	
	// 2�� �ó�����
	SOUNDMANAGER->addSound("����Ʈ_�׿���", SOUND"����Ʈ_�׿���.mp3", false, false);
	SOUNDMANAGER->addSound("����Ʈ_�װ͸���", SOUND"����Ʈ_�װ͸���.mp3", false, false);
	
	// ��ų
	SOUNDMANAGER->addSound("��ų��", SOUND"��ų��.mp3", false, false);
	SOUNDMANAGER->addSound("Ŭ����Ҹ�", SOUND"Ŭ����Ҹ�.mp3", false, false);
	SOUNDMANAGER->addSound("������������", SOUND"������������.mp3", false, false);
	SOUNDMANAGER->addSound("������", SOUND"������.mp3", false, false);
	SOUNDMANAGER->addSound("ȭ����������", SOUND"ȭ����������.mp3", false, false);
	SOUNDMANAGER->addSound("���ұ�ն�", SOUND"���ұ�ն�.mp3", false, false);
	SOUNDMANAGER->addSound("�밢���ұ��", SOUND"�밢���ұ��.mp3", false, false);
}