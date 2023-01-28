#include "Stdafx.h"
#include "SoundScene.h"

HRESULT SoundScene::init(void)
{
	IMAGEMANAGER->addImage("데드 스페이스", "Resources/Images/Background/DeadSpace.bmp", WINSIZE_X, WINSIZE_Y);

	SOUNDMANAGER->addSound("찬란","Resources/Sounds/Golden.mp3", true, true);


	return S_OK;
}

void SoundScene::release(void)
{


}

void SoundScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->play("찬란", 1.0f);
	}	
	
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->stop("찬란");
	}	
	
	if (KEYMANAGER->isOnceKeyDown(VK_MBUTTON))
	{
		SOUNDMANAGER->pause("찬란");
	}	
	
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		SOUNDMANAGER->resume("찬란");
	}

	SOUNDMANAGER->update();


}

void SoundScene::render(void)
{
	IMAGEMANAGER->render("데드 스페이스", getMemDC());

}
