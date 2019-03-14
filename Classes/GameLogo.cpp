//------ 작성자:김명식 ------- 작성일:2013년 11월 25일 월요일 --------//
#include "MainMenu.h"
#include "GameLogo.h"

CCScene* GameLogo::scene()
{
	CCScene* Scene = CCScene::create();
	GameLogo* Layer = GameLogo::create();
	Scene->addChild(Layer);
	return Scene;
}

bool GameLogo::init()
{
	if(CCLayer::init()==false)
	{
		return false;
	}

	CCSprite *BackGroundImage = CCSprite::create("background/Logo.png");
	BackGroundImage->setAnchorPoint(ccp(0,0));
	this->setPosition(ccp(0,0));
	this->addChild(BackGroundImage,0);

	this->scheduleOnce(schedule_selector(GameLogo::introTick), 3.0f);

	return true;
}

void GameLogo::introTick()
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, MainMenu::scene()));
}
