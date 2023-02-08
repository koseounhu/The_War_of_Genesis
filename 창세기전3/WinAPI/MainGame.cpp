#include "Stdafx.h"
#include "MainGame.h"
#include "Openning.h"
#include "Scenario.h"
#include "Battle.h"
#include "Battle2.h"
#include "firstCutScene.h"
#include "WorldMap.h"
#include "SecondScene.h"
#include "Loading.h"

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
	SCENEMANAGER->addScene("1번시나리오", new firstCutScene);
	SCENEMANAGER->addScene("2번시나리오", new SecondScene);
	SCENEMANAGER->addScene("로딩", new Loading);


	SCENEMANAGER->changScene("1번시나리오");


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
#pragma region 마우스
	ShowCursor(false);
	_Mrc = RectMake(_ptMouse.x, _ptMouse.y, 16, 24);
	_frame++;
	IMAGEMANAGER->findImage("마우스")->frameRender(getMemDC(), _ptMouse.x, _ptMouse.y, _frame, 0);
	if (_frame > 12)_frame = 0;
#pragma endregion



	this->getBackBuffer()->render(getHDC());
}

