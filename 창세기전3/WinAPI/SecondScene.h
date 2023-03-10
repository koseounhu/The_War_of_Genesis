#pragma once
#include "GameNode.h"
#include "Dialogue.h"



class SecondScene : public GameNode
{
private:
	Dialogue* _dia;
	bitset<10> _diaText;
	bitset<30> _diaSound;

	int _alpha;
	int _count;
	int _tick;
	int _frame;
	int _effect;

	int _neckX;
	int _neckY;
	int _neckFrame;
	
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

