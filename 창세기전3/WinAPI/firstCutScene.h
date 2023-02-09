#pragma once
#include "GameNode.h"
#include "Dialogue.h"



class firstCutScene : public GameNode
{
private:
	Dialogue* _dia;
	bitset<40> _diaSound;
	
	bool _sal;
	bool _sara;
	bool _ver;
	bool _last;
	bool _die;

	int _tick;
	int _BGalpha;

	int _diaCount;
	int _bigImageAlpha;

	int _bigImageAlpha2;

	int _lastAlpha;
	int _saraFrame;

	int _verX, _verY;
	int _verFrame;
	int _dieFrame;

	int _salX;
	int _salY;
	int _salFrame;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	firstCutScene() {}
	~firstCutScene() {}
};

