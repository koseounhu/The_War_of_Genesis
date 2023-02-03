#include "Stdafx.h"
#include "Skill.h"
#include "Enemy.h"
#include "Player.h"

HRESULT Skill::init(void)
{
	_skill.reset();
	_tick = 0;

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

void Skill::skillRender(Player* _pl, Enemy* _em[10])
{
	_tick++;
	if (_skill[0] == 1)
	{
		if (_tick % 5 == 0)
		{
			_temp[0].frame++;
			
		}
		IMAGEMANAGER->findImage("��ų��")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 150, _temp[0].frame, 0);
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
			for (int i = 0; i < _temp.size(); i++)
			{
				for (int j = 0; j < 5; j++)
				{
					/*_particle.push_back({RND->getFromFloatTo(),});*/
				}
			}
		}
	}

	// �ٴڿ� �ҹٴ� ��Ƴ�
	else if (_skill[1] == 1)
	{
		if (IMAGEMANAGER->findImage("����_��ų")->getFrameX() == IMAGEMANAGER->findImage("����_��ų")->getMaxFrameX())
		{

			if (_tick % 2 == 0)
			{
				for (int i = 0; i < _temp.size(); i++)
				{
					if (_temp[i].start && _temp[i].frame < 6)	_temp[i].frame++;
					if (_temp[i].frame > 5)_temp[i].frame = 1;
				}
			}
			if (_tick % 5 == 0)
			{
				for (int i = 0; i < _fireball.size(); i++)
				{
					if (_temp[i].start) _fireball[i].frame++;
				}
			}
			

			for (int i = 0; i < _temp.size(); i++)
			{
				if (_temp[i].start)
				{
					if (_temp[i].frame > 3 && i + 1 < _temp.size())
					{
						_temp[i + 1].start = true;
						_fireball[i + 1].start = true;
					}
				}
				if (_fireball[i].start)
				{
					IMAGEMANAGER->findImage("��ų����Ʈ5")->alphaFrameRender(getMemDC(), _fireball[i].x-50, _fireball[i].y-20, 80, _fireball[i].frame, 0);
					IMAGEMANAGER->findImage("��ų����Ʈ5����")->alphaFrameRender(getMemDC(), _fireball[i].x-50, _fireball[i].y-20, 255, _fireball[i].frame, 0);
				}

				if (_temp[i].start && i>39)
				{
					IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 80, _temp[i].frame, 0);
					IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 255, _temp[i].frame, 0);
				}
				else if (_temp[i].start && i < 40)
				{
					IMAGEMANAGER->findImage("��ų����Ʈ3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 80, _temp[i].frame, 0);
					IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y, 255, _temp[i].frame, 0);
				}
			}
		}

		if (_temp.back().start)
		{
			_skill.set(2, 1);
			for (int i = 0; i < _temp.size(); i++)
			{
				_fire.push_back({ _temp[i].x,_temp[i].y-185,0,false });
			}
		}
	}
	
	// �ұ��
	if (_skill[2] == 1)
	{
		if (_tick % 5 == 0)
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
			IMAGEMANAGER->findImage("��ų�ұ��1_1")->alphaFrameRender(getMemDC(), _fire[i].x, _fire[i].y, 80, _fire[i].frame, 0);
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
	}
}



