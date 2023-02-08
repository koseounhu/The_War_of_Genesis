#pragma once
#include "GameNode.h"

struct dia
{
	string _name;
	string _text;

	int tickName;
	int tickText;
	bool end;
};

class Dialogue : public GameNode
{
private:
	int _tick;
	vector<dia>_dia;

public:
	HRESULT init(int num);
	void release(void);
	void update(void);
	void render(void);

	void drawTextNoSkip(int num, int posX, int posY, int width, int height, int textsize, int r, int g, int b);

	Dialogue() {}
	~Dialogue() {}
};