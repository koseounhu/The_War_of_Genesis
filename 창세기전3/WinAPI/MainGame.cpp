#include "Stdafx.h"
#include "MainGame.h"
#include "Openning.h"
#include "Scenario.h"
#include "Battle.h"
#include "Battle2.h"
#include "Battle3.h"
#include "firstCutScene.h"
#include "WorldMap.h"
#include "SecondScene.h"
#include "Loading.h"
#include "Store.h"
#include "WeaponShop.h"

#pragma region 임시

#pragma endregion


HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	ImageInit();

	SCENEMANAGER->addScene("오프닝", new Openning);
	SCENEMANAGER->addScene("월드맵", new WorldMap);
	SCENEMANAGER->addScene("시나리오", new Scenario);
	SCENEMANAGER->addScene("전투", new Battle);
	SCENEMANAGER->addScene("전투2", new Battle2);
	SCENEMANAGER->addScene("전투3", new Battle3);
	SCENEMANAGER->addScene("1번시나리오", new firstCutScene);
	SCENEMANAGER->addScene("2번시나리오", new SecondScene);
	SCENEMANAGER->addScene("로딩", new Loading);
	SCENEMANAGER->addScene("메인상점", new Store);
	SCENEMANAGER->addScene("무기상점", new WeaponShop);


	SCENEMANAGER->changScene("전투3");


	return S_OK;
}
void MainGame::release(void)
{
	GameNode::release();


}

void MainGame::update(void)
{
	GameNode::update();
	SCENEMANAGER->update();


}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	SCENEMANAGER->render();
	TIMEMANAGER->render(getMemDC());




	this->getBackBuffer()->render(getHDC());
}

