#pragma once
#include "SingletonBase.h"

class FontManager : public SingletonBase<FontManager>
{
public:
	void drawText(HDC hdc, int posX, int posY,int textSize, int r, int g, int b, char* txtStyle, bool txtBold, char* str);
	void drawInt(HDC hdc, int posX, int posY, int textSize, int r, int g, int b, char* txtStyle, bool txtBold, char* str);
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR printString, int length, COLORREF color);
	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWeight, LPCWSTR* printString, int length, COLORREF color);

	FontManager() {}
	~FontManager() {}
};

