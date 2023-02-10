#pragma once
#include "GameNode.h"

struct MENU
{
	int x;
	int y;
	RECT rc[4];
	bool rcFrameCheck[4];

};
class Store : public GameNode
{
private:
	MENU _menu;

	bool _main;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);






	Store() {}
	~Store() {}
};

