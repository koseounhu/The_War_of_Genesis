#include "Stdafx.h"
#include "QuestSample.h"
// #include "Quest.h"

void QuestSample::init(void)
{
	questSetUp();



}

void QuestSample::questSetUp(Quest* pQuest)
{
	Json::Value root = JSONDATAMANAGER->loadJsonFile("Quest.json");
	for (auto it = root["Quest"].begin(); it != root["Quest"].end(); it++)
	{
		if ((*it).isObject())	
		{
			Quest* qQuest = new Quest;
			qQuest->init
			(
				(*it)["_name"].asString(),
				(*it)["_gold"].asInt(),
				(*it)["_exp"].asInt(),
				(*it)["_description"].asString(),
				(*it)["_item"].asString(),
				(*it)["_monster"].asInt(),
				(*it)["_questCheck"].asString(),
				(*it)["_monsterName"].asString(),
				(*it)["_questStage"].asString()
			);

			_quest.push(qQuest);

		}
	}
}
