#include "Stdafx.h"
#include "Quest.h"

void Quest::init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage)
{
	_name = name;
	_gold = gold;
	_exp = exp;
	_description = description;
	_item = item;
	_monster = monster;
	_questCheck = questCheck;
	_monsterName = monsterName;
	_questStage = questStage;
}
