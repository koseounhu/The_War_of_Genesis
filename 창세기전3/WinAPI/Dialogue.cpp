#include "Stdafx.h"
#include "Dialogue.h"

HRESULT Dialogue::init(void)
{
	//// 1 
	//_dialogue.push_back({ "[ 버몬트 ]", 0, false, false });
	//
	//// 2 
	//_dialogue.push_back({ "기다리고 있었다.", 0, false, false });
	//
	//// 3
	//_dialogue.push_back({ "[ 살라딘 ]", 0, false, false });
	//
	//// 4
	//_dialogue.push_back({ "...", 0, false, false });
	//
	//// 5
	//_dialogue.push_back({ "[ 버몬트 ]", 0, false, false });
	//
	//// 6
	//_dialogue.push_back({ "지난번엔 운좋게 빠져 나갔지만 이번엔 힘들걸?", 0, false, false });

	//// 7
	//_dialogue.push_back({ "[ 셰라자드 ]",0, false, false });
	//
	//// 8
	//_dialogue.push_back({ "살라딘 ...", 0, false, false });
	//
	//// 9
	//_dialogue.push_back({ "[ 살라딘 ]", 0, false, false });
	//
	//// 10
	//_dialogue.push_back({ "셰라자드, 걱정 마시오. 곧 구해줄테니...",0, false, false });
	//
	//// 11
	//_dialogue.push_back({ "[ 버몬트 ]", 0, false, false });
	//
	//// 12
	//_dialogue.push_back({ "미안하네...허허", 0, false, false });
	//
	//// 13
	//_dialogue.push_back({ "흥! 네놈의 이야기는 들었다. 요새 두개가 네녀석에게 박살이 났더군. \n  자, 어서 그 칼을 버리지 않으면, 이 여자를 두 번 다시 볼수 없을 것\n이다.",0, false, false });
	//
	//// 14
	//_dialogue.push_back({ "[ 셰라자드 ]", 0, false, false });
	//
	//// 15
	//_dialogue.push_back({ "살라딘, 저는 개의치 마세요. \n 저는 이미 깨끗하지 못한 몸이에요.",0, false, false });
	//
	//// 16
	//_dialogue.push_back({ "[ 살라딘 ]",	0, false, false });
	//
	//// 17
	//_dialogue.push_back({ "설마...", 0, false, false });
	//
	//// 18
	//_dialogue.push_back({ "[ 버몬트 ]", 0, false, false });
	//
	//// 19
	//_dialogue.push_back({ "하하하! 투르제국의 여술탄과 팬드래건 왕가의 결합. \n 멋지지 않나? \n 단, 투르의 영토는 지참금으로 가지고 와야지.", 0, false, false });
	//
	//// 20
	//_dialogue.push_back({ "[ 살라딘 ]", 0, false, false });
	//
	//// 21
	//_dialogue.push_back({ "[ 버몬트 ]", 0, false, false });
	//
	//// 22
	//_dialogue.push_back({ "복수다! 네놈따위는 상상도 하지 못할 증오에 찬 복수!\n 자, 네놈과 떠들 시간따윈 없어. 어서 칼을 버리지 않으면 이 여자의 \n 목숨은 없다!", 0, false, false });
	//
	//// 23
	//_dialogue.push_back({ "[ 살라딘 ]", 0, false, false });
	//
	//// 24
	//_dialogue.push_back({ "좋다. 칼을 버리겠다.", 0, false, false });
	//
	//// 25
	//_dialogue.push_back({ "[ 셰라자드 ]", 0, false, false });
	//
	//// 26
	//_dialogue.push_back({ "살라딘님, 안되요! \n 왜 자신에 대해 얘기 안하시는 거죠 ?", 0, false, false });
	//
	//// 27
	//_dialogue.push_back({ "[ 살라딘 ]", 0, false, false });
	//
	//// 28
	//_dialogue.push_back({ "셰라자드, 나는 이미 과거는 잊었다오. \n 단지 한사람의 투르인으로 살아왔고 투르인으로 죽을것이오.", 0, false, false });
	//
	//// 29
	//_dialogue.push_back({ "[ 셰라자드 ]", 0, false, false });
	//
	//// 30
	//_dialogue.push_back({ "살라딘님! 저는 언제나 당신의 짐만 되는 군요. \n 하지만, 이젠 저도 용기를 내겠어요 ...", 0, false, false });
	//
	//// 31
	//_dialogue.push_back({ "[ 버몬트 ]", 0, false, false });
	//
	//// 32
	//_dialogue.push_back({ "제길, 할수없군.", 0, false, false });


	Json::Value root = JSONDATAMANAGER->loadJsonFile("Dialog.json");

	for (auto it = root["2번시나리오"].begin(); it != root["2번시나리오"].end(); it++)
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
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("맑은 고딕"));
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
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("맑은 고딕"));
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
