#pragma once
#include "Quest.h"


class Quest;

class QuestSample
{
private:
	queue<Quest*> _quest;

public:
	void init(void);
	void questSetUp(Quest* pQuest = nullptr);

	queue<Quest*>* getQuest() { return &this->_quest; }



	QuestSample() {}
	~QuestSample() {}
};

