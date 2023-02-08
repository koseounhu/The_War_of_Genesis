#pragma once
#include "GameNode.h"
#include "Dialogue.h"



class firstCutScene : public GameNode
{
private:
	Dialogue* _dia;
	bitset<30> _diaSound;
	
	bool _sal;
	bool _sara;
	bool _ver;
	bool _last;
	

	int _tick;
	int _BGalpha;

	int _diaCount;
	int _bigImageAlpha;

	int _bigImageAlpha2;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	firstCutScene() {}
	~firstCutScene() {}
};

