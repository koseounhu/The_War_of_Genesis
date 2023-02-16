#include "Stdafx.h"
#include "Tiger.h"
#include "Player.h"
#include "Vermouth.h"

HRESULT Tiger::init(void)
{
	// ����
	_tick = 0;
	_step.reset();

	// ��ų���ۼ�Ŭ
	_circleFrame = 0;

	// ȣ����
	_ti.x = _ti.y = _ti.frame = 0;
	_ti.alpha = 255;

	// ����
	_light.frame = 0;
	_light.alpha = 150;

	// ���۽� 0�� 1�� ���� �س��� ��ų ��밡�� , ��ų������ ��Ʈ�� �����ϰ� 0���� �ٽ� 1�� �����
	_step.set(0, 1);
	
	return S_OK;
}

void Tiger::release(void)
{
	// ��ų ��� ����
	/*
	0==1 ��ų��
	1==1 ȣ����
	2==1 ����
	3==1 
	
	
	*/
}

void Tiger::update(Player* _pl, Vermouth* _ve)
{
	// ����
	_tick++;
	
	// ���� ��Ŭ
	if (_step[0])
	{
		if (_tick % 7 == 0) _circleFrame++;

		// ���·� ���� 1�������ü��հԼ���
		if(_pl->getPL()._state !=3)	SOUNDMANAGER->play("��ų��", 1.0f);
		_pl->setPState(3);

		// ������ �������
		if (_circleFrame > IMAGEMANAGER->findImage("��ų��")->getMaxFrameX())
		{
			_ti.x = _pl->getPL()._x - 100;
			_ti.y = _pl->getPL()._y - 250;
			_step.reset();
			_step.set(1, 1);
		}
	}

	// ȣ����
	if (_step[1])
	{
		if (!SOUNDMANAGER->isPlaySound("ȣ����")) SOUNDMANAGER->play("ȣ����", 1.0f);

		if (_tick % 10 == 0) _ti.frame++;
		if (_ti.alpha > 3)_ti.alpha -= 2;
		if (_ti.frame > IMAGEMANAGER->findImage("ȣ����")->getMaxFrameX())
			_ti.frame = IMAGEMANAGER->findImage("ȣ����")->getMaxFrameX();
		
		_ti.y++;

		// �ʱ�ȭ�ϰ� ���� ���
		if (_ti.alpha <= 3)
		{
			_step.reset();
			_step.set(2, 1);	// ����
			_step.set(3, 1);	// ����

			// ������ ����
			for (int i = 0; i < _countof(_dash); i++)
			{
				_dash[i].x = _pl->getPL()._x - 70;
				_dash[i].y = _pl->getPL()._y - 80;
				_dash[i].speed = 15.0f;
				_dash[i].frame = 0;
				_dash[i].effectFrame = 0;
				_dash[i].alpha = 255;
			}
		}
	}

	// ����
	if (_step[2])
	{
		if (_tick % 5 == 0)_light.frame++;
		if (_light.frame > IMAGEMANAGER->findImage("��Ż����")->getMaxFrameX())
		{
			_light.frame = 0;
			_step.set(2, 0);
		}
	}

	// ����
	if (_step[3])
	{
		if (!_atkSound)
		{
			SOUNDMANAGER->play("ȣ���̾���", 1.0f);
			_atkSound = true;
		}

#pragma region ���� ����
		// ������ ����
		for (int i = 0; i < 8; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].x = _dash[0].x;
				_shadow[i].y = _dash[0].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}
		// ���̵� ����
		for (int i = 8; i < 10; i++)
		{
			if (!_shadow[7].start)
			{
				_shadow[i].x = _shadow[0].x;
				_shadow[i].y = _shadow[0].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}

		// ���� 
		if (_pl->getPL()._x - 270 < _dash[0].x)
		{
			_dash[0].x -= _dash[0].speed;
			if (_dash[0].speed >= 0) _dash[0].speed -= 0.5;
		}
		// ���� ���Ʒ�
		if (_dash[0].x < _shadow[8].x)
		{
			_shadow[8].x -= _shadow[8].speed;
			if (_shadow[8].speed >= 0) _shadow[8].speed -= 0.5;
			_shadow[9].x -= _shadow[9].speed;
			if (_shadow[8].speed >= 0) _shadow[9].speed -= 0.5;
		}
		if(_dash[0].x == _shadow[8].x) _dash[0].frame++;

		if (_dash[0].effectFrame >=4)
		{
			_dash[0].frame++;
		}
		
		// ����Ʈ
		if (_tick % 12 == 0 && _pl->getPL()._x - 90 > _dash[0].x)_dash[0].effectFrame++;
#pragma endregion

#pragma region ���� ����

		// ������ ����
		for (int i = 10; i < 18; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].x = _dash[1].x+50;
				_shadow[i].y = _dash[1].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}
		// ���̵� ����
		for (int i = 18; i < 20; i++)
		{
			if (!_shadow[17].start)
			{
				_shadow[i].x = _shadow[10].x;
				_shadow[i].y = _shadow[10].y;
				_shadow[i].alpha = 255;
				_shadow[i].speed = 15.0f;
			}
		}
		// ���� 
		if (_pl->getPL()._x + 230 > _dash[1].x)
		{
			_dash[1].x += _dash[1].speed;
			if (_dash[1].speed >5) _dash[1].speed -= 0.5;
		}
		// ���� �¿�
		if (_dash[1].x > _shadow[18].x)
		{
			
			_shadow[18].x += _shadow[18].speed;
			if (_shadow[18].speed >5) _shadow[18].speed -= 0.5;
			_shadow[19].x += _shadow[19].speed;
			if (_shadow[18].speed >5) _shadow[19].speed -= 0.5;
		}
		if (_dash[1].x == _shadow[18].x) _dash[1].frame++;

		if (_dash[1].effectFrame >= 4)
		{
			_dash[1].frame++;
		}

		// ����Ʈ
		if (_tick % 12 == 0 && _pl->getPL()._x < _dash[1].x)_dash[1].effectFrame++;

#pragma endregion

		// ������ ��
		if (SOUNDMANAGER->getPosition("ȣ����") >=2500 )
		{
			_atkSound = false;

			_step.set(3, 0);
			_step.set(4, 1);
			for (int i = 0; i < _countof(_dash); i++)
			{
				_dash[i].x = _pl->getPL()._x - 70;
				_dash[i].y = _pl->getPL()._y - 80;
				_dash[i].speed = 15.0f;
				_dash[i].frame = 0;
				_dash[i].effectFrame = 0;
				_dash[i].alpha = 255;
			}
		}
	}
	
}

