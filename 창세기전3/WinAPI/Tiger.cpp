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
	_light.pillarFrame = 0;
	_light.groundFrame = 0;
	_light.alpha = 200;
	
	return S_OK;
}

void Tiger::release(void)
{
	// ��ų ��� ����
	/*
	0==0 ��ų��
	0==1 ȣ����
	1==1 ����
	
	
	
	*/
}

void Tiger::update(Player* _pl, Vermouth* _ve)
{
	// ����
	_tick++;
	



	// ���� ��Ŭ
	if (_step[0] == 0)
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
			_step.set(0, 1);
		}
	}

	// ȣ����
	if (_step[0] == 1)
	{
		if (_tick % 10 == 0) _ti.frame++;
		if (_ti.alpha > 3)_ti.alpha -= 2;
		if (_ti.frame > IMAGEMANAGER->findImage("ȣ����")->getMaxFrameX())
			_ti.frame = IMAGEMANAGER->findImage("ȣ����")->getMaxFrameX();
		
		_ti.y++;

		// �ʱ�ȭ�ϰ� ���� ���
		if (_ti.alpha <= 3)
		{
			// _step.reset();	�����ϸ� ���ۼ�Ŭ �� ���ͼ� �����ϸ�ȵ�
			_step.set(1, 1);
		}

	}

	if (_step[1] == 1)
	{
		if (_tick % 15 == 0)_light.pillarFrame++;
		if (_light.pillarFrame > IMAGEMANAGER->findImage("�������")->getMaxFrameX())_light.pillarFrame = 0;

		if (_tick % 7 == 0)_light.groundFrame++;
		if (_light.groundFrame > IMAGEMANAGER->findImage("�����ٴ�")->getMaxFrameX())_light.groundFrame = 0;
	}
	
}

void Tiger::render(Player* _pl, Vermouth* _ve)
{
	if (_step[0] == 0)
	{
		IMAGEMANAGER->findImage("��ų��")->alphaFrameRender(getMemDC(), _pl->getPL()._x - 110, _pl->getPL()._y - 100, 100, _circleFrame, 0);
	}


	else if (_step[0] == 1)
	{
		IMAGEMANAGER->findImage("ȣ����")->alphaFrameRender(getMemDC(), _ti.x, _ti.y, _ti.alpha, _ti.frame, 0);
	}
	

	if (_step[1] == 1)
	{
		// IMAGEMANAGER->findImage("�����ٴ�")->alphaFrameRender(getMemDC(), _ve->getVE()._x-55, _ve->getVE()._y-70, _light.alpha, _light.groundFrame, 0);
		// IMAGEMANAGER->findImage("�������")->alphaFrameRender(getMemDC(), _ve->getVE()._x-32, _ve->getVE()._y-290, _light.alpha, _light.pillarFrame, 0);

		IMAGEMANAGER->findImage("��Ż����")->alphaFrameRender(getMemDC(), _ve->getVE()._x-55, _ve->getVE()._y-70, 40, _light.groundFrame, 0);
		IMAGEMANAGER->findImage("��Ż��������")->alphaFrameRender(getMemDC(), _ve->getVE()._x-55, _ve->getVE()._y-70, _light.alpha, _light.groundFrame, 0);
	}

	










}
