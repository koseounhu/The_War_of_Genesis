#pragma once
#include "GameNode.h"

class Player;

class UI : public GameNode
{
private:
	bool _skillOn;
	bool _ui;
	bool _ability;
	bool _tileOn;
	bool _state;
	bool _total;
	bool _atk;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(Player* _pl);

	bool getTotalUI(void) { return _total; }

	bool getSkillState(void) { return _skillOn; }
	bool getUIState(void) { return _ui; }
	bool getAbilityState(void) { return _ability; }
	bool getTileState(void) { return _tileOn; }

	void setSkillState(bool skill) { _skillOn = skill; }
	void setUIState(bool ui) { _ui = ui; }
	void setAbilityState(bool ability) { _ability = ability; }
	void setTileState(bool tileOn) { _tileOn = tileOn; }

	// 일반 공격시 타일
	bool getAtkTile(void) { return _atk; }
	void setAtkTile(bool atk) { _atk = atk; }

	UI() {}
	~UI() {}
};

