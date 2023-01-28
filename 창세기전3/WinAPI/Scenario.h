#pragma once
#include "GameNode.h"


class Scenario : public GameNode
{
private:

	RECT _rc;
	int _tick;

	// ���� ȭ��
	int _alpha;

	// �����ó����� �Ѿ���� �Ҳ�
	int _fireAlpha;

	// ���� �ó�����
	bool _next;


public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	Scenario(){}
	~Scenario() {}
};

