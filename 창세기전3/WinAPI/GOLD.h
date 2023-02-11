#pragma once
#include "SingletonBase.h"

class GOLD : public SingletonBase <GOLD>
{
private:

	int _gold = 1000000;



public:

	int getGold(void) { return _gold; }
	void setGold(int gold) { _gold = gold; }

	GOLD() {}
	~GOLD() {}
};

