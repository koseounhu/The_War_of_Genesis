#pragma once
#include "GameNode.h"
#include "Dialogue.h"

struct JSON
{
	int x;
	int y;
	string text;
	int tick;
};

class SecondScene : public GameNode
{
private:
	Dialogue* _dia;
	bitset<10> _diaText;
	bitset<10> _diaSound;

	int _alpha;
	int _count;
	int _tick;
	
	int _bigImageAlpha;


	int x, y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	SecondScene() {}
	~SecondScene() {}
};

