#pragma once
#include "GameNode.h"

class Player;
class Vermouth;


struct TIGER
{
	float x;
	float y;
	int alpha;
	int frame;
};

struct LIGHT
{
	int alpha;
	int pillarFrame;
	int groundFrame;
};

class Tiger : public GameNode
{
private:
	TIGER _ti;
	LIGHT _light;
	int _circleFrame;

	bitset<5> _step;


	int _tick;



public:
	HRESULT init(void);
	void release(void);
	void update(Player* _pl,Vermouth* _ve);
	void render(Player* _pl,Vermouth* _ve);


	Tiger() {}
	~Tiger() {}
};

