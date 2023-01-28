#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	// ���콺
	RECT _Mrc;
	int _frame;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void ImageInit(void);
	
	MainGame() {}
	~MainGame() {}
};