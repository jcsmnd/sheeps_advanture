//------ 작성자:김명식 ------- 작성일:2013년 11월 20일 수요일 --------//
#ifndef sa_GameLogo_sa
#define sa_GameLogo_sa

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

class GameLogo : public CCLayer{
public:
	virtual bool init();
	static CCScene *scene();
	CREATE_FUNC(GameLogo);

	void introTick();
};
#endif
