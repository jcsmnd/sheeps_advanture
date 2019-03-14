//------ 작성자:김명식 ------- 작성일:2013년 11월 25일 월요일 --------//
#ifndef sa_GameOver
#define sa_GameOver

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameOver : public CCLayer{
public:
	virtual bool init();

	static CCScene *scene();

	CREATE_FUNC(GameOver);

	void CreateBackGround();
	void BackButton();
	void BackTouch(CCObject *sender);
};
#endif
