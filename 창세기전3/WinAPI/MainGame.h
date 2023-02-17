#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void ImageInit(void);
	
	MainGame() {}
	~MainGame() {}
};