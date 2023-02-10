#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Item.json");
	for (auto it = root["����"].begin(); it != root["����"].end(); it++)
	{
		if ((*it).isObject())
		{
			_item.push_back({ (*it)["_name"].asString(), (*it)["_gold"].asInt(),(*it)["_have"].asInt() });
		}
	}


	return S_OK;
}

void Item::release(void)
{
}

void Item::update(void)
{
}

void Item::render(void)
{
}

void Item::rendItem(int num, int posX, int posY, int textsize, int r, int g, int b, bool bold)
{
	char itemName[512];
	strcpy_s(itemName, _item[num]._name.c_str());
	FONTMANAGER->drawText(getMemDC(),posX,posY,textsize,r,g,b,"����",bold, itemName);
	FONTMANAGER->drawInt(getMemDC(), posX + 150, posY, textsize, r, g, b, "����", bold, (char*)_item[num]._gold);
	FONTMANAGER->drawText(getMemDC(),posX+200,posY,textsize,r,g,b,"����",bold, "Eld");

}
