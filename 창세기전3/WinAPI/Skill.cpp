#include "Stdafx.h"
#include "Skill.h"
#include "Player.h"

HRESULT Skill::init(void)
{
	_skill.reset();
	_circleFrame= _tick = 0;

	_temp.push_back({ 0,0,0,0 });

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
/*
 ★ 스킬 사운드 사용 내역 ★

0번 스킬구
1번 마지막 찍을때
2번 처음 찍을때
3번 화염구 터질때
4번 적불기둥때
5번 대각선 전체 불기둥

※ 특이사항
/ 1 /스킬 끝나면 클리어소리 자동 플레이
/ 2 / 화염구 터질때 이펙트 대기

*/
}

void Skill::UpSkill(Player* _pl)
{
	// 전체 틱
	_tick++;

	// 스킬구
	if (_skill[0] == 1)
	{
		if (_tick % 5 == 0)
		{
			_temp[0].frame++;

		}
		if (!_skillSound[0])
		{
			_skillSound.set(0, 1);
			SOUNDMANAGER->play("스킬구", 1.0f);
		}
		
		IMAGEMANAGER->findImage("스킬구")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 100, _temp[0].frame, 0);
		if (IMAGEMANAGER->findImage("스킬구")->getFrameX() >= IMAGEMANAGER->findImage("스킬구")->getMaxFrameX())
		{

			_skill.reset();
			_skill.set(1, 1);
			_temp.clear();
			_tick = 0;

			// 다음 스킬 입력
			int tempX = _pl->getPL()._x - 5;
			int tempY = _pl->getPL()._y - 90;
			for (int i = 0; i < 20; i++)
			{
				tempX += 40;
				tempY += 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			tempX = _pl->getPL()._x - 5;
			tempY = _pl->getPL()._y - 90;
			for (int i = 20; i < 40; i++)
			{
				tempX -= 40;
				tempY -= 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			tempX = _pl->getPL()._x - 5;
			tempY = _pl->getPL()._y - 90;
			for (int i = 40; i < 60; i++)
			{
				tempX -= 40;
				tempY += 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			tempX = _pl->getPL()._x - 5;
			tempY = _pl->getPL()._y - 90;
			for (int i = 60; i < 80; i++)
			{
				tempX += 40;
				tempY -= 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			_temp.front().start = true;
			_temp[20].start = true;
			_temp[40].start = true;
			_temp[60].start = true;
			_fireball = _temp;

			// 파티클 넣어놓기
			_particle.clear();
			for (int i = 0; i < _temp.size(); i++)
			{
				for (int j = 0; j < 30; j++)
				{
					_particle.push_back({ RND->getFromFloatTo(_temp[i].x - 50,_temp[i].x + 50),
										RND->getFromFloatTo(_temp[i].y - 50,_temp[i].y + 50),
										0,RND->getFromFloatTo(7,15),255,false });
				}
			}
		}
	}
	// 바닥불 + 폭발
	else if (_skill[1] == 1)
	{


		if (!_skillSound[2])
		{
			SOUNDMANAGER->play("찍을때", 1.0f);
			_skillSound.set(2, 1);
		}


		if (IMAGEMANAGER->findImage("살라딘_스킬")->getFrameX() == IMAGEMANAGER->findImage("살라딘_스킬")->getMaxFrameX())
		{
			if (_tick % 2 == 0 && _enemyXY[0].frame < IMAGEMANAGER->findImage("스킬이펙트1")->getMaxFrameX())
			{
				for (int i = 0; i < _temp.size(); i++)
				{
					if (_temp[i].start)	_temp[i].frame++;
					if (_temp[i].frame > 6)_temp[i].frame = 1;
				}
			}

			// 바닥 사라짐
			if (_enemyXY[0].frame > IMAGEMANAGER->findImage("스킬이펙트1")->getMaxFrameX())
			{
				if (_tick % 3 == 0)
				{
					for (int i = 0; i <40; i++)
					{
						_temp[i].frame++;
					}

					if (_temp[39].frame > IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX())
					for (int i = 40; i < 80; i++)
					{
						_temp[i].frame++;
						if (_temp[i].frame > 12 && i + 1 < _temp.size())
							if (_temp.back().frame > IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX()) _temp.back().start = false;

					}
				}
			}

			// 프레임
			if (_tick % 10 == 0)
			{
				for (int i = 0; i < _fireball.size(); i++)
				{
					if (_temp[i].start) _fireball[i].frame++;
				}
			}
			if (_tick % 3 == 0)
			{
				if (_skill[5] == 0) _circleFrame++;

				for (int i = 0; i < _particle.size(); i++)
					_particle[i].frame++;
			}

			// 플레이어 바닥 연기
			if (IMAGEMANAGER->findImage("스킬이펙트2")->getFrameX() < IMAGEMANAGER->findImage("스킬이펙트2")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("스킬이펙트2")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 78, _pl->getPL()._y - 50, 110, _circleFrame, 0);
				IMAGEMANAGER->findImage("스킬이펙트2광원")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 78, _pl->getPL()._y - 50, 255, _circleFrame, 0);
			}

			// 플레이어 폭발 이펙트
			//if (_skill[5] == 0 && IMAGEMANAGER->findImage("스킬이펙트1")->getFrameX() < IMAGEMANAGER->findImage("스킬이펙트1")->getMaxFrameX())
			//{
			//	IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 85, _pl->getPL()._y - 170, 110, _circleFrame, 0);
			//	IMAGEMANAGER->findImage("스킬이펙트1광원")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 85, _pl->getPL()._y - 170, 255, _circleFrame, 0);
			//}

			if(IMAGEMANAGER->findImage("스킬이펙트2")->getFrameX() >= IMAGEMANAGER->findImage("스킬이펙트2")->getMaxFrameX())
			for (int i = 0; i < _temp.size(); i++)
			{
				if (!_skillSound[5])
				{
					SOUNDMANAGER->play("대각선불기둥", 1.0f);
					_skillSound.set(5, 1);
				}

				if (!_skillSound[3])
				{
					SOUNDMANAGER->play("화염구터질때", 1.0f);
					_skillSound.set(3, 1);
				}

				if (_temp[i].start)
				{
					for (int k = i * 30; k < i * 30 + 30; k++)
					{
						if (k < _particle.size())_particle[k].start = true;
					}
				}


				if (_temp[i].start && _temp.back().frame < IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX())
				{


					if (_temp[i].frame > 1 && i + 1 < _temp.size() && !_temp.back().start)
					{
						_temp[i + 1].start = true;
						_fireball[i + 1].start = true;

					}
				}

				if (_fireball[i].start)
				{
					IMAGEMANAGER->findImage("스킬이펙트5")->alphaFrameRender(getMemDC(), _fireball[i].x - 50, _fireball[i].y - 20, 100, _fireball[i].frame, 0);
					IMAGEMANAGER->findImage("스킬이펙트5광원")->alphaFrameRender(getMemDC(), _fireball[i].x - 50, _fireball[i].y - 20, 120, _fireball[i].frame, 0);
				}

				if (_temp[i].start && i > 39 && _temp[i].frame< IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX())
				{

					IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 100, _temp[i].frame, 0);
					IMAGEMANAGER->findImage("스킬이펙트3광원")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 255, _temp[i].frame, 0);
				}
				else if (_temp[i].start && i < 40)
				{

					IMAGEMANAGER->findImage("스킬이펙트3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 100, _temp[i].frame, 0);
					IMAGEMANAGER->findImage("스킬이펙트3_1광원")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 255, _temp[i].frame, 0);
				}
			}

			if (_skill[5] == 0)
			{
				int degree = RND->getFromIntTo(-5, 5);
				for (int i = 0; i < _particle.size(); i++)
				{
					if (_particle[i].start)
					{
						_particle[i].alpha -= 15;
						if (_particle[i].alpha < 0) _particle[i].alpha = 0;

						IMAGEMANAGER->findImage("스킬파티클1")->alphaFrameRender(getMemDC(), _particle[i].x + 15, _particle[i].y + 80, _particle[i].alpha, _particle[i].frame, 0);

						_particle[i].y -= _particle[i].speed;
						_particle[i].x -= degree;
						_particle[i].speed--;
					}

				}
			}

		}
		// 초기화
		if (_temp.back().start && !_num2)
		{


			_skill.set(2, 1);
			_num2 = true;
			// 불기둥 구조체
			for (int i = 0; i < _temp.size(); i++)
			{
				_fire.push_back({ _temp[i].x,_temp[i].y - 120,0,false });
			}
			_particle.clear();
		}
	}
	// 노란 불기둥
	if (_skill[2] == 1)
	{
		
		if (_tick % 3 == 0)
		{
			for (int i = 0; i < _fire.size(); i++)
			{
				_fire[i].frame++;
			}
		}
		for (int i = 0; i < 20; i++)
		{
			IMAGEMANAGER->findImage("스킬불기둥1_1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 180, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("스킬불기둥1_1광원")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}
		for (int i = 20; i < 40; i++)
		{
			IMAGEMANAGER->findImage("스킬불기둥1_1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 180, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("스킬불기둥1_1광원")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}
		for (int i = 40; i < 60; i++)
		{
			IMAGEMANAGER->findImage("스킬불기둥1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 180, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("스킬불기둥1광원")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}
		for (int i = 60; i < 80; i++)
		{
			IMAGEMANAGER->findImage("스킬불기둥1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 180, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("스킬불기둥1광원")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}

		if (IMAGEMANAGER->findImage("스킬불기둥1")->getFrameX() == IMAGEMANAGER->findImage("스킬불기둥1")->getMaxFrameX())
		{
			_skill.set(3, 1);
			_skill.set(2, 0);
			_fire.clear();

		}
	}
	if (_skill[4] == 1)
	{
		if (_tick % 7 == 0)
		{
			for (int i = 4; i < 8; i++)
			{
				if(_enemyXY[i].frame < IMAGEMANAGER->findImage("스킬불기둥2")->getMaxFrameX())_enemyXY[i].frame++;
			}
		}


		for (int i = 4; i < 8; i++)
		{
			if (_enemyXY[i].start)
			{
				IMAGEMANAGER->findImage("스킬불기둥2")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y - 145, 255, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬불기둥2광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y - 145, 180, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬불기둥2_1")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y - 145, 150, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬불기둥2_1광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y - 145, 180, _enemyXY[i].frame, 0);
			}
		}


		// 초기화
		if (_enemyXY[5].frame == 29)
		{
			_skill.set(3, 0);
			_skill.set(4, 0);
			_skill.set(5, 1);
			_skill.set(7, 1);
			for (int i = 0; i < 8; i++)
			{
				
					_enemyXY[i].frame = 0;
			}
			// 파티클 생성
			for (int i = 0; i < _enemyXY.size(); i++)
			{
				for (int j = 0; j < 30; j++)
				{
					_particle.push_back({ RND->getFromFloatTo(_enemyXY[i].x - 50,_enemyXY[i].x + 50),
										RND->getFromFloatTo(_enemyXY[i].y,_enemyXY[i].y + 100),
										0,0,255,false });
				}
			}
		}
	}

}

void Skill::DownSkill(Player* _pl)
{
	// 적 불기둥 전 바닥 용암
	if (_skill[3] == 1)
	{
		if (!_skillSound[4])
		{
			SOUNDMANAGER->play("적불기둥때", 1.0f);
			_skillSound.set(4, 1);
		}


		if (_tick % 6 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				if (i < _enemyXY.size())
				{
					_enemyXY[i].frame++;
					if (_enemyXY[i].frame == IMAGEMANAGER->findImage("스킬이펙트3")->getMaxFrameX())_enemyXY[i].frame = 13;
				}
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (i < _enemyXY.size())
			if (_enemyXY[i].start)
			{
				IMAGEMANAGER->findImage("스킬이펙트3")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 35, 150, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬이펙트3광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 35, 150, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬이펙트3_1광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 35, 150, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬이펙트3_1광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 35, 150, _enemyXY[i].frame, 0);
			}
		}

		// 끝나고 초기화
		if (_enemyXY[0].frame == 21)
		{
			_skill.set(4, 1);
		}
	}

	if (_skill[5] == 1)
	{
		// 사운드
		if (!_skillSound[1])
		{
			SOUNDMANAGER->play("마지막터질때", 1.0f);
			_skillSound.set(1, 1);
		}


		if (_enemyXY[0].frame == 0)	IMAGEMANAGER->findImage("빨강알파")->render(getMemDC());

		if (_tick % 3 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				
				_enemyXY[i].frame++;
			}
			for (int i = 0; i < _particle.size(); i++) _particle[i].frame++;
		}
		if (_tick % 15 == 0)
		{
			for (int i = 4; i < 8; i++)
			{
				
				_enemyXY[i].frame++;
			}
		}


		for (int i = 0; i < 80; i++)
		{
			IMAGEMANAGER->findImage("스킬파티클3")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _particle[i].frame, 0);
			_particle[i].y += _particle[i].speed;
			_particle[i].speed -= 0.1;
			_particle[i].alpha -= 5;
			if (_particle[i].alpha < 0)_particle[i].alpha = 0;
		}
		for (int i = 80; i < 160; i++)
		{
			IMAGEMANAGER->findImage("스킬파티클2")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _particle[i].frame, 0);
			_particle[i].y += _particle[i].speed;
			_particle[i].speed -= 0.1;
			_particle[i].alpha -= 3;
			if (_particle[i].alpha < 0)_particle[i].alpha = 0;
		}

		for (int i = 4; i < 8; i++)
		{
			if (_enemyXY[i].start && _enemyXY[i].frame < IMAGEMANAGER->findImage("스킬바닥불")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("스킬바닥불")->alphaFrameRender(getMemDC(), _enemyXY[i].x - 50, _enemyXY[i].y + 55, 80, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬바닥불광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x - 50, _enemyXY[i].y + 55, 255, _enemyXY[i].frame, 0);
			}
			else
			{
				_skill.set(8, 1);
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (_enemyXY[i].start && _enemyXY[i].frame < IMAGEMANAGER->findImage("스킬이펙트1")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("스킬이펙트1")->alphaFrameRender(getMemDC(), _enemyXY[i].x - 80, _enemyXY[i].y - 50, 120, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("스킬이펙트1광원")->alphaFrameRender(getMemDC(), _enemyXY[i].x - 80, _enemyXY[i].y - 50, 180, _enemyXY[i].frame, 0);
			}
		}




		for (int i = 160; i < 240; i++)
		{
			IMAGEMANAGER->findImage("스킬파티클1")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _particle[i].frame, 0);
			_particle[i].y += _particle[i].speed;
			_particle[i].speed -= 0.1;
			_particle[i].alpha -= 3;
			if (_particle[i].alpha < 0)_particle[i].alpha = 0;
		}
		if (_temp.back().start == false)
		{
			SOUNDMANAGER->play("클리어소리", 1.0f);
			_skill.reset();
			_skill.set(6, 1);
			_skill.set(7, 1); // 적렌더를 위해 트루값설정
			for (int i = 0; i < 8; i++) _enemyXY[i].frame = 0;
		}

	}

}


