//------ 작성자:김명식 ------- 작성일:2013년 11월 20일 수요일 --------//
#ifndef sa_MainMenu
#define sa_MainMenu

#include "cocos2d.h"

using namespace cocos2d;

//static CCDictionary s_dic;

class MainMenu : public CCLayer{
public:
	virtual bool init();

	static CCScene *scene();

	CREATE_FUNC(MainMenu);

	void CreateBackGround();
	void CreateButton();
	void StartTouch(CCObject *sender);
	void OptionTouch(CCObject *sender);
	void ExitTouch(CCObject *sender);

	void introTick();
};
#endif
