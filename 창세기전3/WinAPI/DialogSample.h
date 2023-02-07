#pragma once
#include "Dialog2.h"

class Dialog2;
//struct dia
//{
//	string _name;
//	string _text;
//};

class DialogSample
{
private:
	queue<Dialog2*>_dialog2;

	//vector<dia>_dia;

public:

	void init(void);
	void dialogSetUp(Dialog2* pDia = nullptr);

	queue<Dialog2*>* getDialog2() { return &this->_dialog2; }

};

