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

}

void Skill::skillRender(Player* _pl)
{
	// ��ü ƽ
	_tick++;

	// ��ų��
	if (_skill[0] == 1)
	{
		if (_tick % 5 == 0)
		{
			_temp[0].frame++;
			
		}
		IMAGEMANAGER->findImage("��ų��")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 100, _temp[0].frame, 0);
		// IMAGEMANAGER->findImage("��ų������")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 255, _skillFrame, 0);
		if (IMAGEMANAGER->findImage("��ų��")->getFrameX() >= IMAGEMANAGER->findImage("��ų��")->getMaxFrameX())
		{
			_skill.reset();
			_skill.set(1, 1);
			_temp.clear();
			_tick = 0;

			// ���� ��ų �Է�
			int tempX = _pl->getPL()._x-5;
			int tempY = _pl->getPL()._y-90;
			for (int i = 0; i < 20; i++)
			{
				tempX += 40;
				tempY += 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			tempX = _pl->getPL()._x-5;
			tempY = _pl->getPL()._y-90; 
			for (int i = 20; i < 40; i++)
			{
				tempX -= 40;
				tempY -= 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			tempX = _pl->getPL()._x-5;
			tempY = _pl->getPL()._y-90;
			for (int i = 40; i < 60; i++)
			{
				tempX -= 40;
				tempY += 32;
				_temp.push_back({ tempX,tempY,0,false });
			}
			tempX = _pl->getPL()._x-5;
			tempY = _pl->getPL()._y-90;
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
			
			// ��ƼŬ �־����
			for (int i = 0; i < _temp.size(); i++)
			{
				for (int j = 0; j < 5; j++)
				{
					/*_particle.push_back({RND->getFromFloatTo(),});*/
				}
			}
		}
	}

	// �ٴں� + ����
	else if (_skill[1] == 1)
	{
		if (IMAGEMANAGER->findImage("����_��ų")->getFrameX() == IMAGEMANAGER->findImage("����_��ų")->getMaxFrameX())
		{

			if (_tick % 2 == 0&& _enemyXY[0].frame < IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
			{
				for (int i = 0; i < _temp.size(); i++)
				{
					if (_temp[i].start)	_temp[i].frame++;
					if (_temp[i].frame > 6)_temp[i].frame = 1;
				}
			}


			if (_enemyXY[0].frame > IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
			{
				if (_tick % 5 == 0)
				{
					for (int i = 0; i < _temp.size(); i++)
					{
						_temp[i].frame++;

						if (_temp[i].frame > 12 && i + 1 < _temp.size())

						if (_temp.back().frame > IMAGEMANAGER->findImage("��ų����Ʈ3")->getMaxFrameX()) _temp.back().start = false;
						
					}
				}
			}

			if (_tick % 10 == 0 )
			{
				for (int i = 0; i < _fireball.size(); i++)
				{
					if (_temp[i].start) _fireball[i].frame++;
				}
			}
			if (_tick % 5 == 0)
			{
				_circleFrame++;
			}

			// �÷��̾� �ٴ� ����
			if (IMAGEMANAGER->findImage("��ų����Ʈ2")->getFrameX() < IMAGEMANAGER->findImage("��ų����Ʈ2")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("��ų����Ʈ2")->alphaFrameRender(getMemDC(), _pl->getPL()._x-78, _pl->getPL()._y-50, 110, _circleFrame, 0);
				IMAGEMANAGER->findImage("��ų����Ʈ2����")->alphaFrameRender(getMemDC(), _pl->getPL()._x-78, _pl->getPL()._y-50, 255, _circleFrame, 0);
			}

			// �÷��̾� ���� ����Ʈ
			if (IMAGEMANAGER->findImage("��ų����Ʈ1")->getFrameX() < IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("��ų����Ʈ1")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 85, _pl->getPL()._y - 170, 110, _circleFrame, 0);
				IMAGEMANAGER->findImage("��ų����Ʈ1����")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 85, _pl->getPL()._y - 170, 255, _circleFrame, 0);
			}

			
			for (int i = 0; i < _temp.size(); i++)
			{
				
				if (_temp[i].start && _temp.back().frame < IMAGEMANAGER->findImage("��ų����Ʈ3")->getMaxFrameX())
				{
					if (_temp[i].frame > 3 && i + 1 < _temp.size()&& !_temp.back().start)
					{
						_temp[i + 1].start = true;
						_fireball[i + 1].start = true;
					}
				}

				if (_fireball[i].start )
				{
					IMAGEMANAGER->findImage("��ų����Ʈ5")->alphaFrameRender(getMemDC(), _fireball[i].x - 50, _fireball[i].y - 20, 80, _fireball[i].frame, 0);
					IMAGEMANAGER->findImage("��ų����Ʈ5����")->alphaFrameRender(getMemDC(), _fireball[i].x - 50, _fireball[i].y - 20, 255, _fireball[i].frame, 0);
				}

				if (_temp[i].start && i > 39)
				{
					IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 100, _temp[i].frame, 0);
					IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 255, _temp[i].frame, 0);
				}
				else if (_temp[i].start && i < 40)
				{
					IMAGEMANAGER->findImage("��ų����Ʈ3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 100, _temp[i].frame, 0);
					IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 255, _temp[i].frame, 0);
				}
			}
			
		}

		if (_temp.back().start && !_num2)
		{
			_skill.set(2, 1);
			_num2 = true;
			// �ұ�� ����ü
			for (int i = 0; i < _temp.size(); i++)
			{
				_fire.push_back({ _temp[i].x,_temp[i].y-185,0,false });
			}
		}
	}
	
	// ��� �ұ��
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
			IMAGEMANAGER->findImage("��ų�ұ��1_1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 80, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("��ų�ұ��1_1����")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}
		for (int i =20; i < 40; i++)
		{
			IMAGEMANAGER->findImage("��ų�ұ��1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 80, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("��ų�ұ��1����")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}
		for (int i =40; i < 60; i++)
		{
			IMAGEMANAGER->findImage("��ų�ұ��1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 80, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("��ų�ұ��1����")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}
		for (int i = 60; i < 80; i++)
		{
			IMAGEMANAGER->findImage("��ų�ұ��1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 80, _fire[i].frame, 0);
			IMAGEMANAGER->findImage("��ų�ұ��1����")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 255, _fire[i].frame, 0);
		}

		if (IMAGEMANAGER->findImage("��ų�ұ��1")->getFrameX() == IMAGEMANAGER->findImage("��ų�ұ��1")->getMaxFrameX())
		{
			_skill.set(3, 1);
			_skill.set(2, 0);
			_fire.clear();
			
		}
	}
	else if (_skill[3] == 1)
	{
		if (_tick % 6 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				_enemyXY[i].frame++;
				if (_enemyXY[i].frame == IMAGEMANAGER->findImage("��ų����Ʈ3")->getMaxFrameX())_enemyXY[i].frame = 13;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (_enemyXY[i].start)
			{
				IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 20, 150, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 20, 255, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 20, 150, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _enemyXY[i].x, _enemyXY[i].y + 20, 255, _enemyXY[i].frame, 0);
			}
		}

		// ������ �ʱ�ȭ
		if (_enemyXY[0].frame == 21)
		{
			_skill.set(4, 1);
		}
	}
	if (_skill[4] == 1)
	{
		if (_tick % 5 == 0)
		{
			for (int i = 4; i < 8; i++)
			{
				_enemyXY[i].frame++;
			}
		}

		for (int i = 4; i < 8; i++)
		{
			if (_enemyXY[i].start)
			{
				IMAGEMANAGER->findImage("��ų�ұ��3")->alphaFrameRender(getMemDC(), _enemyXY[i].x + 8, _enemyXY[i].y - 165, 80, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų�ұ��3����")->alphaFrameRender(getMemDC(), _enemyXY[i].x + 8, _enemyXY[i].y - 165, 255, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų�ұ��3_1")->alphaFrameRender(getMemDC(), _enemyXY[i].x + 8, _enemyXY[i].y - 165, 80, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų�ұ��3_1����")->alphaFrameRender(getMemDC(), _enemyXY[i].x + 8, _enemyXY[i].y - 165, 255, _enemyXY[i].frame, 0);
			}
		}
		if (_enemyXY[5].frame > 31)
		{
			_skill.set(3, 0);
			_skill.set(4, 0);
			_skill.set(5, 1);
			for (int i = 0; i < 8; i++)
			{
				_enemyXY[i].frame = 0;
			}
		}
	}
	else if (_skill[5] == 1)
	{
		if (_enemyXY[0].frame == 0)	IMAGEMANAGER->findImage("��������")->render(getMemDC());

		if (_tick % 5 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				_enemyXY[i].frame++;
			}
		}
		if (_tick % 15 == 0)
		{
			for (int i = 4; i < 8; i++)
			{
				_enemyXY[i].frame++;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			if (_enemyXY[i].start && _enemyXY[i].frame<IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("��ų����Ʈ1")->alphaFrameRender(getMemDC(), _enemyXY[i].x-80, _enemyXY[i].y-100, 80, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų����Ʈ1����")->alphaFrameRender(getMemDC(), _enemyXY[i].x-80, _enemyXY[i].y-100, 255, _enemyXY[i].frame, 0);
			}
		}
		for (int i = 4; i < 8; i++)
		{
			if (_enemyXY[i].start && _enemyXY[i].frame < IMAGEMANAGER->findImage("��ų�ٴں�")->getMaxFrameX())
			{
				IMAGEMANAGER->findImage("��ų�ٴں�")->alphaFrameRender(getMemDC(), _enemyXY[i].x -50, _enemyXY[i].y+55 , 80, _enemyXY[i].frame, 0);
				IMAGEMANAGER->findImage("��ų�ٴںұ���")->alphaFrameRender(getMemDC(), _enemyXY[i].x-50 , _enemyXY[i].y+55 , 255, _enemyXY[i].frame, 0);
			}
		}
		if (_temp.back().start==false)
		{
			_skill.set(6, 1);
			_skill.set(5, 0);

			for (int i = 0; i < 8; i++) _enemyXY[i].frame = 0;
		}

		if (_enemyXY[0].frame > IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
		{
			
		}
	}
}

