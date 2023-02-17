#pragma once
#include "GameNode.h"
#include "Dialogue.h"
#include "Item.h"

struct button
{
	int x;
	int y;
	RECT rc;
	bool click;
};

struct updown
{
	int x;
	int y;
	RECT rc;
	bool yFrame;
	int count;
};

struct itemIMAGE
{
	int x;
	int y;
};

struct buyCount
{
	int x;
	int y;
	int count;
};

struct shopAmount
{
	int x;
	int y;
	int amount;
};


class WeaponShop : public GameNode
{
private:
	button _button[4];
	updown _updown[14];
	itemIMAGE _itemIMAGE[7];
	shopAmount _shopAmount[7];
	buyCount _buyCount[7];




	Dialogue* _dia;
	Item* _item;
	
	int _buyPay;

	// ¸¶¿ì½º
	RECT _Mrc;
	int _frame;


public :
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	WeaponShop() {}
	~WeaponShop() {}
};

