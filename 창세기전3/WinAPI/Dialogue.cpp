#include "Stdafx.h"
#include "Dialogue.h"

HRESULT Dialogue::init(void)
{
	// 1 
	_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	
	// 2 
	_dialogue.push_back({ "��ٸ��� �־���.", 0, false, false });
	
	// 3
	_dialogue.push_back({ "[ ���� ]", 0, false, false });
	
	// 4
	_dialogue.push_back({ "...", 0, false, false });
	
	// 5
	_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	
	// 6
	_dialogue.push_back({ "�������� ������ ���� �������� �̹��� �����?", 0, false, false });

	// 7
	_dialogue.push_back({ "[ �ζ��ڵ� ]",0, false, false });
	
	// 8
	_dialogue.push_back({ "���� ...", 0, false, false });
	
	// 9
	_dialogue.push_back({ "[ ���� ]", 0, false, false });
	
	// 10
	_dialogue.push_back({ "�ζ��ڵ�, ���� ���ÿ�. �� �������״�...",0, false, false });
	
	// 11
	_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	
	// 12
	_dialogue.push_back({ "�̾��ϳ�...����", 0, false, false });
	
	// 13
	_dialogue.push_back({ "��! �׳��� �̾߱�� �����. ��� �ΰ��� �׳༮���� �ڻ��� ������. \n  ��, � �� Į�� ������ ������, �� ���ڸ� �� �� �ٽ� ���� ���� ��\n�̴�.",0, false, false });
	
	// 14
	_dialogue.push_back({ "[ �ζ��ڵ� ]", 0, false, false });
	
	// 15
	_dialogue.push_back({ "����, ���� ����ġ ������. \n ���� �̹� �������� ���� ���̿���.",0, false, false });
	
	// 16
	_dialogue.push_back({ "[ ���� ]",	0, false, false });
	
	// 17
	_dialogue.push_back({ "����...", 0, false, false });
	
	// 18
	_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	
	// 19
	_dialogue.push_back({ "������! ���������� ����ź�� �ҵ巡�� �հ��� ����. \n ������ �ʳ�? \n ��, ������ ����� ���������� ������ �;���.", 0, false, false });
	
	// 20
	_dialogue.push_back({ "[ ���� ]", 0, false, false });
	
	// 21
	_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	
	// 22
	_dialogue.push_back({ "������! �׳������ ��� ���� ���� ������ �� ����!\n ��, �׳�� ���� �ð����� ����. � Į�� ������ ������ �� ������ \n ����� ����!", 0, false, false });
	
	// 23
	_dialogue.push_back({ "[ ���� ]", 0, false, false });
	
	// 24
	_dialogue.push_back({ "����. Į�� �����ڴ�.", 0, false, false });
	
	// 25
	_dialogue.push_back({ "[ �ζ��ڵ� ]", 0, false, false });
	
	// 26
	_dialogue.push_back({ "�����, �ȵǿ�! \n �� �ڽſ� ���� ��� ���Ͻô� ���� ?", 0, false, false });
	
	// 27
	_dialogue.push_back({ "[ ���� ]", 0, false, false });
	
	// 28
	_dialogue.push_back({ "�ζ��ڵ�, ���� �̹� ���Ŵ� �ؾ��ٿ�. \n ���� �ѻ���� ���������� ��ƿ԰� ���������� �������̿�.", 0, false, false });
	
	// 29
	_dialogue.push_back({ "[ �ζ��ڵ� ]", 0, false, false });
	
	// 30
	_dialogue.push_back({ "�����! ���� ������ ����� ���� �Ǵ� ����. \n ������, ���� ���� ��⸦ ���ھ�� ...", 0, false, false });
	
	// 31
	_dialogue.push_back({ "[ ����Ʈ ]", 0, false, false });
	
	// 32
	_dialogue.push_back({ "����, �Ҽ�����.", 0, false, false });

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
	if (!_dialogue[num].skip)
	{
		if (_tick % 3 == 0) _dialogue[num].tick++;

		if (_dialogue[num].tick > strlen(_dialogue[num].text))
			_dialogue[num].tick = strlen(_dialogue[num].text);

		char tmpStr[512] = {};
		RECT rc = RectMake(posX, posY, width, height);
		SetBkMode(getMemDC(), 1);
		HFONT _currentFont = CreateFont(textsize, 0, 0, 0, FW_SEMIBOLD, 0, 0, 0,
			HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("���� ���"));
		HFONT _oldFont = (HFONT)SelectObject(getMemDC(), _currentFont);
		SetTextColor(getMemDC(), RGB(r, g, b));

		for (int i = 0; i < _dialogue[num].tick; i++)
		{
			tmpStr[i] = _dialogue[num].text[i];
		}

		DrawText(getMemDC(), tmpStr, -1, &rc, DT_LEFT | DT_WORDBREAK);
		SelectObject(getMemDC(), _oldFont);
		DeleteObject(_currentFont);

		if (_dialogue[num].tick == strlen(_dialogue[num].text)) _dialogue[num].end = true;
	}
}
