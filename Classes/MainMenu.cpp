//------ 작성자:김명식 ------- 작성일:2013년 11월 20일 수요일 --------//
#include "Stage01.h"
#include "MainMenu.h"
#include "GameFinish.h"
#include "GameOver.h"
#include "GameLogo.h"

CCScene* MainMenu::scene()
{
	CCScene* Scene = CCScene::create();
	MainMenu* Layer = MainMenu::create();
	Scene->addChild(Layer);
	return Scene;
}

bool MainMenu::init()
{
	if(CCLayer::init()==false)
	{
		return false;
	}

	this->CreateBackGround();
	this->CreateButton();
	this->scheduleOnce(schedule_selector(MainMenu::introTick), 0.5f);
	return true;
}

void MainMenu::introTick()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/menuLoop.mp3", true);
}

void MainMenu::CreateBackGround(){
	CCSprite *BackGroundImage = CCSprite::create("background/mainmenu.png");
	BackGroundImage->setAnchorPoint(ccp(0,0));
	this->setPosition(ccp(0,0));
	this->addChild(BackGroundImage,0);
}

void MainMenu::CreateButton(){

	CCMenuItemImage *Start = CCMenuItemImage::create(
			"button/main/StartA.png",
			"button/main/StartB.png",
			this,
			menu_selector(MainMenu::StartTouch)
	);
	Start->setPosition(ccp(400,250));

	CCMenuItemImage *Option = CCMenuItemImage::create(
			"button/main/OptionA.png",
			"button/main/OptionB.png",
			this,
			menu_selector(MainMenu::OptionTouch)
	);
	Option->setPosition(ccp(400,160));

	CCMenuItemImage *Exit = CCMenuItemImage::create(
			"button/main/ExitA.png",
			"button/main/ExitB.png",
			this,
			menu_selector(MainMenu::ExitTouch)
	);
	Exit->setPosition(ccp(400,70));

	CCMenu *Menu = CCMenu::create(Start,Option,Exit,NULL);
	Menu->setPosition(ccp(0,0));
	this->addChild(Menu);
}

void MainMenu::StartTouch(CCObject *sender)
{
	//SimpleAudioEngine::sharedEngine()->playEffect("sound/button.mp3"); //효과음
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, Stage01::scene()));
}

void MainMenu::OptionTouch(CCObject *sender)
{

}

void MainMenu::ExitTouch(CCObject *sender)
{
	CCDirector::sharedDirector()->end(); //어플종료
}
