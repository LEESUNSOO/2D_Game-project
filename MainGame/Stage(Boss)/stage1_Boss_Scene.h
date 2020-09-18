#pragma once
#include "gameNode.h"
#include "yerinaT.h"
#include "stage_MAPt.h"
#include "RBenemyManager.h"
#include "rabiribiBullet.h"
#include "UIT.h"

struct talkBox
{
	float x;
	float y;
	RECT rc;
	image* _image[4];
	bool isActive;
	CONVERSATIONEMOTION emotion;

};
class stage1_Boss_Scene : public gameNode
{
private:
	yerinaT* _player;
	stage1_BOSS_MAPt* _map;
	RBenemyManager* _eMG;
	UIT* _ui;

	int count;
	bool isStartTalk;
	bool isEndTalk;


	//대화관련
	talkBox conversation;
	talkBox yerina;
	talkBox ribbon;

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

	stage1_Boss_Scene() {}
	~stage1_Boss_Scene() {}
};

