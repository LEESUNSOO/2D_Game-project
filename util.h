#pragma once
//=============================================================
//	## namespace MY_UTIL ##
//=============================================================

#define PI 3.141592654f		//180도
#define PI2 (PI * 2)			//360도

//나중에 이미지 회전시 사용할 값
#define PI_2 (PI / 2)		//90도
#define PI_4 (PI / 4)		//45도
#define PI_8 (PI / 8)		//22.5도

#define MAGENTA RGB(255,0,255)

namespace MY_UTIL //이름은 너희맘대로 변경해도 된다
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
	//씬의 제목보여주기
	void showTitle(HDC hdc, const char* title, int x = 0, int y = 70, COLORREF color = RGB(255, 255, 0));
};

struct tagRc
{
	float x;
	float y;
	float speed;
	float angle;
	float radius;
	bool isActive;
	RECT rc;
	int alpha;


};

struct tagPos
{
	float x;
	float y;
};

enum CONVERSATIONEMOTION
{
	NORMAL, SAD, HAPPY, ANGRY
};


enum RIBBONSTATE
{
	R_MOVE, R_ATTACT1, R_ATTACT2, RIBBONEND
};

enum STATE
{
	IDLE, JUMP, FALL, BOMB, SPRINGJUMP, MOVE, SLIDE, BEATTACTED, DEAD, ATTACT1, ATTACT2, ATTACT3, ATTACT4, ATTACT5, DOWNATTACT, UPATTACT, YERINAEND
};

enum HAMMER
{
	HAMMER1, HAMMER2, HAMMER3, HAMMER4, HAMMER5, HAMMERDOWN, HAMMERUP, RIBBONSKILL, HAMMER_END
};

enum DIRECTION
{
	LEFT, RIGHT
};

enum BOSSTYPE
{
	RIBBON_BOSS, FINAL_BOSS
};

enum ribbonSkill
{
	STAY, BODYRUSH, BBYORORONG, BLUERAIN, SUNBEAM, FLOWERBEAM, SPIDERWEB, RIBBONSKILLEND
};

enum finalBossSkill
{
	F_STAY, GUIDEDMISSILE, TORNADO, SNAKE, POLYGON, OCTOPUS, BALL, FINALBOSSSKILLEND
};

enum ENEMY_TYPE
{
	MUSHROOM, PUPPY, RABBIT, CHICK, CHIPMUNK, BEE, FLOWER, EYE, PIG, CAT, CAPSULE, MAGICSTICK, TYPE_END
};

enum ENEMY_STATE
{
	E_IDLE, E_MOVE, E_JUMP, E_FALL, E_BEATTACTED, E_ATTACK,  E_SHOOT, E_DEAD, E_STATE_END
};

enum ENEMY_DIRECT
{
	E_LEFT, E_RIGHT, DIR_END
};

enum STAGE_NUMBER
{
	STAGE1, STAGE2, STAGE3, STAGE4, STAGEBOSS1, STAGE6, FINALBOSS, STAGE8, STAGE9, STAGE10, STAGE11, STAGE12, STAGE13, STAGEBOSS2, TOWN, STAGE_END
};

