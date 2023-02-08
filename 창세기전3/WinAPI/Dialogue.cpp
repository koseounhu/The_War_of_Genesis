#include "Stdafx.h"
#include "Dialogue.h"

HRESULT Dialogue::init(int num)
{	
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Dialog.json");

	if (num == 2)
	{
		for (auto it = root["2번시나리오"].begin(); it != root["2번시나리오"].end(); it++)
		{
			if ((*it).isObject())
			{
				_dia.push_back({ (*it)["_name"].asString(), (*it)["_text"].asString() });
			}
		}
	}
	else if (num == 1)
	{

		for (auto it = root["1번시나리오"].begin(); it != root["1번시나리오"].end(); it++)
		{
			if ((*it).isObject())
			{
				_dia.push_back({ (*it)["_name"].asString(), (*it)["_text"].asString() });
			}
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
	char strToCharName[512];
	strcpy_s(strToCharName, _dia[num]._name.c_str());

		if (_tick % 3 == 0) _dia[num].tickName++;

		if (_dia[num].tickName > strlen(strToCharName))
			_dia[num].tickName = strlen(strToCharName);

		RECT rc = RectMake(posX, posY, width, height);
		SetBkMode(getMemDC(), 1);
		HFONT _currentFont = CreateFont(30, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0,
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


		char strToCharText[512];
		strcpy_s(strToCharText, _dia[num]._text.c_str());
		char tmp[512] = {};

		if (_tick % 3 == 0) _dia[num].tickText++;

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
