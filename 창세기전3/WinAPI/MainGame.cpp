#include "Stdafx.h"
#include "MainGame.h"
#include "Openning.h"
#include "Scenario.h"
#include "Battle.h"
#include "Battle2.h"
#include "firstCutScene.h"
#include "WorldMap.h"


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
	SCENEMANAGER->addScene("�ó������ƾ�", new firstCutScene);


	SCENEMANAGER->changScene("����");


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
#pragma region ���콺
	ShowCursor(false);
	_Mrc = RectMake(_ptMouse.x, _ptMouse.y, 16, 24);
	_frame++;
	IMAGEMANAGER->findImage("���콺")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frame, 0);
	if (_frame > 12)_frame = 0;
#pragma endregion



	this->getBackBuffer()->render(getHDC());
}

