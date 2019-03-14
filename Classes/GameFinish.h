//------ 작성자:김명식 ------- 작성일:2013년 11월 20일 수요일 --------//
#ifndef sa_GameFinish
#define sa_GameFinish

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameFinish : public CCLayer{
public:
	virtual bool init();

	static CCScene *scene();

	CREATE_FUNC(GameFinish);

	void CreateBackGround();
	void BackButton();
	void BackTouch(CCObject *sender);
};
#endif
