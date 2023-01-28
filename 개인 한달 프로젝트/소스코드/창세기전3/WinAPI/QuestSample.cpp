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
		if ((*it).isObject())		// C++ 언어가 개정되면서 허용된 방식
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
	/*
		- asString()
			ㄴ asString 변수가 스트링 값이 아니거나 NULL 값이 들어있다면 별도의 예외없이 그냥 NULL을 반환한다.


		- ToString()
			ㄴ ToString 변수가 NULL 값이라면 예외 발생
	 */
}
