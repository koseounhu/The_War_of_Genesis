#pragma once
#include "GameNode.h"

struct ITEM
{
	string _name;
	int _gold;
	int _have;
};
class Item : public GameNode
{
private:
	vector<ITEM>_item;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void rendItem(bool sell,int num, int posX, int posY, int textsize, int r, int g, int b, bool bold);

	string getItemName(int num) { return _item[num]._name; }

	int getItemGold(int num) { return _item[num]._gold; }

	int getItemAmount(int num) { return _item[num]._have; }
	void setItemAmount(int num,int amount) { _item[num]._have = amount; }
	
	Item() {}
	~Item() {}
};

