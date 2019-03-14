//------ 작성자:김명식 ------- 작성일:2013년 11월 25일 월요일 --------//
#include "Stage01.h"
#include "MainMenu.h"
#include "GameOver.h"

CCScene* GameOver::scene()
{
	CCScene* Scene = CCScene::create();
	GameOver* Layer = GameOver::create();
	Scene->addChild(Layer);
	return Scene;
}

bool GameOver::init()
{
	if(CCLayer::init()==false)
	{
		return false;
	}

	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/gameover.ogg", false);
	this->CreateBackGround();
	this->BackButton();

	return true;
}

void GameOver::CreateBackGround(){
	CCSprite *BackGroundImage = CCSprite::create("background/gameover.png");
	BackGroundImage->setAnchorPoint(ccp(0,0));
	this->setPosition(ccp(0,0));
	this->addChild(BackGroundImage,0);
}

void GameOver::BackButton(){
	CCMenuItemImage *Back = CCMenuItemImage::create(
			"button/backA.png",
			"button/backB.png",
			this,
			menu_selector(Stage01::BackTouch)
	);
	Back->setPosition(ccp(760,440));
	Back->setScale(0.8);
	CCMenu *BMenu = CCMenu::create(Back,NULL);
	BMenu->setPosition(ccp(0,0));
	this->addChild(BMenu);
}

//뒤로가기 버튼 눌렀을때 MainMenu로 복귀하는 메서드
void GameOver::BackTouch(CCObject *sender)
{
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, MainMenu::scene()));
}
