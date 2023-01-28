#pragma once

enum QUEST_TYPE
{
	QUEST_STAGE_1,


};


class Quest
{
protected:

	int _exp;
	int _gold;
	int _monster;

	string _name;
	string _description;
	string _item;
	string _questCheck;
	string _monsterName;
	string _questStage;

	QUEST_TYPE _questType;



public:

	void init(string name, int gold, int exp, string description, string item, int monster, string questCheck, string monsterName, string questStage);

#pragma region 접근자 함수
	int getExp() { return this->_exp; }
	int getGold() { return this->_gold; }
	int getMonster() { return this->_monster; }

	string getName() { return this->_name; }
	string getDesciription() { return this->_description; }
	string getItem() { return this->_item; }
	string getQuestCheck() { return this->_questCheck; }
	string getMonsterName() { return this->_monsterName; }
	string getQuestStage() { return this->_questStage; }

	QUEST_TYPE getType() { return this->_questType; }
#pragma endregion



	Quest() {}
	~Quest() {}
};

