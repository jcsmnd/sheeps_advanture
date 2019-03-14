//------ 작성자:김명식 ------- 작성일:2013년 11월 20일 수요일 --------//
#include "AppDelegate.h"
#include "cocos2d.h"
#include "Stage01.h"
#include "MainMenu.h"
#include "Common.h"
#include "GameLogo.h"


USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCEGLView::sharedOpenGLView()->setFrameSize(winSize.width, winSize.height);
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(DESIGN_WIDTH, DESIGN_HEIGHT, kResolutionShowAll); //해상도 조절

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = GameLogo::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
