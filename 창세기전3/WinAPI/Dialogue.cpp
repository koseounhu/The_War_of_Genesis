#include "Stdafx.h"
#include "Dialogue.h"

HRESULT Dialogue::init(void)
{
	//// 1 
	//_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	//
	//// 2 
	//_dialogue.push_back({ "��ٸ��� �־���.", 0, false, false });
	//
	//// 3
	//_dialogue.push_back({ "[ ���� ]", 0, false, false });
	//
	//// 4
	//_dialogue.push_back({ "...", 0, false, false });
	//
	//// 5
	//_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	//
	//// 6
	//_dialogue.push_back({ "�������� ������ ���� �������� �̹��� �����?", 0, false, false });

	//// 7
	//_dialogue.push_back({ "[ �ζ��ڵ� ]",0, false, false });
	//
	//// 8
	//_dialogue.push_back({ "���� ...", 0, false, false });
	//
	//// 9
	//_dialogue.push_back({ "[ ���� ]", 0, false, false });
	//
	//// 10
	//_dialogue.push_back({ "�ζ��ڵ�, ���� ���ÿ�. �� �������״�...",0, false, false });
	//
	//// 11
	//_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	//
	//// 12
	//_dialogue.push_back({ "�̾��ϳ�...����", 0, false, false });
	//
	//// 13
	//_dialogue.push_back({ "��! �׳��� �̾߱�� �����. ��� �ΰ��� �׳༮���� �ڻ��� ������. \n  ��, � �� Į�� ������ ������, �� ���ڸ� �� �� �ٽ� ���� ���� ��\n�̴�.",0, false, false });
	//
	//// 14
	//_dialogue.push_back({ "[ �ζ��ڵ� ]", 0, false, false });
	//
	//// 15
	//_dialogue.push_back({ "����, ���� ����ġ ������. \n ���� �̹� �������� ���� ���̿���.",0, false, false });
	//
	//// 16
	//_dialogue.push_back({ "[ ���� ]",	0, false, false });
	//
	//// 17
	//_dialogue.push_back({ "����...", 0, false, false });
	//
	//// 18
	//_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	//
	//// 19
	//_dialogue.push_back({ "������! ���������� ����ź�� �ҵ巡�� �հ��� ����. \n ������ �ʳ�? \n ��, ������ ����� ���������� ������ �;���.", 0, false, false });
	//
	//// 20
	//_dialogue.push_back({ "[ ���� ]", 0, false, false });
	//
	//// 21
	//_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	//
	//// 22
	//_dialogue.push_back({ "������! �׳������ ��� ���� ���� ������ �� ����!\n ��, �׳�� ���� �ð����� ����. � Į�� ������ ������ �� ������ \n ����� ����!", 0, false, false });
	//
	//// 23
	//_dialogue.push_back({ "[ ���� ]", 0, false, false });
	//
	//// 24
	//_dialogue.push_back({ "����. Į�� �����ڴ�.", 0, false, false });
	//
	//// 25
	//_dialogue.push_back({ "[ �ζ��ڵ� ]", 0, false, false });
	//
	//// 26
	//_dialogue.push_back({ "�����, �ȵǿ�! \n �� �ڽſ� ���� ��� ���Ͻô� ���� ?", 0, false, false });
	//
	//// 27
	//_dialogue.push_back({ "[ ���� ]", 0, false, false });
	//
	//// 28
	//_dialogue.push_back({ "�ζ��ڵ�, ���� �̹� ���Ŵ� �ؾ��ٿ�. \n ���� �ѻ���� ���������� ��ƿ԰� ���������� �������̿�.", 0, false, false });
	//
	//// 29
	//_dialogue.push_back({ "[ �ζ��ڵ� ]", 0, false, false });
	//
	//// 30
	//_dialogue.push_back({ "�����! ���� ������ ����� ���� �Ǵ� ����. \n ������, ���� ���� ��⸦ ���ھ�� ...", 0, false, false });
	//
	//// 31
	//_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	//
	//// 32
	//_dialogue.push_back({ "����, �Ҽ�����.", 0, false, false });


	Json::Value root = JSONDATAMANAGER->loadJsonFile("Dialog.json");

	for (auto it = root["2���ó�����"].begin(); it != root["2���ó�����"].end(); it++)
	{
		if ((*it).isObject())
		{
			_dia.push_back({ (*it)["_name"].asString(), (*it)["_text"].asString() });
		}
	}

	return S_OK;
}

void Dialogue::release(void)
{
}

void Dialogue::update(void)
{
	_tick++;
}

void Dialogue::render(void)
{
}


void Dialogue::drawTextNoSkip(int num, int posX, int posY, int width, int height, int textsize, int r, int g, int b)
{
	char strToCharName[128];
	strcpy_s(strToCharName, _dia[num]._name.c_str());

		if (_tick % 3 == 0) _dia[num].tickName++;

		if (_dia[num].tickName > strlen(strToCharName))
			_dia[num].tickName = strlen(strToCharName);

		RECT rc = RectMake(posX, posY, width, height);
		SetBkMode(getMemDC(), 1);
		HFONT _currentFont = CreateFont(25, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("���� ���"));
		HFONT _oldFont = (HFONT)SelectObject(getMemDC(), _currentFont);
		SetTextColor(getMemDC(), RGB(49, 255, 205));

		for (int i = 0; i < _dia[num].tickName; i++)
		{
			strToCharName[i] = _dia[num]._name[i];
		}


		DrawText(getMemDC(), strToCharName, -1, &rc, DT_LEFT | DT_WORDBREAK);
		SelectObject(getMemDC(), _oldFont);
		DeleteObject(_currentFont);


// ============================================================================================

		if (_tick % 5 == 0) _dia[num].tickText++;

		char strToCharText[128];
		strcpy_s(strToCharText, _dia[num]._text.c_str());
		char tmp[128] = {};

		if (_dia[num].tickText > strlen(strToCharText))
			_dia[num].tickText = strlen(strToCharText);

		RECT rcA = RectMake(posX+35, posY+30, width, height);
		SetBkMode(getMemDC(), 1);
		HFONT _currentFont2 = CreateFont(textsize, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("���� ���"));
		HFONT _oldFont2 = (HFONT)SelectObject(getMemDC(), _currentFont2);
		SetTextColor(getMemDC(), RGB(r, g, b));

		for (int i = 0; i < _dia[num].tickText; i++)
		{
			tmp[i] = strToCharText[i];
		}


		DrawText(getMemDC(), tmp, -1, &rcA, DT_LEFT | DT_WORDBREAK);
		SelectObject(getMemDC(), _oldFont2);
		DeleteObject(_currentFont2);

		if (_dia[num].tickText == strlen(tmp)) _dia[num].end = true;
}
