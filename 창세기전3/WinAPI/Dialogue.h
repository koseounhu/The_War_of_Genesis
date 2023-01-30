#pragma once
#include "GameNode.h"

struct TagDialogue
{
	char* text;
	int tick;
	bool end;
	bool skip;
};

class Dialogue : public GameNode
{
private:
	int _tick;
	vector<TagDialogue> _dialogue;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void drawTextNoSkip(int num, int posX, int posY, int width, int height, int textsize, int r, int g, int b);
	bool getDialogueEnd(int num) { return _dialogue[num].end; }
	void setDialogueSkip(int num) { _dialogue[num].skip = true; }

	Dialogue() {}
	~Dialogue() {}
};