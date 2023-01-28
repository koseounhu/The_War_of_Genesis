#pragma once
#include "GameNode.h"
#include "QuestSample.h"

class JsonDataScene : public GameNode
{
private:

	QuestSample* _questSample;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	void questPopUp();
	void currentQuest();

	JsonDataScene() {}
	~JsonDataScene() {}
};

