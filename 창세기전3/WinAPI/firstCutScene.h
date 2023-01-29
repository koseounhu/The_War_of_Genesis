#pragma once
#include "GameNode.h"
class firstCutScene : public GameNode
{
private:
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

