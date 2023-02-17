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

#pragma region �ӽ�

#pragma endregion


HRESULT MainGame::init(void)
{
	GameNode::init(TRUE);
	ImageInit();

	SCENEMANAGER->addScene("������", new Openning);
	SCENEMANAGER->addScene("�����", new WorldMap);
	SCENEMANAGER->addScene("�ó�����", new Scenario);
	SCENEMANAGER->addScene("����", new Battle);
	SCENEMANAGER->addScene("����2", new Battle2);
	SCENEMANAGER->addScene("����3", new Battle3);
	SCENEMANAGER->addScene("1���ó�����", new firstCutScene);
	SCENEMANAGER->addScene("2���ó�����", new SecondScene);
	SCENEMANAGER->addScene("�ε�", new Loading);
	SCENEMANAGER->addScene("���λ���", new Store);
	SCENEMANAGER->addScene("�������", new WeaponShop);


	SCENEMANAGER->changScene("����3");


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

