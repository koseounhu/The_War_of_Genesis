#include "Stdafx.h"
#include "Skill.h"
#include "Enemy.h"
#include "Player.h"

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

void Skill::SkillRender(Player* _pl,Enemy* _em[10])
{
	IMAGEMANAGER->findImage("검정알파")->alphaRender(getMemDC(), 150);
	_tick++;
	if (_skill[0] == 1)
	{
		if (_tick % 5 == 0)
		{
			_skillFrame++;
		}
		IMAGEMANAGER->findImage("스킬구")->alphaFrameRender(getMemDC(), _pl->getPL()._x-110, _pl->getPL()._y-100, 150, _skillFrame, 0);
		if (IMAGEMANAGER->findImage("스킬구")->getFrameX() >= IMAGEMANAGER->findImage("스킬구")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(1, 1);
			_skillFrame = 0;
			_tick = 0;
			
		}
	}
	else if (_skill[1] == 1)
	{
		#pragma region 불기둥1
		if (IMAGEMANAGER->findImage("살라딘_스킬")->getFrameX() == IMAGEMANAGER->findImage("살라딘_스킬")->getMaxFrameX())
		{
			if (_tick % 5 == 0)
			{
				_skillFrame++;
			}
		
			if (_temp.size() == 0)
			{
				// 불기둥1
			// 우하
				int _tempX =0;
				int _tempY =0;
				for (int i = 0; i < 10; i++)
				{
					_tempX += 40;
					_tempY += 32;
					_temp.push_back({ _pl->getPL()._x+ _tempX,_pl->getPL()._y+ _tempY,false,0 });
				}

				//좌상
				_tempX = 0;
				_tempY = 0;
				for (int i = 10; i < 20; i++)
				{
					_tempX -= 40;
					_tempY -= 32;
					_temp.push_back({ _pl->getPL()._x+ _tempX,_pl->getPL()._y+_tempY,false,0 });
				}

				// 좌하
				_tempX = 0;
				_tempY = 0;
				for (int i = 20; i < 30; i++)
				{
					_tempX -= 40;
					_tempY += 32;
					_temp.push_back({ _pl->getPL()._x+ _tempX,_pl->getPL()._y+_tempY,false,0 });
				}

				// 우상
				_tempX = 0;
				_tempY = 0;
				for (int i = 30; i < 40; i++)
				{
					_tempX += 40;
					_tempY -= 32;
					_temp.push_back({ _pl->getPL()._x+_tempX,_pl->getPL()._y+_tempY,false,0 });
				}
			}
			


			for (int i = 0; i < 10; i++)
			{
				IMAGEMANAGER->findImage("스킬불기둥1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}
			for (int i = 10; i < 20; i++)
			{
				IMAGEMANAGER->findImage("스킬불기둥1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}

			for (int i = 20; i < 30; i++)
			{
				IMAGEMANAGER->findImage("스킬불기둥1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}
			for (int i = 30; i < 40; i++)
			{
				IMAGEMANAGER->findImage("스킬불기둥1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
			}

			// 터지는 이펙트
			IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _pl->getPL()._x-80, _pl->getPL()._y-150, 150, _skillFrame, 0);
			IMAGEMANAGER->findImage("스킬이펙트2")->alphaFrameRender(getMemDC(), _pl->getPL()._x-80, _pl->getPL()._y-50, 150, _skillFrame, 0);

			if (IMAGEMANAGER->findImage("스킬이펙트1")->getFrameX() >= IMAGEMANAGER->findImage("스킬이펙트1")->getMaxFrameX())
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
		#pragma region 불기둥2
		if (_tick % 8 == 0)
		{
			_skillFrame++;
		}

		for (int i = 0; i < 10; i++)
		{
			IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y-100, 150, _skillFrame, 0);
		}
		for (int i = 10; i < 20; i++)
		{
			IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y-100, 150, _skillFrame, 0);
		}

		for (int i = 20; i < 30; i++)
		{
			IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y- 100, 150, _skillFrame, 0);
		}
		for (int i = 30; i < 40; i++)
		{
			IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y-100, 150, _skillFrame, 0);
		}

		if (IMAGEMANAGER->findImage("스킬이펙트3")->getFrameX() >= 11)
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
		// 파티클 넣어놓기
		if (_particle.size() < _temp.size())
		{
			for (int i = 0; i < _temp.size(); i++)
			{
				for (int j = 0; j < 5; j++)
				{
					_particle.push_back({RND->getFromFloatTo(_temp[i].x-16,_temp[i].x+16),RND->getFromFloatTo(_temp[i].y-20,_temp[i].y+20),0,RND->getFromFloatTo(3,7),255 });
				}
			}
		}
		

		
		if (_tick % 1 == 0)
		{
			for (int i = 0; i < _temp.size(); i++)
			{
				if (_temp[i].start)_temp[i].frame++;
			}

			// 파티클
			for (int i = 0; i < _particle.size(); i++)
			{
				if (_particle[i].start)
				{
					_particle[i].frame++;
					if (_particle[i].frame > 15)_particle[i].frame = 0;
				}


			}
		}
		if (_tick % 10 == 0&& _frame.size()!=0)
		{
			for (int i = 0; i < _temp.size(); i++)
			{
				if (_temp[i].start)_frame[i]++;
			}
		}
		


		// 스킬
		for (int i = 0; i < _temp.size(); i++)
		{
			if (_temp[i].start)
			{
				
				if (i < 20)
				{
					if (_frame[i] < 12)
						IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 255, _frame[i], 0);
				}
				else if(i <40)
				{
					if (_frame[i] < 12)
						IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 255, _frame[i], 0);
				}
				

				if(_temp[i].frame<IMAGEMANAGER->findImage("스킬이펙트5")->getMaxFrameX()) 
					IMAGEMANAGER->findImage("스킬이펙트5")->alphaFrameRender(getMemDC(), _temp[i].x - 50, _temp[i].y - 80, 255, _temp[i].frame, 0);

				if (_temp[i].frame > 10 && i+1 < _temp.size()) _temp[i + 1].start = true;
				
				for (int j = 0; j < i*5; j++)
				{
					if(!_particle[j].start)	_particle[j].start = true;
				}
			}
		}

		for (int i = 0; i < _particle.size(); i++)
		{
			if (_particle[i].start)
			{
				IMAGEMANAGER->findImage("스킬파티클1")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _particle[i].frame, 0);
				if (_particle[i].alpha >0 )_particle[i].alpha-=2;
				if (_particle[i].alpha <= 0 )_particle[i].alpha=0;
				_particle[i].y -= _particle[i].speed;
				if(_particle[i].speed>0) _particle[i].speed-=0.3f;
			}
		}
		

		// 초기화 턴넘김
		if (_frame.back() >= IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX() && _frame[39] >IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(4, 1);
			_skillFrame = 0;
			_tick = 0;
			for (int i = 0; i < _frame.size(); i++)
				_frame[i] = 0;

			for (int i = 0; i < _temp.size(); i++)
			{
				_temp[i].start = false;
				_temp[i].frame = 0;
			}
			_particle.clear();
		}
	}
	else if (_skill[4] == 1)
	{
		if (_tick % 5 == 0)
		{
			_skillFrame++;
			_frame[0]++;
			if(_frame[0]> IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX()/2 )	_frame[1]++;
			if(_frame[1]> IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX()/2)	_frame[2]++;

		}

		if (_frame[0]< IMAGEMANAGER->findImage("스킬이펙트3") ->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _em[0]->getEnemyX() + 20, _em[0]->getEnemyY() - 40, 200, _frame[0], 0);
			IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _em[1]->getEnemyX() + 20, _em[1]->getEnemyY() - 40, 200, _frame[0], 0);
			IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _em[2]->getEnemyX() + 20, _em[2]->getEnemyY() - 40, 200, _frame[0], 0);
			IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _em[3]->getEnemyX() + 20, _em[3]->getEnemyY() - 40, 200, _frame[0], 0);
		}
		else if (_frame[1] < IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _em[0]->getEnemyX() + 20, _em[0]->getEnemyY() - 40, 200, _frame[1], 0);
			IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _em[1]->getEnemyX() + 20, _em[1]->getEnemyY() - 40, 200, _frame[1], 0);
			IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _em[2]->getEnemyX() + 20, _em[2]->getEnemyY() - 40, 200, _frame[1], 0);
			IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _em[3]->getEnemyX() + 20, _em[3]->getEnemyY() - 40, 200, _frame[1], 0);
		}
		else if (_frame[2] < IMAGEMANAGER->findImage("스킬불기둥3")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("스킬불기둥2")->alphaFrameRender(getMemDC(), _em[0]->getEnemyX() + 20, _em[0]->getEnemyY() - 220, 200, _frame[2], 0);
			IMAGEMANAGER->findImage("스킬불기둥2")->alphaFrameRender(getMemDC(), _em[1]->getEnemyX() + 20, _em[1]->getEnemyY() - 220, 200, _frame[2], 0);
			IMAGEMANAGER->findImage("스킬불기둥2")->alphaFrameRender(getMemDC(), _em[2]->getEnemyX() + 20, _em[2]->getEnemyY() - 220, 200, _frame[2], 0);
			IMAGEMANAGER->findImage("스킬불기둥2")->alphaFrameRender(getMemDC(), _em[3]->getEnemyX() + 20, _em[3]->getEnemyY() - 220, 200, _frame[2], 0);
		}

		// 초기화
		if (_frame[2]> IMAGEMANAGER->findImage("스킬불기둥3") ->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(5, 1);
			_skillFrame = 0;
			_tick = 0;
			_particle.clear();
			_frame.clear();
			for (int i = 0; i < _temp.size(); i++)
			{
				_frame.push_back(0);
			}

			// 파티클 새로 추가
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					_particle.push_back({ RND->getFromFloatTo(_em[i]->getEnemyX() - 100,_em[i]->getEnemyX() + 40),
										RND->getFromFloatTo(_em[i]->getEnemyY() - 60,_em[i]->getEnemyY()),
										0,0,255,false });
				}

			}

		}

	}
	else if (_skill[5] == 1)
	{
		if (_tick % 5 == 0)
		{
			_skillFrame++;
			_frame[0]++;

			_frame[1]++;
			if (_frame[1] > 4)_frame[1] = 0;

			_frame[2]++;
			if (_frame[2] > 15)_frame[2] = 0;
		}


		if (_frame[0] < IMAGEMANAGER->findImage("스킬이펙트1")->getMaxFrameX())
		{
			IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _em[0]->getEnemyX()-70, _em[0]->getEnemyY()-130, 255, _frame[0], 0);
			IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _em[1]->getEnemyX()-70, _em[1]->getEnemyY()-130, 255, _frame[0], 0);
			IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _em[2]->getEnemyX()-70, _em[2]->getEnemyY()-130, 255, _frame[0], 0);
			IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _em[3]->getEnemyX()-70, _em[3]->getEnemyY()-130, 255, _frame[0], 0);
		}


		for (int i = 0; i < 4; i++)
			IMAGEMANAGER->findImage("스킬바닥불")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX()-30, _em[i]->getEnemyY(),255, _frame[1], 0);

		for (int i = 0; i < _particle.size(); i++)
		{
			IMAGEMANAGER->findImage("스킬파티클3")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _frame[2], 0);
			_particle[i].y += _particle[i].speed;
			_particle[i].speed -= 0.1f;
			_particle[i].alpha-=2;
			if (_particle[i].alpha <= 0) _particle[i].alpha = 0;
		}



		if (_frame[2] > IMAGEMANAGER->findImage("스킬불기둥3")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(5, 1);
			_skillFrame = 0;
			_tick = 0;
			_frame.clear();
		}


	}

}

