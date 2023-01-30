#pragma once
#include "GameNode.h"
#include "Dialogue.h"

class firstCutScene : public GameNode
{
private:
	Dialogue* _da;

	int _BgAlpha;
	int _frame;
	int _tick;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	firstCutScene() {}
	~firstCutScene() {}
};