//void Skill::skillUp(Player* _pl, Enemy* _em[10])
//{
//	_tick++;
//	if (_skill[0] == 1)
//	{
//		if (_tick % 5 == 0)
//		{
//			_skillFrame++;
//		}
//		IMAGEMANAGER->findImage("��ų��")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 150, _skillFrame, 0);
//		 IMAGEMANAGER->findImage("��ų������")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 255, _skillFrame, 0);
//		if (IMAGEMANAGER->findImage("��ų��")->getFrameX() >= IMAGEMANAGER->findImage("��ų��")->getMaxFrameX())
//		{
//			_skill.reset();
//			_skill.set(1, 1);
//			_skillFrame = 0;
//			_tick = 0;
//		}
//	}
//	else if (_skill[3] == 1)
//	{
//	 ��ƼŬ �־����
//	if (_particle.size() < _temp.size())
//	{
//		for (int i = 0; i < _temp.size(); i++)
//		{
//			for (int j = 0; j < 5; j++)
//			{
//				_particle.push_back({ RND->getFromFloatTo(_temp[i].x - 16,_temp[i].x + 16),RND->getFromFloatTo(_temp[i].y - 20,_temp[i].y + 20),0,RND->getFromFloatTo(3,7),255 });
//			}
//		}
//	}
//
//	if (_tick % 3 == 0)
//	{
//		for (int i = 0; i < _temp.size(); i++)
//		{
//			if (_temp[i].start)_temp[i].frame++;
//		}
//	}
//
//	if (_tick % 1 == 0)
//	{
//		 ��ƼŬ
//		for (int i = 0; i < _particle.size(); i++)
//		{
//			if (_particle[i].start)
//			{
//				_particle[i].frame++;
//				if (_particle[i].frame > 15)_particle[i].frame = 0;
//			}
//		}
//	}
//	if (_tick % 15 == 0 && _frame.size() != 0)
//	{
//		for (int i = 0; i < _temp.size(); i++)
//		{
//			if (_temp[i].start)_frame[i]++;
//		}
//	}
//
//
//
//	 ��ų
//	for (int i = 0; i < _temp.size(); i++)
//	{
//		if (_temp[i].start)
//		{
//
//			if (i < 20)
//			{
//				if (_frame[i] < 12)
//				{
//					IMAGEMANAGER->findImage("��ų����Ʈ3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 120, _frame[i], 0);
//					IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 255, _frame[i], 0);
//				}
//			}
//			else if (i < 40)
//			{
//				if (_frame[i] < 12)
//				{
//					IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 120, _frame[i], 0);
//					IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 80, 255, _frame[i], 0);
//				}
//			}
//
//
//			if (_temp[i].frame < IMAGEMANAGER->findImage("��ų����Ʈ5")->getMaxFrameX())
//			{
//				IMAGEMANAGER->findImage("��ų����Ʈ5")->alphaFrameRender(getMemDC(), _temp[i].x - 50, _temp[i].y - 100, 120, _temp[i].frame, 0);
//				IMAGEMANAGER->findImage("��ų����Ʈ5����")->alphaFrameRender(getMemDC(), _temp[i].x - 50, _temp[i].y - 100, 255, _temp[i].frame, 0);
//			}
//
//
//			if (_temp[i].frame > 5 && i + 1 < _temp.size()) _temp[i + 1].start = true;
//
//			for (int j = 0; j < i * 5; j++)
//			{
//				if (!_particle[j].start)	_particle[j].start = true;
//			}
//		}
//	}
//
//		for (int i = 0; i < _particle.size(); i++)
//		{
//			if (_particle[i].start)
//			{
//				IMAGEMANAGER->findImage("��ų��ƼŬ1")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _particle[i].frame, 0);
//				if (_particle[i].alpha > 0)_particle[i].alpha -= 2;
//				if (_particle[i].alpha <= 0)_particle[i].alpha = 0;
//				_particle[i].y -= _particle[i].speed;
//				_particle[i].speed -= 0.3f;
//			}
//		}
//
//
//		 �ʱ�ȭ �ϳѱ�
//		if (_frame[30] >= IMAGEMANAGER->findImage("��ų����Ʈ3")->getMaxFrameX())
//		{
//			_skill.reset();
//			_skill.set(4, 1);
//			_skillFrame = 0;
//			_tick = 0;
//			for (int i = 0; i < _frame.size(); i++)
//				_frame[i] = 0;
//
//			for (int i = 0; i < _temp.size(); i++)
//			{
//				_temp[i].start = false;
//				_temp[i].frame = 0;
//			}
//			_particle.clear();
//		}
//	}
//	else if (_skill[4] == 1)
//	{
//		if (_frame[1] > IMAGEMANAGER->findImage("��ų����Ʈ3_1")->getMaxFrameX()&&_frame[2] < IMAGEMANAGER->findImage("��ų�ұ��2")->getMaxFrameX())
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				IMAGEMANAGER->findImage("��ų�ұ��2")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 220, 100, _frame[2], 0);
//				IMAGEMANAGER->findImage("��ų�ұ��2����")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 220, 255, _frame[2], 0);
//				IMAGEMANAGER->findImage("��ų�ұ��2_1")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 220, 100, _frame[2], 0);
//				IMAGEMANAGER->findImage("��ų�ұ��2_1����")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 220, 255, _frame[2], 0);
//			}
//		}
//
//	}
//	if(_skill[5]==1 && _frame[0]==0)IMAGEMANAGER->findImage("��������")->render(getMemDC());
//}
//
//void Skill::skillDown(Player* _pl, Enemy* _em[10])
//{
//	if (_skill[1] == 1)
//	{
//#pragma region �ұ��1
//	if (IMAGEMANAGER->findImage("����_��ų")->getFrameX() == IMAGEMANAGER->findImage("����_��ų")->getMaxFrameX())
//	{
//		if (_tick % 5 == 0)
//		{
//			_skillFrame++;
//		}
//
//		if (_temp.size() == 0)
//		{
//			 �ұ��1
//		 ����
//			int _tempX = 0;
//			int _tempY = 0;
//			for (int i = 0; i < 10; i++)
//			{
//				_tempX += 40;
//				_tempY += 32;
//				_temp.push_back({ _pl->getPL()._x + _tempX,_pl->getPL()._y + _tempY,false,0 });
//			}
//
//			�»�
//			_tempX = 0;
//			_tempY = 0;
//			for (int i = 10; i < 20; i++)
//			{
//				_tempX -= 40;
//				_tempY -= 32;
//				_temp.push_back({ _pl->getPL()._x + _tempX,_pl->getPL()._y + _tempY,false,0 });
//			}
//
//			 ����
//			_tempX = 0;
//			_tempY = 0;
//			for (int i = 20; i < 30; i++)
//			{
//				_tempX -= 40;
//				_tempY += 32;
//				_temp.push_back({ _pl->getPL()._x + _tempX,_pl->getPL()._y + _tempY,false,0 });
//			}
//
//			 ���
//			_tempX = 0;
//			_tempY = 0;
//			for (int i = 30; i < 40; i++)
//			{
//				_tempX += 40;
//				_tempY -= 32;
//				_temp.push_back({ _pl->getPL()._x + _tempX,_pl->getPL()._y + _tempY,false,0 });
//			}
//		}
//
//
//
//		for (int i = 0; i < 10; i++)
//		{
//			IMAGEMANAGER->findImage("��ų�ұ��1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
//			IMAGEMANAGER->findImage("��ų�ұ��1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 255, _skillFrame, 0);
//		}
//		for (int i = 10; i < 20; i++)
//		{
//			IMAGEMANAGER->findImage("��ų�ұ��1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
//			IMAGEMANAGER->findImage("��ų�ұ��1_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 255, _skillFrame, 0);
//		}
//
//		for (int i = 20; i < 30; i++)
//		{
//			IMAGEMANAGER->findImage("��ų�ұ��1_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
//			IMAGEMANAGER->findImage("��ų�ұ��1_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 255, _skillFrame, 0);
//		}
//		for (int i = 30; i < 40; i++)
//		{
//			IMAGEMANAGER->findImage("��ų�ұ��1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 150, _skillFrame, 0);
//			IMAGEMANAGER->findImage("��ų�ұ��1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 250, 255, _skillFrame, 0);
//		}
//
//		 ������ ����Ʈ
//		IMAGEMANAGER->findImage("��ų����Ʈ1")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 80, _pl->getPL()._y - 150, 150, _skillFrame, 0);
//		IMAGEMANAGER->findImage("��ų����Ʈ1����")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 80, _pl->getPL()._y - 150, 255, _skillFrame, 0);
//
//		IMAGEMANAGER->findImage("��ų����Ʈ2")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 80, _pl->getPL()._y - 50, 150, _skillFrame, 0);
//		IMAGEMANAGER->findImage("��ų����Ʈ2����")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 80, _pl->getPL()._y - 50, 255, _skillFrame, 0);
//
//		if (IMAGEMANAGER->findImage("��ų����Ʈ1")->getFrameX() >= IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
//		{
//			_skill.reset();
//			_skill.set(2, 1);
//			_skillFrame = 0;
//			_tick = 0;
//		}
//	}
//#pragma endregion
//	}
//	else if (_skill[2] == 1)
//{
//#pragma region �ұ��2
//if (_tick % 8 == 0)
//{
//	_skillFrame++;
//}
//
//for (int i = 0; i < 10; i++)
//{
//	IMAGEMANAGER->findImage("��ų����Ʈ3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 150, _skillFrame, 0);
//	IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 255, _skillFrame, 0);
//}
//for (int i = 10; i < 20; i++)
//{
//	IMAGEMANAGER->findImage("��ų����Ʈ3_1")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 150, _skillFrame, 0);
//	IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 255, _skillFrame, 0);
//}
//
//for (int i = 20; i < 30; i++)
//{
//	IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 150, _skillFrame, 0);
//	IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 255, _skillFrame, 0);
//}
//for (int i = 30; i < 40; i++)
//{
//	IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 150, _skillFrame, 0);
//	IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _temp[i].x, _temp[i].y - 100, 255, _skillFrame, 0);
//}
//
//if (IMAGEMANAGER->findImage("��ų����Ʈ3")->getFrameX() >= 11)
//{
//	_skill.reset();
//	_skill.set(3, 1);
//	_skillFrame = 0;
//	_tick = 0;
//	_temp[0].start = true;
//	for (int i = 0; i < _temp.size(); i++)
//	{
//		_frame.push_back(0);
//	}
//}
//#pragma endregion
//}
//	else if (_skill[4] == 1)
//	{
//	if (_tick % 5 == 0)
//	{
//		_skillFrame++;
//		_frame[0]++;
//		_frame[1]++;
//		if (_frame[1] > IMAGEMANAGER->findImage("��ų����Ʈ3_1")->getMaxFrameX()) _frame[2]++;
//	}
//
//	if (_frame[0] < IMAGEMANAGER->findImage("��ų����Ʈ3")->getMaxFrameX())
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			IMAGEMANAGER->findImage("��ų����Ʈ3")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 40, 100, _frame[0], 0);
//			IMAGEMANAGER->findImage("��ų����Ʈ3����")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 40, 255, _frame[0], 0);
//		}
//	}
//
//	if (_frame[1] < IMAGEMANAGER->findImage("��ų����Ʈ3_1")->getMaxFrameX())
//	{
//		for (int i = 0; i < 4; i++)
//		{
//			IMAGEMANAGER->findImage("��ų����Ʈ3_1")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 40, 100, _frame[1], 0);
//			IMAGEMANAGER->findImage("��ų����Ʈ3_1����")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() + 20, _em[i]->getEnemyY() - 40, 255, _frame[1], 0);
//		}
//	}
//
//
//	 �ʱ�ȭ
//	if (_frame[2] > IMAGEMANAGER->findImage("��ų�ұ��2")->getMaxFrameX())
//	{
//		_skill.reset();
//		_skill.set(5, 1);
//		_skillFrame = 0;
//		_tick = 0;
//		_particle.clear();
//		_frame.clear();
//		for (int i = 0; i < _temp.size(); i++)
//		{
//			_frame.push_back(0);
//		}
//
//		 ��ƼŬ ���� �߰�
//		for (int i = 0; i < 4; i++)
//		{
//			for (int j = 0; j < 10; j++)
//			{
//				_particle.push_back({ RND->getFromFloatTo(_em[i]->getEnemyX() - 100,_em[i]->getEnemyX() + 100),
//									RND->getFromFloatTo(_em[i]->getEnemyY() - 60,_em[i]->getEnemyY() + 100),
//									0,0,255,false });
//			}
//
//		}
//
//	}
//
//	}
//	else if (_skill[5] == 1)
//	{
//		if (_tick % 5 == 0)
//		{
//			_skillFrame++;
//			_frame[0]++;
//			_frame[1]++;
//			_frame[2]++;
//
//			if (_frame[1] > 4 && _particle[0].alpha != 0)_frame[1] = 0;
//			if (_frame[2] > 15)_frame[2] = 0;
//		}
//
//		if (_frame[0] < IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
//		{
//			for (int i = 0; i < 4; i++)
//			{
//				IMAGEMANAGER->findImage("��ų����Ʈ1")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() - 70,
//																				_em[i]->getEnemyY() - 130, 100, _frame[0], 0);
//				IMAGEMANAGER->findImage("��ų����Ʈ1����")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() - 70, 
//																				_em[i]->getEnemyY() - 130, 255, _frame[0], 0);
//			}
//		}
//
//
//		for (int i = 0; i < 4; i++)
//		{
//			IMAGEMANAGER->findImage("��ų�ٴں�")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() - 30, _em[i]->getEnemyY(), 100, _frame[1], 0);
//			IMAGEMANAGER->findImage("��ų�ٴںұ���")->alphaFrameRender(getMemDC(), _em[i]->getEnemyX() - 30, _em[i]->getEnemyY(), 255, _frame[1], 0);
//		}
//
//		for (int i = 0; i < _particle.size(); i++)
//		{
//			IMAGEMANAGER->findImage("��ų��ƼŬ3")->alphaFrameRender(getMemDC(), _particle[i].x, _particle[i].y, _particle[i].alpha, _frame[2], 0);
//			_particle[i].y += _particle[i].speed;
//			_particle[i].speed -= 0.05f;
//			_particle[i].alpha -= 2;
//			if (_particle[i].alpha <= 0) _particle[i].alpha = 0;
//		}
//
//		if (_frame[0] > IMAGEMANAGER->findImage("��ų����Ʈ1")->getMaxFrameX())
//		{
//			_skill.reset();
//			_skill.set(6, 1);
//			_skillFrame = 0;
//			_tick = 0;
//			_frame.clear();
//			_particle.clear();
//		}
//		
//
//	}
//
//}

