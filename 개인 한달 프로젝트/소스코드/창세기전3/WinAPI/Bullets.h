#pragma once
#include "GameNode.h"

struct tagBullet
{
	GImage* img;
	RECT rc;
	int radius;
	int count;
	float x,y;
	float fireX, fireY;
	float angle;
	float speed;
	bool fire;
};


// 배열처럼 미리 장전해두고 발사
// 메모리 소모량이크다 하지만 연산속도가 빠르다
class Missile : public GameNode
{
private:
	vector<tagBullet>_vBullet;
	vector<tagBullet>::iterator _viBullet;

	//어느정도 거리 이상이 되면 삭제될수있게 판단하는 변수
	float _range;




public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);


	void fire(float x, float y);
	void draw(void);
	void move(void);




	Missile() {}
	~Missile() {}
};







// 쏠때마다 만들고 삭제
// 메모리 소모량이 핵이득 하지만 연산속도가 느리다
class MissileM1 : public GameNode
{
private:

	vector<tagBullet>_vBullet;
	vector<tagBullet>::iterator _viBullet;

	//어느정도 거리 이상이 되면 삭제될수있게 판단하는 변수
	float _range;
	int _bulletMax;


public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);


	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }
	void removeBullet(int arrNum);

	MissileM1() {}
	~MissileM1() {}
};



class Bullets : public GameNode
{
private:


public:


	
};

class Beam : public GameNode
{
private:

	vector<tagBullet>_vBullet;
	vector<tagBullet>::iterator _viBullet;

	// typedef vector(tagBullet)::iterator iterBullet;

	//어느정도 거리 이상이 되면 삭제될수있게 판단하는 변수
	float _range;
	int _bulletMax;


public:
	HRESULT init(int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);


	void fire(float x, float y);
	void draw(void);
	void move(void);

	vector<tagBullet> getBullet(void) { return _vBullet; }


	Beam() {}
	~Beam() {}
};

//=========================================================================================================
// 공용 총알
class Bullet : public GameNode
{
private:
	vector<tagBullet>_vBullet;
	vector<tagBullet>::iterator _viBullet;

	const char* _imageName;
	int _bulletMax;
	float _range;




public:
	HRESULT init(const char* imagName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);


	void fire(float x, float y, float angle, float speed);
	void draw(void);
	void move(void);

	void removeBullet(int arrNum);

	vector<tagBullet> getBullet(void) { return _vBullet; }



	Bullet(void) {}
	virtual ~Bullet(void) {}
};

