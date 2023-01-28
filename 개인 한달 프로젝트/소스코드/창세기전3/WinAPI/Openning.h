#pragma once
#include "GameNode.h"

class Openning : public GameNode
{
private:
	// ����â
	RECT _rc[5];


	// ���
	int _BGalpha;
	int _count;

	// �Ҳ�
	int _fireAlpha;
	int _fireFame;
	bool _fire;

	// �Ѿ�� ȭ��
	bool _next;
	int _nextAlpha;

	// ��� �۾� ������
	int _textFrame;

	bitset<8>_textImage;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



	Openning() {}
	~Openning() {}
};

