#pragma once
#include "gameNode.h"

struct RB_BULLET
{
	image* _bulletImg;

	float x, y;
	float fireX, fireY;
	float angleX;
	float angleY;
	float gravity;
	float speed;
	float radius;
	float rotateRate;

	bool isfire;
	int count;

	RECT rc;
};

struct RB_BULLET_PNG
{
	gdipImage* _bulletImg[4];
	image* _image;
	float x, y;
	float fireX, fireY;
	float angleX_first;
	float angleY_first;
	float angleX_second;
	float angleY_second;
	float gravity;
	float speed;
	float radius;
	float rotateRate;
	int damage;
	bool isfire;
	bool isActive_first;
	bool isActive_second;
	bool isActive_third;
	int count;
	int limitedCount;
	int indexX;
	int indexY;
	RECT rc;
};


#define CARROT 5
class yerinaCarrot : public gameNode
{
private:
	
	vector<RB_BULLET> _vCarrot;
	vector<RB_BULLET>::iterator _viCarrot;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, int dir);
	void move();

	vector<RB_BULLET> getVCarrot() { return _vCarrot; }
	void setVCarrotY(float _y, int _i) { _vCarrot[_i].y = _y; }
	void setVCarrotGravity(float _gravity, int _i) { _vCarrot[_i].gravity = _gravity; }

	

	yerinaCarrot() {}
	~yerinaCarrot() {}
};



#define BLUEBULLET 20
class ribbonBlueBullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vBigBullet;
	//RB_BULLET _smallBullet;
	vector<RB_BULLET_PNG> _vSmallBullet;

	gdipImage* _image[3];
	gdipImage* _image_Big;


	int count;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, int dir);
	void move();
	void animation();

	vector<RB_BULLET_PNG> getBigBullet() { return _vBigBullet; }
	vector<RB_BULLET_PNG> getSmallBullet() { return _vSmallBullet; }

	/*int getIndexX() { return indexX; }
	void setIndexX(int _indexX) { indexX = _indexX; }
	int getIndexY() { return indexY; }
	void setIndexY(int _indexY) { indexY = _indexY; }*/

	ribbonBlueBullet() {}
	~ribbonBlueBullet() {}
};


#define BLUERAINS 60

class ribbonBlueRain : public gameNode
{
private:

	vector<RB_BULLET_PNG> _vBlueRain;

	//gdipImage* _image[3];
	gdipImage* _image;
	gdipImage* _blueRainImage;

	int count;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void fire(float x, float y, int dir);
	void move();
	//void animation();

	vector<RB_BULLET_PNG> getBlueRain() { return _vBlueRain; }

	/*int getIndexX() { return indexX; }
	void setIndexX(int _indexX) { indexX = _indexX; }
	int getIndexY() { return indexY; }
	void setIndexY(int _indexY) { indexY = _indexY; }*/

	ribbonBlueRain() {}
	~ribbonBlueRain() {}
};

#define YELLOWS 24 // 3 * 8 
#define SUN 3
#define BLUES 12 
#define FLOWERLEAF 60 // 12 * 5 or 20 * 3

class yerinaT;

class ribbonYellowBlue : public gameNode
{
private:
	yerinaT* _player;

	vector<RB_BULLET_PNG> _vYellow;
	vector<vector<RB_BULLET_PNG>> _vSun;

	float yellowsRotateRate;
	float yellowsLimitSpeed;
	int yellowCount;
	float aimAngle;


	vector<RB_BULLET_PNG> _vFlowerLeaf;
	vector<vector<RB_BULLET_PNG>> _vFlower;


	vector<RB_BULLET_PNG> _vBlue;

	//gdipImage* _image[3];
	/*gdipImage* _image;
	gdipImage* _blueRainImage;*/


	int count;

public:

	HRESULT init();
	void release();
	void update();
	//void render();

	void fire_yellows(float x, float y, int order);
	void fire_blues(float x, float y, int dir);
	void fire_flower(float x, float y, int dir);

	void move_yellows();
	void move_blues(); 
	void move_flower();

	//void animation();


	vector<vector<RB_BULLET_PNG>> getSun() { return _vSun; }
	vector<RB_BULLET_PNG> getBlue() { return _vBlue; }
	vector<vector<RB_BULLET_PNG>> getFlower() { return _vFlower; }

	void setPlayerLink(yerinaT* player) { _player = player; }

	ribbonYellowBlue() {}
	~ribbonYellowBlue() {}
};

#define SPIDERWEBBULLETS 144
class ribbonSpiderWeb : public gameNode
{
private:
	yerinaT* _player;

	vector<RB_BULLET_PNG> _vSpiderWebBullet;
	vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	vector<RB_BULLET_PNG> getSpiderWeb() { return _vSpiderWebBullet; }
	vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }



	void setPlayerLink(yerinaT* player) { _player = player; }

	ribbonSpiderWeb() {}
	~ribbonSpiderWeb() {}
};
//////////////
////º¸½º//////
/////////////

class guided_bullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vGuidedBullet;
	//vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

	yerinaT* _player;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	void setPlayerLink(yerinaT* player) { _player = player; }


	vector<RB_BULLET_PNG> getGuidedBullet() { return _vGuidedBullet; }
	//vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }

	guided_bullet() {}
	~guided_bullet() {}
};

class tornado_bullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vTornadoBullet;
	//vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

	int checkCount;

	yerinaT* _player;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	void setPlayerLink(yerinaT* player) { _player = player; }


	vector<RB_BULLET_PNG> getTornadoBullet() { return _vTornadoBullet; }
	//vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }

	tornado_bullet() {}
	~tornado_bullet() {}
};

class snake_bullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vSnakebullet;
	//vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

	int checkCount;

	yerinaT* _player;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	void setPlayerLink(yerinaT* player) { _player = player; }


	vector<RB_BULLET_PNG> getSnakebullet() { return _vSnakebullet; }
	//vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }

	snake_bullet() {}
	~snake_bullet() {}
};

class polygon_bullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vPolygonBullet;
	//vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

	int checkCount;

	yerinaT* _player;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	void setPlayerLink(yerinaT* player) { _player = player; }


	vector<RB_BULLET_PNG> getPolygonBullet() { return _vPolygonBullet; }
	//vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }

	polygon_bullet() {}
	~polygon_bullet() {}
};

#define SPINSPEED 2
class octopus_bullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vOctopusBullet;
	//vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

	int checkCount;

	yerinaT* _player;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	void setPlayerLink(yerinaT* player) { _player = player; }


	vector<RB_BULLET_PNG> getOctopusBullet() { return _vOctopusBullet; }
	//vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }

	octopus_bullet() {}
	~octopus_bullet() {}
};

class ball_bullet : public gameNode
{
private:
	vector<RB_BULLET_PNG> _vBallBullet;
	//vector<vector<RB_BULLET_PNG>> _vSpider;

	image* _image;
	gdipImage* _pngImage;


	int count;

	int checkCount;

	yerinaT* _player;

public:

	HRESULT init();
	void release();
	void update();

	void fire(float x, float y, int order);

	void move();

	void animation();

	void setPlayerLink(yerinaT* player) { _player = player; }


	vector<RB_BULLET_PNG> getBallBullet() { return _vBallBullet; }
	//vector<vector<RB_BULLET_PNG>> getSpider() { return _vSpider; }

	ball_bullet() {}
	~ball_bullet() {}
};