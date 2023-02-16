#include "Stdafx.h"
#include "Dragon.h"
#include "Player.h"
#include "Enemy2.h"

HRESULT Dragon::init(void)
{
	// ¼ø¼­
	_phase = 0;

	// ÀüÃ¼Æ½
	_tick = 0;


	// ½ÃÀÛ±¸
	_frame = 0;
	
	//¸¶Áö¸· »ç¿îµå
	_endSound = 1.0f;
	return S_OK;
}

void Dragon::release(void)
{

}

void Dragon::update(void)
{
	// ½ºÅ³ »ç¿ëÇÒ °÷¿¡¼­ pl, em ¼³Á¤ÇØÁÖ°í »ç¿ëÇÒ°Í!!



	// ÀüÃ¼Æ½
	_tick++;


	

	// ½ºÅ³±¸
	if (_phase == 0)
	{
	 	if (!SOUNDMANAGER->isPlaySound("¸¶·æ½ÃÀÛ"))
	 		SOUNDMANAGER->play("¸¶·æ½ÃÀÛ", 1.0f);

		if (_tick % 8 == 0)
		{
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("½ºÅ³±¸")->getMaxFrameX())
			{
				_frame = 0;
				_phase++;
				for (int i = 0; i < _em.size(); i++)
				{
					_moveDragon.push_back(_em[i].y);
				}

			}
		}
	}

	// µå·¡°ï
	else if (_phase == 1)
	{
		if (!SOUNDMANAGER->isPlaySound("¸¶·æµå·¡°ï"))
			SOUNDMANAGER->play("¸¶·æµå·¡°ï", 1.0f);


		if (_tick % 12 == 0)
		{
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("µå·¡°ï")->getMaxFrameX())
			{
				_moveDragon.clear();
				_frame = 0;
				_phase++;
			}
		}
	}

	// ³«·Ú
	else if (_phase == 2)
	{
		if (!SOUNDMANAGER->isPlaySound("¸¶·æ³«·Ú"))
			SOUNDMANAGER->play("¸¶·æ³«·Ú", 1.0f);


		if (_tick % 5 == 0)
		{
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("ÅäÅ»¹ø°³")->getMaxFrameX())
			{
				_frame = 0;
				_phase++;
			}
		}
	}

	// ¹ø°³Æø¹ß
	else if (_phase == 3)
	{
		if (!SOUNDMANAGER->isPlaySound("¸¶·æÆø¹ß"))
			SOUNDMANAGER->play("¸¶·æÆø¹ß", 1.0f);
		
		if (_tick % 5 == 0)
		{
			
			_frame++;
			if (_frame > IMAGEMANAGER->findImage("¹ø°³Æø¹ß")->getMaxFrameX())
			{
				_frame = 0;
				_phase++;
			}
		}

	}
	else
	{
		// ½ºÅ³³¡ »ç¿ëÇÑ ¸ðµç º¯¼ö ÃÊ±âÈ­
		_tick = 0;
		_frame = 0;
		_phase = 0;
	}
}

void Dragon::render(void)
{
	// ½ºÅ³±¸
	if (_phase == 0)
	{
		IMAGEMANAGER->findImage("½ºÅ³±¸")->alphaFrameRender(getMemDC(), _pl.x-110, _pl.y-100, 80, _frame, 0);
	}

	// µå·¡°ï
	else if (_phase == 1)
	{
		for (int i = 0; i < _moveDragon.size(); i++)
		{
			IMAGEMANAGER->findImage("µå·¡°ï")->alphaFrameRender(getMemDC(), _em[i].x-100, _moveDragon[i]-100, 205, _frame, 0);
			_moveDragon[i] -= 3;
		}
	}

	// ³«·Ú
	else if (_phase == 2)
	{
		for (int i = 0; i < _em.size(); i++)
		{
			IMAGEMANAGER->findImage("ÅäÅ»¹ø°³")->alphaFrameRender(getMemDC(), _em[i].x-90, _em[i].y-400, 120, _frame, 0);
			IMAGEMANAGER->findImage("ÅäÅ»¹ø°³±¤¿ø")->alphaFrameRender(getMemDC(), _em[i].x-90, _em[i].y-400, 120, _frame, 0);
		}
	}

	// ¹ø°³Æø¹ß
	else if (_phase == 3)
	{
		for (int i = 0; i < _em.size(); i++)
		{
			IMAGEMANAGER->findImage("¹ø°³Ã¢")->alphaFrameRender(getMemDC(), _em[i].x-50 , _em[i].y-150 , 55, _frame, 0);
			IMAGEMANAGER->findImage("¹ø°³Ã¢±¤¿ø")->alphaFrameRender(getMemDC(), _em[i].x-50 , _em[i].y-150, 255, _frame, 0);

			IMAGEMANAGER->findImage("¹ø°³Æø¹ß")->alphaFrameRender(getMemDC(), _em[i].x-110 , _em[i].y-140 , 150, _frame, 0);
			IMAGEMANAGER->findImage("¹ø°³Æø¹ß±¤¿ø")->alphaFrameRender(getMemDC(), _em[i].x - 110, _em[i].y-140, 255, _frame, 0);
		}
	}







}
