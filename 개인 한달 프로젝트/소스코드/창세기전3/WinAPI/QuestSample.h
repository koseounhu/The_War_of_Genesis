#pragma once
#include "Quest.h"

#pragma region
/*
	▶ 큐 (queue)

	- 큐는 삽입과 삭제가 용이하다. -> 따라서 게임쪽에서 많이 사용한다. 가장 큰 장점
		ㄴ 리스트의 일종
	-  스택과는 다르게 가장 처음에 들어간 데이터가 처음에 나오는 FIO 구조를 가지고 있다.
	- 삽입이 일어나는 쪽을 뒤 (rear), 삭제가 일어나는 쪽을 앞 (front)라고 한다.

	stl 3대장 벡터 맵 리스트 -> 하지만 무겁다
	큐는 가볍다 그래서 많이 사용한다

	※ 큐를 사용하면 좋은 상황

	- 프린트 큐						자료구조의 일종, 한번에 출력해서 확인하는 작업에 사용 할 수있다.
	- CPU 스케쥴링					프로세서를 놀지 못하게 한다. 
	- 데이터 버퍼 확인 작업
	- BFS / DFS

	// 사용법
	- front()
		ㄴ 첫번째 요소 접근
	- back()
		ㄴ 마지막 요소에 접근
	- push()
		ㄴ 큐에 데이터 삽입
	- size()
		ㄴ 크기 반환
	- empty
		ㄴ 비어있는지 확인
*/
#pragma endregion

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

