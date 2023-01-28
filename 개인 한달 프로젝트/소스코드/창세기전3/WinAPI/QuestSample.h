#pragma once
#include "Quest.h"

#pragma region
/*
	�� ť (queue)

	- ť�� ���԰� ������ �����ϴ�. -> ���� �����ʿ��� ���� ����Ѵ�. ���� ū ����
		�� ����Ʈ�� ����
	-  ���ð��� �ٸ��� ���� ó���� �� �����Ͱ� ó���� ������ FIO ������ ������ �ִ�.
	- ������ �Ͼ�� ���� �� (rear), ������ �Ͼ�� ���� �� (front)��� �Ѵ�.

	stl 3���� ���� �� ����Ʈ -> ������ ���̴�
	ť�� ������ �׷��� ���� ����Ѵ�

	�� ť�� ����ϸ� ���� ��Ȳ

	- ����Ʈ ť						�ڷᱸ���� ����, �ѹ��� ����ؼ� Ȯ���ϴ� �۾��� ��� �� ���ִ�.
	- CPU �����층					���μ����� ���� ���ϰ� �Ѵ�. 
	- ������ ���� Ȯ�� �۾�
	- BFS / DFS

	// ����
	- front()
		�� ù��° ��� ����
	- back()
		�� ������ ��ҿ� ����
	- push()
		�� ť�� ������ ����
	- size()
		�� ũ�� ��ȯ
	- empty
		�� ����ִ��� Ȯ��
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

