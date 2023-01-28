#include "Stdafx.h"
#include "JsonDataScene.h"

HRESULT JsonDataScene::init(void)
{
    _questSample = new QuestSample;
    _questSample->init();

    return S_OK;
}

void JsonDataScene::release(void)
{


}

void JsonDataScene::update(void)
{


}

void JsonDataScene::render(void)
{
    questPopUp();

}

void JsonDataScene::questPopUp()
{
    char str[256];
    queue<Quest*>* temp = _questSample->getQuest();
    Quest* node = temp->front();
    
    sprintf_s(str, "개요 : %s", node->getDesciription().c_str());
    TextOut(getMemDC(), 200, 150, str, strlen(str));

    sprintf_s(str, "몬스터 이름  : %s", node->getName().c_str());
    TextOut(getMemDC(), 200, 450, str, strlen(str));

    sprintf_s(str, "몬스터 이름 : %s", node->getMonsterName().c_str());
    TextOut(getMemDC(), 200, 400, str, strlen(str));

    sprintf_s(str, "처치해야 할 몬스터 : %d마리", node->getMonster());
    TextOut(getMemDC(), 200, 350, str, strlen(str));

    sprintf_s(str, "퀘스트 보상 아이템 : %s", node->getItem().c_str());
    TextOut(getMemDC(), 200, 300, str, strlen(str));
    
    sprintf_s(str, "보상 경험치 : %d exp", node->getExp());
    TextOut(getMemDC(), 200, 200, str, strlen(str));

    sprintf_s(str, "퀘스트 보상 골드 : %d gold", node->getGold());
    TextOut(getMemDC(), 200, 250, str, strlen(str));

    sprintf_s(str, "퀘스트 체크 : %s", node->getQuestCheck().c_str());
    TextOut(getMemDC(), 200, 500, str, strlen(str));

    sprintf_s(str, "퀘스트 스테이지 : %s", node->getQuestStage().c_str());
    TextOut(getMemDC(), 200, 550, str, strlen(str));

}

void JsonDataScene::currentQuest()
{


}
