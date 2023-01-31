#include "Stdafx.h"
#include "Skill.h"

HRESULT Skill::init(void)
{
	_skill.reset();
	_skillFrame = 0;
	_effect = 0;
	_tick = 0;


    return S_OK;
}

void Skill::release(void)
{
}

void Skill::update(void)
{
}

void Skill::render(void)
{

}

void Skill::SkillRender(int x, int y)
{
	_tick++;
	if (_skill[0] == 1)
	{
		if (_tick % 5 == 0)
		{
			_skillFrame++;
		}
		IMAGEMANAGER->findImage("½ºÅ³±¸")->alphaFrameRender(getMemDC(), x-100, y-100, 150, _skillFrame, 0);
		if (IMAGEMANAGER->findImage("½ºÅ³±¸")->getFrameX() >= IMAGEMANAGER->findImage("½ºÅ³±¸")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(1, 1);
			_skillFrame = 0;
			_tick = 0;
			
		}
	}
	else if (_skill[1] == 1)
	{
		#pragma region ºÒ±âµÕ1
		if (IMAGEMANAGER->findImage("»ì¶óµò_½ºÅ³")->getFrameX() == IMAGEMANAGER->findImage("»ì¶óµò_½ºÅ³")->getMaxFrameX())
		{
			if (_tick % 5 == 0)
			{
				_skillFrame++;
			}
		
			if (_temp.size() == 0)
			{
				// ºÒ±âµÕ1
			// ¿ìÇÏ
				int _tempX = x;
				int _tempY = y;
				for (int i = 0; i < 10; i++)
				{
					_tempX += 40;
					_tempY += 32;
					_temp.push_back({ _tempX,_tempY,false,0 });
				}

				//ÁÂ»ó
				_tempX = x;
				_tempY = y;
				for (int i = 10; i < 20; i++)
				{
					_tempX -= 40;
					_tempY -= 32;
					_temp.push_back({ _tempX,_tempY,false,0 });
				}

				// ÁÂÇÏ
				_tempX = x;
				_tempY = y;
				for (int i = 20; i < 30; i++)
				{
					_tempX -= 40;
					_tempY += 32;
					_temp.push_back({ _tempX,_tempY,false,0 });
				}

				// ¿ì»ó
				_tempX = x;
				_tempY = y;
				for (int i = 30; i < 40; i++)
				{
					_tempX += 40;
					_tempY -= 32;
					_temp.push_back({ _tempX,_tempY,false,0 });
				}
			}
			


			for (int i = 0; i < 10; i++)
			{
				IMAGEMANAGER->findImage("½ºÅ³ºÒ±âµÕ1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}
			for (int i = 10; i < 20; i++)
			{
				IMAGEMANAGER->findImage("½ºÅ³ºÒ±âµÕ1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}

			for (int i = 20; i < 30; i++)
			{
				IMAGEMANAGER->findImage("½ºÅ³ºÒ±âµÕ1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}
			for (int i = 30; i < 40; i++)
			{
				IMAGEMANAGER->findImage("½ºÅ³ºÒ±âµÕ1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}

			// ÅÍÁö´Â ÀÌÆåÆ®
			IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®1")->alphaFrameRender(getMemDC(), x-80, y-150, 150, _skillFrame, 0);
			IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®2")->alphaFrameRender(getMemDC(), x-80, y-50, 150, _skillFrame, 0);

			if (IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®1")->getFrameX() >= IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®1")->getMaxFrameX())
			{
				_skill.reset();
				_skill.set(2, 1);
				_skillFrame = 0;
				_tick = 0;
			}
		}
		#pragma endregion
	}
	else if (_skill[2] == 1)
	{
		#pragma region ºÒ±âµÕ2
		if (_tick % 8 == 0)
		{
			_skillFrame++;
		}

		for (int i = 0; i < 10; i++)
		{
			IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y-100, 150, _skillFrame, 0);
		}
		for (int i = 10; i < 20; i++)
		{
			IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y-100, 150, _skillFrame, 0);
		}

		for (int i = 20; i < 30; i++)
		{
			IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y- 100, 150, _skillFrame, 0);
		}
		for (int i = 30; i < 40; i++)
		{
			IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y-100, 150, _skillFrame, 0);
		}

		if (IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3")->getFrameX() >= 11)
		{
			_skill.reset();
			_skill.set(3, 1);
			_skillFrame = 0;
			_tick = 0;
			_temp[0].start = true;
			for (int i = 0; i < _temp.size(); i++)
			{
				_frame.push_back(0);
			}
		}
		#pragma endregion
	}
	else if (_skill[3] == 1)
	{

		
		if (_tick % 2 == 0)
		{
			for (int i = 0; i < _temp.size(); i++)
			{
				if (_temp[i].start)_temp[i].frame++;
			}
		}
		if (_tick % 13 == 0&& _frame.size()!=0)
		{
			for (int i = 0; i < _temp.size(); i++)
			{
				if (_temp[i].start)_frame[i]++;
				if(_frame[i]>)
			}
		
		}

		for (int i = 0; i < _temp.size(); i++)
		{
			if (_temp[i].start)
			{
				if (i < 20)
				{
					IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3_1")->alphaFrameRender(getMemDC(), _temp[i].x , _temp[i].y - 80, 150, _frame[i], 0);
				}
				else
				{
					IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 150, _frame[i], 0);
				}
					
				IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®4")->alphaFrameRender(getMemDC(), _temp[i].x-50, _temp[i].y - 80, 150, _temp[i].frame, 0);
				if (_temp[i].frame > 10 && i+1 < _temp.size()) _temp[i + 1].start = true;
			}
		}

		if (IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®4")->getFrameX() >= IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®4")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(4, 1);
			_skillFrame = 0;
			_tick = 0;
		}
	}
	else if (_skill[4] == 1)
	{
		if (_tick % 2 == 0)
		{
			_skillFrame++;
		}

		if (IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®4")->getFrameX() >= IMAGEMANAGER->findImage("½ºÅ³ÀÌÆåÆ®4")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(4, 1);
			_skillFrame = 0;
			_tick = 0;
		}
	}


}