void Tiger::render(Player* _pl, Vermouth* _ve)
{
	// ��ų����
	if (_step[0])
	{
		IMAGEMANAGER->findImage("��ų��")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 100, _circleFrame, 0);
	}

	// ȣ����
	else if (_step[1])
	{
		IMAGEMANAGER->findImage("ȣ����")->alphaFrameRender(getMemDC(), _ti.x, _ti.y, _ti.alpha, _ti.frame, 0);
	}


	// ����
	if (_step[3])
	{
		_pl->setPState(5); // �÷��̾� ������

		// ������ ����
		for (int i = 0; i < 10; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}
		for (int i = 10; i < 20; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}
		for (int i = 20; i < 30; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}
		for (int i = 30; i < 40; i++)
		{
			if (!_shadow[i].start)
			{
				_shadow[i].start = true;
				break;
			}

			if (_shadow[i].start)
			{
				_shadow[i].alpha -= 5;
				if (_shadow[i].alpha <= 0) _shadow[i].alpha = 0;
			}
		}

		// ����
		for (int i = 0; i < 8; i++)
		{
			IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _shadow[i].x, _shadow[i].y, _shadow[i].alpha, 0, 0);
		}
		IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _shadow[8].x, _shadow[8].y - 60, _shadow[8].alpha, 0, 0);
		IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _shadow[9].x, _shadow[9].y + 60, _shadow[9].alpha, 0, 0);

		IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _dash[0].x, _dash[0].y, _dash[0].alpha, _dash[0].frame, 0);
		IMAGEMANAGER->findImage("��������Ʈ")->alphaFrameRender(getMemDC(), _dash[0].x - 70, _dash[0].y - 50, _dash[0].alpha, _dash[0].effectFrame, 0);

		// ����
		for (int i = 10; i < 18; i++)
		{
			IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _shadow[i].x, _shadow[i].y, _shadow[i].alpha, 0, 1);
		}
		IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _shadow[18].x, _shadow[18].y - 60, _shadow[18].alpha, 0, 1);
		IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _shadow[19].x, _shadow[19].y + 60, _shadow[19].alpha, 0, 1);

		IMAGEMANAGER->findImage("��������")->alphaFrameRender(getMemDC(), _dash[1].x, _dash[1].y, _dash[1].alpha, _dash[1].frame, 1);
		IMAGEMANAGER->findImage("��������Ʈ")->alphaFrameRender(getMemDC(), _dash[1].x, _dash[1].y - 50, _dash[1].alpha, _dash[1].effectFrame, 1);
	}
	
	// ������Ʈ�Ǵ� ������ ������ ���� �Ϻη� �ٸ�����
	// ����
	if (_step[2])
	{
		IMAGEMANAGER->findImage("��Ż����")->alphaFrameRender(getMemDC(), _ve->getVE()._x - 85, _ve->getVE()._y - 315, 40, _light.frame, 0);
		IMAGEMANAGER->findImage("��Ż��������")->alphaFrameRender(getMemDC(), _ve->getVE()._x - 85, _ve->getVE()._y - 365, _light.alpha, _light.frame, 0);
	}



	if (_step[4])
	{
		_pl->setPState(0); // �÷��̾� �׸���
	}

	











}
