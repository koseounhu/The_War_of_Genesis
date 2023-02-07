#include "Stdafx.h"
#include "DialogSample.h"

void DialogSample::init(void)
{
	dialogSetUp();
}

void DialogSample::dialogSetUp(Dialog2* pDia)
{
	//Json::Value root = JSONDATAMANAGER->loadJsonFile("Dialog.json");
	//for (auto it = root["2번시나리오"].begin(); it != root["2번시나리오"].end(); it++)
	//{
	//	if ((*it).isObject())
	//	{
	//		Dialog2* qdia = new Dialog2;
	//		qdia->init(
	//			(*it)["_name"].asString(),
	//			(*it)["_text"].asString());

	//		_dialog2.push(qdia);
	//	}
	//
	//}
	//Json::Value root = JSONDATAMANAGER->loadJsonFile("Dialog.json");

	//for (auto it = root["2번시나리오"].begin(); it != root["2번시나리오"].end(); it++)
	//{
	//	if ((*it).isObject())
	//	{
	//		_dia.push_back({ (*it)["_name"].asString(), (*it)["_text"].asString()});
	//	}
	//}
}
