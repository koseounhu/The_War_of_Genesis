#include "Stdafx.h"
#include "FontManager.h"


void FontManager::drawText(HDC hdc, int posX, int posY,int textSize, int r, int g, int b, char* txtStyle, bool txtBold, char* str)
{
	char tmpStr[512] = {};
	HFONT _currentFont;
	if (txtBold)
		_currentFont = CreateFont(textSize, 0, 0, 0, FW_HEAVY, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(txtStyle));
	else
		_currentFont = CreateFont(textSize, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(txtStyle));
	HFONT _oldFont = (HFONT)SelectObject(hdc, _currentFont);
	SetTextColor(hdc, RGB(r, g, b));
	wsprintf(tmpStr, "%s", str);
	TextOut(hdc, posX, posY, tmpStr, strlen(tmpStr));
	SelectObject(hdc, _oldFont);
	DeleteObject(_currentFont);
}

void FontManager::drawInt(HDC hdc, int posX, int posY, int textSize, int r, int g, int b, char* txtStyle, bool txtBold, char* str)
{
	char tmpStr[512] = {};
	HFONT _currentFont;
	if (txtBold)
		_currentFont = CreateFont(textSize, 0, 0, 0, FW_HEAVY, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(txtStyle));
	else
		_currentFont = CreateFont(textSize, 0, 0, 0, 0, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT(txtStyle));
	HFONT _oldFont = (HFONT)SelectObject(hdc, _currentFont);
	SetTextColor(hdc, RGB(r, g, b));
	wsprintf(tmpStr, "%d", str);
	TextOut(hdc, posX, posY, tmpStr, strlen(tmpStr));
	SelectObject(hdc, _oldFont);
	DeleteObject(_currentFont);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	HFONT font;
	HFONT oldFont;

	font = CreateFont
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0,
		TEXT(fontName)
	);

	oldFont = (HFONT)SelectObject(hdc, font);
	for (int i = 0; i < length; i++)
	{
		//TextOut(hdc, destX, destY, printString, length);
		Sleep(10);
	}

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextColor(hdc, RGB(0, 0, 0));
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printString, int length, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, color);

	HFONT font;
	HFONT oldFont;

	font = CreateFont
	(
		fontSize, 0, 0, 0, fontWeight,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0,
		TEXT(fontName)
	);

	oldFont = (HFONT)SelectObject(hdc, font);
	//TextOut(hdc, destX, destY, printString, length);

	SelectObject(hdc, oldFont);
	DeleteObject(font);
	SetTextColor(hdc, RGB(0, 0, 0));
}
