#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "stage_MAPt.h"
#include "RBenemyManager.h"
#include "rabiribiBullet.h"
#include "UIT.h"

struct talkBox2
{
	float x;
	float y;
	RECT rc;
	image* _image[4];
	bool isActive;
	CONVERSATIONEMOTION emotion;

};
class stage_FinalBoss_Scene : public gameNode
{
private:
	yerinaT* _player;
	stage_FinalBoss_MAPt* _map;
	RBenemyManager* _eMG;
	UIT* _ui;


	image* _bgImage[8];

	int count;
	bool isStartTalk;
	bool isEndTalk;

	//대화관련
	talkBox2 conversation;
	talkBox2 yerina;
	talkBox2 irisu;

	vector<string> textInf;
	vector<string> textInf2;

	int content;
	int maxContent;
	int textLength;




public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void TalkerMove();
	void battleTalkScene();
	void contentOfconversation(vector<string> _temp);

	stage_FinalBoss_Scene() {}
	~stage_FinalBoss_Scene() {}
};

