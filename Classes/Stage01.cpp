//------ 메인작성자:김명식 ------ 아이디어제공&작성보조:이재영 ------ 리소스제작:김수민 ------ 최종작성일:2013년 12월 06일 금요일 ------//
//------ 해결해야할 문제: jumpto에서 위치지정 잘하면 백점프 방지 ------//
#include "Stage01.h"
#include "MainMenu.h"
#include "GameFinish.h"
#include "GameOver.h"

#define STAGE_WIDTH 9600 //스테이지 총 가로길이
#define STAGE_HEIGHT 480 //스테이지 총 세로길이

CCScene* Stage01::scene()
{
	CCScene* Scene = CCScene::create();
	Stage01* Layer = Stage01::create();
	Scene->addChild(Layer);
	return Scene;
}

bool Stage01::init()
{
	if(CCLayer::init()==false)
	{
		return false;
	}

	winSize = CCDirector::sharedDirector()->getWinSize();

	this->scheduleOnce(schedule_selector(Stage01::TouchStart),2.0f); //터치활성화
	this->createBackgroundParallax(); //배경,타일 패럴렉스노드
	this->createButtons(); //버튼
	this->createSheep(); //캐릭터
	this->BackButton(); //뒤로가기
	this->MovingTile(); //타일 움직임

	this->scheduleOnce(schedule_selector(Stage01::introTick), 0.5f); //배경음 0.5초뒤 시작

	scheduleUpdate(); //중력,충돌체크

	return true;
}

void Stage01::update(float dt)
{
	//중력 효과
	sheep->setPosition(ccp(sheep->getPosition().x, sheep->getPosition().y -10.0));

	//2중 점프 방지
	if(sheep->getPosition().y < 105 || sheep->getPosition().y > 412){
		jumpYN=true;
		JumpBrokenSprite->setVisible(true);
	}

	//충돌구현용 좌표변환
	CCNode *BackgroundNode = this->getChildByTag(1);
	CCNode *worldSheep = sheep;
	World = BackgroundNode->convertToNodeSpace(worldSheep->getPosition());
	sheepRect = CCSprite::create("character/collisionSheep.png");
	sheepRect->setPosition(World);
	//this->addChild(sheepRect);
	//CCLog("World.x = %f",sheepRect->getPosition().x);
	//CCLog("World.y = %f",sheepRect->getPosition().y);
	//CCLog("sheep.x = %f",sheep->getPosition().x);
	//CCLog("sheep.y = %f",sheep->getPosition().y);
	//CCLog("BackgroundNode.x = %f",BackgroundNode->getPosition().x);
	//CCLog("BackgroundNode.y = %f",BackgroundNode->getPosition().y);

	//양이 화면 화면 맨밑, 맨위로 떨어지면 게임오버
	if(sheep->getPosition().y<=0.0 || sheep->getPosition().y>=480.0){
		SheepDead();
	}

	//충돌체크
	collisionCheck();
}

void Stage01::TouchStart()
{
	this->setTouchEnabled(true);
}

void Stage01::introTick()
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/dungeon.ogg", true);
}

void Stage01::createBackgroundParallax() //패럴렉스 노드
{
	//타일맵,레이어 읽어오기
	stageMap = CCTMXTiledMap::create("tile/Stage01.tmx");
	stageMap->setAnchorPoint(ccp(0,0));

	//배경 스프라이트 1,2,3,4
	CCSprite* background1 = CCSprite::create("background/background1.png");
	background1->setAnchorPoint(ccp(0,0));
	CCSprite* background2 = CCSprite::create("background/background2.png");
	background2->setAnchorPoint(ccp(0,0));
	CCSprite* background3 = CCSprite::create("background/background2.png");
	background3->setAnchorPoint(ccp(0,0));
	CCSprite* background4 = CCSprite::create("background/background2.png");
	background4->setAnchorPoint(ccp(0,0));
	CCSprite* background5 = CCSprite::create("background/background2.png");
	background5->setAnchorPoint(ccp(0,0));
	CCSprite* background6 = CCSprite::create("background/background2.png");
	background6->setAnchorPoint(ccp(0,0));
	CCSprite* background7 = CCSprite::create("background/background2.png");
	background7->setAnchorPoint(ccp(0,0));
	CCSprite* background8 = CCSprite::create("background/background2.png");
	background8->setAnchorPoint(ccp(0,0));
	CCSprite* background9 = CCSprite::create("background/background2.png");
	background9->setAnchorPoint(ccp(0,0));
	CCSprite* background10 = CCSprite::create("background/background2.png");
	background10->setAnchorPoint(ccp(0,0));
	CCSprite* background11 = CCSprite::create("background/background2.png");
	background11->setAnchorPoint(ccp(0,0));
	CCSprite* background12 = CCSprite::create("background/background3.png");
	background12->setAnchorPoint(ccp(0,0));

	//패럴렉스 노드 생성
	CCParallaxNode* BackgroundNode = CCParallaxNode::create();

	BackgroundNode->addChild(background1,0,ccp(1.0f,0.0f),ccp(0,0));
	BackgroundNode->addChild(background2,0,ccp(1.0f,0.0f),ccp(800,0));
	BackgroundNode->addChild(background3,0,ccp(1.0f,0.0f),ccp(1600,0));
	BackgroundNode->addChild(background4,0,ccp(1.0f,0.0f),ccp(2400,0));
	BackgroundNode->addChild(background5,0,ccp(1.0f,0.0f),ccp(3200,0));
	BackgroundNode->addChild(background6,0,ccp(1.0f,0.0f),ccp(4000,0));
	BackgroundNode->addChild(background7,0,ccp(1.0f,0.0f),ccp(4800,0));
	BackgroundNode->addChild(background8,0,ccp(1.0f,0.0f),ccp(5600,0));
	BackgroundNode->addChild(background9,0,ccp(1.0f,0.0f),ccp(6400,0));
	BackgroundNode->addChild(background10,0,ccp(1.0f,0.0f),ccp(7200,0));
	BackgroundNode->addChild(background11,0,ccp(1.0f,0.0f),ccp(8000,0));
	BackgroundNode->addChild(background12,0,ccp(1.0f,0.0f),ccp(8800,0));
	BackgroundNode->addChild(stageMap,0,ccp(1.0f,0.0f),ccp(0,0));
	BackgroundNode->setTag(1);
	this->addChild(BackgroundNode,0);
}

void Stage01::createButtons()
{
	leftSprite = CCSprite::create("button/Left01.png");
	leftSprite->setPosition(ccp(70,50));
	this->addChild(leftSprite,2);

	leftPressedSprite = CCSprite::create("button/Left02.png");
	leftPressedSprite->setPosition(leftSprite->getPosition());
	this->addChild(leftPressedSprite,1);

	rightSprite = CCSprite::create("button/Right01.png");
	rightSprite->setPosition(ccp(170,50));
	this->addChild(rightSprite,2);

	rightPressedSprite = CCSprite::create("button/Right02.png");
	rightPressedSprite->setPosition(rightSprite->getPosition());
	this->addChild(rightPressedSprite,1);

	JumpSprite = CCSprite::create("button/Jump01.png");
	JumpSprite->setPosition(ccp(700,50));
	this->addChild(JumpSprite,2);

	JumpPressedSprite = CCSprite::create("button/Jump02.png");
	JumpPressedSprite->setPosition(JumpSprite->getPosition());
	this->addChild(JumpPressedSprite,1);

	JumpBrokenSprite = CCSprite::create("button/JumpBroken.png");
	JumpBrokenSprite->setPosition(JumpSprite->getPosition());
	this->addChild(JumpBrokenSprite,3);
	JumpBrokenSprite->setVisible(false);
}

void Stage01::createSheep()
{
	//생성
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("character/Sheep.png");
	CCActionInterval *Blink = CCBlink::create(2,8);
	sheep = CCSprite::createWithTexture(texture, CCRectMake(0,0,39.8,60));
	sheep->setPosition(ccp(400,130));
	this->addChild(sheep,1);
	sheep->runAction(Blink);
	movingSheep();
}

void Stage01::movingSheep()
{
	//캐릭터 상태별 움직임
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("character/Sheep.png");
	CCAnimation *animation = CCAnimation::create();
	animation->setDelayPerUnit(0.1);
	for(int i=0;i<3;i++){
		animation->addSpriteFrameWithTexture(texture,CCRectMake(i*39.8,0,39.8,60));
	}
	CCAnimate *animate = CCAnimate::create(animation);
	CCAction* rep = CCRepeatForever::create(animate);

	if(!moving){
		sheep->runAction(rep);
	}

	if(moving){
		sheep->stopAction(rep);
	}
}

bool Stage01::isTouchInside(CCSprite* sprite, CCTouch* touch) //터치 유효체크
{
	CCPoint touchPoint = touch->getLocation();
	CCRect rect = sprite->boundingBox();
	if(rect.containsPoint(touchPoint)){
		return true;
	}
	return false;
}

void Stage01::ccTouchesBegan(CCSet *pTouches, CCEvent* event) //터치 하는 순간 호출
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	isLeftPressed = false;
	isRightPressed = false;
	isJumpPressed = false;

	//터치가 왼쪽,오른쪽,점프 버튼 안에 들어왔는지 확인
	if(this->isTouchInside(leftSprite, touch) == true){
		leftSprite->setVisible(false);
		isLeftPressed = true;
	}else if(this->isTouchInside(rightSprite, touch) == true){
		rightSprite->setVisible(false);
		isRightPressed = true;
	}

	if(this->isTouchInside(JumpSprite, touch) == true){
		JumpSprite->setVisible(false);
		isJumpPressed = true;
		if(isJumpPressed == true) //점프 버튼 눌렀을때
		{
			if(sheep->getPosition().y>=400){ //아래로 점프
				if(jumpYN==false){
					jumpYN=true;
					SimpleAudioEngine::sharedEngine()->playEffect("sound/jump.ogg"); //효과음
					CCActionInterval *Jump1=CCJumpBy::create(0.9f,ccp(0,0),-96,1); //속도,위치,높이,점프 횟수(0.9f,ccp(0,0),-96,1);
					CCCallFunc *JumpEndCallback1 = CCCallFunc::create(this, callfunc_selector(Stage01::JumpEnd)); //콜백
					sheep->runAction(CCSequence::create(Jump1,JumpEndCallback1,NULL)); //캐릭터가 점프한다.
				}
			}else if(jumpYN==false){ //위로 점프
				jumpYN=true;
				SimpleAudioEngine::sharedEngine()->playEffect("sound/jump.ogg"); //효과음
				CCActionInterval *Jump2=CCJumpBy::create(0.9f,ccp(0,0),170,1); //속도,위치,높이,점프 횟수(0.9f,ccp(0,0),170,1);
				CCCallFunc *JumpEndCallback2 = CCCallFunc::create(this, callfunc_selector(Stage01::JumpEnd)); //콜백
				sheep->runAction(CCSequence::create(Jump2,JumpEndCallback2,NULL)); //캐릭터가 점프한다.
			}
		}
	}

	// 좌,우 둘중 하나라도 눌리면 배경 움직임
	if(isLeftPressed == true || isRightPressed == true){
		moving=true;
		this->startMovingBackground();
	}else this->stopMovingBackground();

	CCLog("Touche Start");
}

void Stage01::JumpEnd() //콜백 메서드
{
	jumpYN = false;
}

void Stage01::ccTouchesMoved(CCSet *pTouches, CCEvent* event) //터치하면서 이동할때 호출
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	//손가락이 버튼에서 벗어나면 움직임을 중단
	if(isLeftPressed == true && this->isTouchInside(leftSprite, touch) == false){
		leftSprite->setVisible(true);
		//this->stopMovingBackground();
	}else if(isRightPressed == true && this->isTouchInside(rightSprite, touch) == false){
		rightSprite->setVisible(true);
		//this->stopMovingBackground();
	}else if(isJumpPressed == true && this->isTouchInside(JumpSprite, touch) == false){
		JumpSprite->setVisible(true);
	}
}

void Stage01::ccTouchesEnded(CCSet *pTouches,CCEvent *event) //터치 끝내는 순간 호출
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	//왼쪽,오른쪽 하나라도 눌려져 있으면 배경 멈춤
	if(isLeftPressed == true || isRightPressed == true){
		moving=false;
		this->stopMovingBackground();
	}

	//터치끝낼때 버튼 색깔 전환
	if(isLeftPressed == true || this->isTouchInside(JumpSprite, touch) == false){
		leftSprite->setVisible(true);
	}

	if(isRightPressed == true || this->isTouchInside(JumpSprite, touch) == false){
		rightSprite->setVisible(true);
	}

	if(isJumpPressed == true || this->isTouchInside(JumpSprite, touch) == false){
		JumpSprite->setVisible(true);
	}

	CCLog("Touche End");
}

void Stage01::startMovingBackground() //moveBackground 스케쥴
{
	//캐릭터 방향(반전) 설정
	if(isRightPressed == true) //오른쪽을 누르면
		sheep->setFlipX(false); //엑스축 반전 X
	if(isLeftPressed == true) //왼쪽을 누르면
		sheep->setFlipX(true); //엑스축 반전 O

	// 좌 우 동시에 눌려있을시 스케줄안하고 리턴
	if(isLeftPressed == true && isRightPressed == true){
		return;
	}
	//스케줄을 사용해서 매 프레임마다 배경화면을 움직인다.
	this->schedule(schedule_selector(Stage01::moveBackground));
}

void Stage01::stopMovingBackground() //moveBackground 언스케쥴
{
	this->unschedule(schedule_selector(Stage01::moveBackground));
}

void Stage01::moveBackground(float f) //배경화면 움직이는 로직
{
	//스테이지1에 들어있는 패럴렉스 노드 태그1로 정한 차일드를 받는다.
	CCNode *BackgroundNode = this->getChildByTag(1);

	//이동속도 moveStep = ccp(3.5,0.0);
	CCPoint moveStep = ccp(3.5,0.0);

	// 오른쪽 버튼 눌렀을땐 반대로 움직임.
	if(isRightPressed){
		moveStep.x = -moveStep.x;
	}

	//배경 움직임
	CCPoint BackgroundPos = ccp(BackgroundNode->getPosition().x + moveStep.x, BackgroundNode->getPosition().y);

	//배경이 양쪽 끝에 도달하면 더이상 안움직이는 조건문
	if(isLeftPressed == true && BackgroundPos.x > 0){
		BackgroundPos.x = 0;
	}else if(isRightPressed == true && BackgroundPos.x < -(STAGE_WIDTH-winSize.width)){
		BackgroundPos.x = -(STAGE_WIDTH-winSize.width);
		GameFinish();
	}

	//양 움직임을 배경 움직임과 조합
	moveSheep(BackgroundNode, moveStep, BackgroundPos);
}

void Stage01::moveSheep(CCNode* BackgroundNode, const CCPoint& moveStep, const CCPoint& BackgroundPos) //캐릭터 움직임
{
	CCPoint sheepPos = ccp(sheep->getPosition().x+(moveStep.x*-1),sheep->getPosition().y); //양이 배경화면 movestep 에 반대(-1)로 계속해서 움직임

	const float halfWinWidth = winSize.width/2; //스마트폰 스크린 가로길이의 절반

	//캐릭터가 화면의 가운데에 있을 경우에만 배경을 움직인다.
	if(sheep->getPosition().x == halfWinWidth){
		BackgroundNode->setPosition(BackgroundPos);
	}

	//오른쪽 버튼 눌렀고 양의 위치가 화면의 절반 미만 일때
	if(isRightPressed == true && sheep->getPosition().x<halfWinWidth){
		sheep->setPosition(sheepPos);
		if(sheep->getPosition().x>halfWinWidth) //양의 위치가 화면의 절반 초과일때
			sheep->setPosition(ccp(halfWinWidth, sheep->getPosition().y)); //가운데 고정
	}
	//else 왼쪽 버튼 눌렸고 양의 위치가 화변의 절반 초과 일때
	else if(isLeftPressed == true && sheep->getPosition().x>halfWinWidth){
		sheep->setPosition(sheepPos); //양 위치는 배경 이동의 반대로 움직인다.
		if(sheep->getPosition().x<halfWinWidth) //양의 위치가 화면의 절반 미만일때
			sheep->setPosition(ccp(halfWinWidth, sheep->getPosition().y)); //가운데 고정
	}
}

void Stage01::GameFinish()
{
	unscheduleAllSelectors();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, GameFinish::scene()));
}

void Stage01::GameOver()
{
	unscheduleAllSelectors();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, Stage01::scene()));
}

void Stage01::BackButton(){
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
void Stage01::BackTouch(CCObject *sender)
{
	unscheduleAllSelectors();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.0f, MainMenu::scene()));
}

void Stage01::doParticles()
{
	CCParticleSystem *particle01 = CCParticleFlower::create();
	particle01->retain();
	particle01->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle/fire.png"));
	if(particle01 != NULL){
		particle01->setScale(0.5f); //크기
		particle01->setDuration(2.0f); //지속시간
		particle01->setTotalParticles(100);
		particle01->setPosition(sheep->getPosition());
		particle01->setSpeedVar(50); //스피드
		particle01->setAutoRemoveOnFinish(true);
		this->addChild(particle01);
	}
}

void Stage01::doParticles2()
{
	CCParticleSystem *particle02 = CCParticleFireworks::create();
	particle02->retain();
	particle02->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle/stars.png"));
	if(particle02 != NULL){
		particle02->setScale(1.0f); //크기
		particle02->setDuration(2.0f); //지속시간
		particle02->setTotalParticles(200);
		particle02->setPosition(sheep->getPosition());
		particle02->setSpeedVar(50); //스피드
		particle02->setAutoRemoveOnFinish(true);
		this->addChild(particle02);
	}
}

void Stage01::doParticles3()
{
	CCParticleSystem *particle03 = CCParticleExplosion::create();
	particle03->retain();
	particle03->setTexture(CCTextureCache::sharedTextureCache()->addImage("particle/stars.png"));
	if(particle03 != NULL){
		particle03->setScale(1.0f); //크기
		particle03->setDuration(2.0f); //지속시간
		particle03->setTotalParticles(200);
		particle03->setPosition(sheep->getPosition());
		particle03->setSpeedVar(50); //스피드
		particle03->setAutoRemoveOnFinish(true);
		this->addChild(particle03);
	}
}

void Stage01::SheepDead()
{
	sheep->setVisible(false);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/death.ogg", false);
	this->setTouchEnabled(false);
	doParticles();
	unscheduleAllSelectors();
	this->scheduleOnce(schedule_selector(Stage01::GameOver),3.0f);
}

void Stage01::SheepMushDead()
{
	sheep->setVisible(false);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/death.ogg", false);
	SimpleAudioEngine::sharedEngine()->playEffect("sound/teemoLoL.mp3");
	this->setTouchEnabled(false);
	doParticles2();
	unscheduleAllSelectors();
	this->scheduleOnce(schedule_selector(Stage01::GameOver),3.0f);
}

void Stage01::SheepTeemoDead()
{
	sheep->setVisible(false);
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/death.ogg", false);
	SimpleAudioEngine::sharedEngine()->playEffect("sound/crazy.mp3");
	this->setTouchEnabled(false);
	doParticles3();
	unscheduleAllSelectors();
	this->scheduleOnce(schedule_selector(Stage01::GameOver),3.0f);
}

//리버스 중력 정의
void Stage01::gravityReverse()
{
	sheep->setPosition(ccp(sheep->getPosition().x, sheep->getPosition().y +20.0));
}

//리버스 중력 적용
void Stage01::gravityReverseFunc()
{
	sheep->setFlipY(true);
	this->schedule(schedule_selector(Stage01::gravityReverse));
}

//리버스 중력 해제
void Stage01::gravityUnReverseFunc()
{
	sheep->setFlipY(false);
	this->unschedule(schedule_selector(Stage01::gravityReverse));
}

void Stage01::MovingTile()
{
	CCTMXLayer *blocklayer = stageMap->layerNamed("block");
	CCTMXLayer *trap01layer = stageMap->layerNamed("trap01");
	CCTMXLayer *trap02layer = stageMap->layerNamed("trap02");
	CCTMXLayer *trap03layer = stageMap->layerNamed("trap03");

//------------------------------------------ 몬스터 이동 모음 시작-----------------------------------------------------------//
	CCSprite *mob01 = blocklayer->tileAt(ccp(14,7));
	CCTexture2D *texture01 = CCTextureCache::sharedTextureCache()->addImage("tile/set48.png");
	CCAnimation *animation01 = CCAnimation::create();
	animation01->setDelayPerUnit(0.07f);
	for(int i=0;i<10;i++){
		animation01->addSpriteFrameWithTexture(texture01,CCRectMake(246+(i*49),1,48,48));
	}
	CCAnimate *animate01 = CCAnimate::create(animation01);
	CCAction* rep01 = CCRepeatForever::create(animate01);
	mob01->runAction(rep01);

	CCActionInterval *mvMon01 = CCMoveBy::create(2.0f,ccp(200,0));
	CCActionInterval *mvMon01_2 = mvMon01->reverse();
	CCFiniteTimeAction *moving01 = CCSequence::create(mvMon01,CCDelayTime::create(0.3),mvMon01_2,CCDelayTime::create(0.3),NULL);
	CCActionInterval *rep01_1 = (CCActionInterval*)moving01;
	CCAction *rep01_1_1 = CCRepeatForever::create(rep01_1);
	mob01->runAction(rep01_1_1);

	//티모 움직임
	CCSprite *Teemo = blocklayer->tileAt(ccp(170,7));
	CCTexture2D *texture02 = CCTextureCache::sharedTextureCache()->addImage("tile/set48.png");
	CCAnimation *animationTM = CCAnimation::create();
	animationTM->setDelayPerUnit(0.5f);
	for(int i=0;i<3;i++){
		animationTM->addSpriteFrameWithTexture(texture01,CCRectMake(736+(i*36),1,36,48));
	}
	CCAnimate *animationTM2 = CCAnimate::create(animationTM);
	CCAction* animationTM3 = CCRepeatForever::create(animationTM2);
	Teemo->runAction(animationTM3);
	Teemo->setScale(2.0);

	CCActionInterval *mvTM1 = CCMoveBy::create(2.0f,ccp(200,0));
	CCActionInterval *mvTM2 = CCJumpBy::create(0.7f,ccp(100,0),150,1);
	CCActionInterval *mvTM3 = CCMoveBy::create(1.0f,ccp(-300,0));
	CCActionInterval *mvTM4 = CCMoveBy::create(1.0f,ccp(150,0));
	CCActionInterval *mvTM5 = CCJumpBy::create(0.5f,ccp(130,0),100,1);
	CCActionInterval *mvTM6 = CCMoveBy::create(1.0f,ccp(-130,0));
	CCActionInterval *mvTM7 = CCJumpBy::create(1.0f,ccp(-150,0),150,1);
	CCFiniteTimeAction *mvTeeMo = CCSequence::create(mvTM1,
													 mvTM2,CCDelayTime::create(0.3),
													 mvTM3,CCDelayTime::create(0.3),
													 mvTM4,
													 mvTM5,CCDelayTime::create(0.3),
													 mvTM6,
													 mvTM7,CCDelayTime::create(0.3),NULL);

	CCActionInterval *mvTMALL = (CCActionInterval*)mvTeeMo;
	CCAction *mvTMRUN = CCRepeatForever::create(mvTMALL);
	Teemo->runAction(mvTMRUN);
	//티모 움직임 끝
//------------------------------------------ 몬스터 이동 모음   끝-----------------------------------------------------------//

//------------------------------------------ 블럭 이동 모음 시작-----------------------------------------------------------//
	CCSprite *block01 = blocklayer->tileAt(ccp(22,8));
	CCActionInterval *moveBlock01 = CCMoveBy::create(3.0f,ccp(340,0));
	CCActionInterval *moveBlock01Back = moveBlock01->reverse();
	CCFiniteTimeAction *moving01_2 = CCSequence::create(moveBlock01, moveBlock01Back, NULL);
	CCActionInterval *rep01_2 = (CCActionInterval*)moving01_2;
	CCAction *rep01_3 = CCRepeatForever::create(rep01_2);
	block01->runAction(rep01_3);

	CCSprite *block06 = blocklayer->tileAt(ccp(74,8));
	CCActionInterval *moveBlock02 = CCMoveBy::create(2.5f,ccp(190,0));
	CCActionInterval *moveBlock02Back = moveBlock02->reverse();
	CCFiniteTimeAction *moving02 = CCSequence::create(moveBlock02, moveBlock02Back, NULL);
	CCActionInterval *rep02 = (CCActionInterval*)moving02;
	CCAction *rep02_2 = CCRepeatForever::create(rep02);
	block06->runAction(rep02_2);

	CCSprite *block07 = blocklayer->tileAt(ccp(75,8));
	CCActionInterval *moveBlock03 = CCMoveBy::create(2.5f,ccp(190,0));
	CCActionInterval *moveBlock03Back = moveBlock03->reverse();
	CCFiniteTimeAction *moving03 = CCSequence::create(moveBlock03, moveBlock03Back, NULL);
	CCActionInterval *rep03 = (CCActionInterval*)moving03;
	CCAction *rep03_2 = CCRepeatForever::create(rep03);
	block07->runAction(rep03_2);

	CCSprite *block08 = blocklayer->tileAt(ccp(85,8));
	CCActionInterval *moveBlock04 = CCMoveBy::create(1.9f,ccp(-190,0));
	CCActionInterval *moveBlock04Back = moveBlock04->reverse();
	CCFiniteTimeAction *moving04 = CCSequence::create(moveBlock04, moveBlock04Back, NULL);
	CCActionInterval *rep04 = (CCActionInterval*)moving04;
	CCAction *rep04_2 = CCRepeatForever::create(rep04);
	block08->runAction(rep04_2);

	CCSprite *block09 = blocklayer->tileAt(ccp(86,8));
	CCActionInterval *moveBlock05 = CCMoveBy::create(1.9f,ccp(-190,0));
	CCActionInterval *moveBlock05Back = moveBlock05->reverse();
	CCFiniteTimeAction *moving05 = CCSequence::create(moveBlock05, moveBlock05Back, NULL);
	CCActionInterval *rep05 = (CCActionInterval*)moving05;
	CCAction *rep05_2 = CCRepeatForever::create(rep05);
	block09->runAction(rep05_2);

	CCSprite *block10 = blocklayer->tileAt(ccp(88,8));
	CCActionInterval *moveBlock06 = CCMoveBy::create(1.3f,ccp(190,0));
	CCActionInterval *moveBlock06Back = moveBlock06->reverse();
	CCFiniteTimeAction *moving06 = CCSequence::create(moveBlock06, moveBlock06Back, NULL);
	CCActionInterval *rep06 = (CCActionInterval*)moving06;
	CCAction *rep06_2 = CCRepeatForever::create(rep06);
	block10->runAction(rep06_2);

	CCSprite *block11 = blocklayer->tileAt(ccp(89,8));
	CCActionInterval *moveBlock07 = CCMoveBy::create(1.3f,ccp(190,0));
	CCActionInterval *moveBlock07Back = moveBlock07->reverse();
	CCFiniteTimeAction *moving07 = CCSequence::create(moveBlock07, moveBlock07Back, NULL);
	CCActionInterval *rep07 = (CCActionInterval*)moving07;
	CCAction *rep07_2 = CCRepeatForever::create(rep07);
	block11->runAction(rep07_2);

	CCSprite *block12 = blocklayer->tileAt(ccp(130,0));
	CCActionInterval *moveBlock08 = CCMoveBy::create(2.0f,ccp(238,0));
	CCActionInterval *moveBlock08Back = moveBlock08->reverse();
	CCFiniteTimeAction *moving08 = CCSequence::create(moveBlock08, moveBlock08Back, NULL);
	CCActionInterval *rep08 = (CCActionInterval*)moving08;
	CCAction *rep08_2 = CCRepeatForever::create(rep08);
	block12->runAction(rep08_2);

	CCSprite *block13 = blocklayer->tileAt(ccp(131,0));
	CCActionInterval *moveBlock09 = CCMoveBy::create(2.0f,ccp(238,0));
	CCActionInterval *moveBlock09Back = moveBlock09->reverse();
	CCFiniteTimeAction *moving09 = CCSequence::create(moveBlock09, moveBlock09Back, NULL);
	CCActionInterval *rep09 = (CCActionInterval*)moving09;
	CCAction *rep09_2 = CCRepeatForever::create(rep09);
	block13->runAction(rep09_2);

	CCSprite *block14 = blocklayer->tileAt(ccp(138,0));
	CCActionInterval *moveBlock10 = CCMoveBy::create(1.6f,ccp(238,0));
	CCActionInterval *moveBlock10Back = moveBlock10->reverse();
	CCFiniteTimeAction *moving10 = CCSequence::create(moveBlock10, moveBlock10Back, NULL);
	CCActionInterval *rep10 = (CCActionInterval*)moving10;
	CCAction *rep10_2 = CCRepeatForever::create(rep10);
	block14->runAction(rep10_2);

	CCSprite *block15 = blocklayer->tileAt(ccp(139,0));
	CCActionInterval *moveBlock11 = CCMoveBy::create(1.6f,ccp(238,0));
	CCActionInterval *moveBlock11Back = moveBlock11->reverse();
	CCFiniteTimeAction *moving11 = CCSequence::create(moveBlock11, moveBlock11Back, NULL);
	CCActionInterval *rep11 = (CCActionInterval*)moving11;
	CCAction *rep11_2 = CCRepeatForever::create(rep11);
	block15->runAction(rep11_2);


//------------------------------------------ 블럭 이동 모음 끝-----------------------------------------------------------//

//------------------------------------------ 투명 함정 0 시작-----------------------------------------------------------//
	CCSprite *trapTT1 = blocklayer->tileAt(ccp(36,7));	trapTT1->setVisible(false);
	CCSprite *trapTT2 = blocklayer->tileAt(ccp(39,7));	trapTT2->setVisible(false);
	CCSprite *trapTT3 = blocklayer->tileAt(ccp(42,7));	trapTT3->setVisible(false);
	CCSprite *trapTT4 = blocklayer->tileAt(ccp(45,7));	trapTT4->setVisible(false);

	CCSprite *blockHD1 = blocklayer->tileAt(ccp(36,8)); blockHD1->setVisible(false);
	CCSprite *blockHD2 = blocklayer->tileAt(ccp(37,8)); blockHD2->setVisible(false);
	CCSprite *blockHD3 = blocklayer->tileAt(ccp(38,8)); blockHD3->setVisible(false);
	CCSprite *blockHD4 = blocklayer->tileAt(ccp(39,8)); blockHD4->setVisible(false);
	CCSprite *blockHD5 = blocklayer->tileAt(ccp(40,8)); blockHD5->setVisible(false);
	CCSprite *blockHD6 = blocklayer->tileAt(ccp(41,8)); blockHD6->setVisible(false);
	CCSprite *blockHD7 = blocklayer->tileAt(ccp(42,8)); blockHD7->setVisible(false);
	CCSprite *blockHD8 = blocklayer->tileAt(ccp(43,8)); blockHD8->setVisible(false);
	CCSprite *blockHD9 = blocklayer->tileAt(ccp(44,8)); blockHD9->setVisible(false);
	CCSprite *blockHD10 = blocklayer->tileAt(ccp(45,8)); blockHD10->setVisible(false);
//------------------------------------------ 투명 함정 0 시작-----------------------------------------------------------//

//------------------------------------------ 투명 함정 1 시작-----------------------------------------------------------//
	CCSprite *tile54_0 = blocklayer->tileAt(ccp(54,9)); tile54_0->setVisible(false);
	CCSprite *tile55_0 = blocklayer->tileAt(ccp(55,9)); tile55_0->setVisible(false);
	CCSprite *tile56_0 = blocklayer->tileAt(ccp(56,9)); tile56_0->setVisible(false);
	CCSprite *tile57_0 = blocklayer->tileAt(ccp(57,9)); tile57_0->setVisible(false);
	CCSprite *tile58_0 = blocklayer->tileAt(ccp(58,9)); tile58_0->setVisible(false);
	CCSprite *tile59_0 = blocklayer->tileAt(ccp(59,9)); tile59_0->setVisible(false);
	CCSprite *tile60_0 = blocklayer->tileAt(ccp(60,9)); tile60_0->setVisible(false);

	CCSprite *tile54 = blocklayer->tileAt(ccp(54,8)); tile54->setVisible(false);
	CCSprite *tile55 = blocklayer->tileAt(ccp(55,8)); tile55->setVisible(false);
	CCSprite *tile56 = blocklayer->tileAt(ccp(56,8)); tile56->setVisible(false);
	CCSprite *tile57 = blocklayer->tileAt(ccp(57,8)); tile57->setVisible(false);
	CCSprite *tile58 = blocklayer->tileAt(ccp(58,8)); tile58->setVisible(false);
	CCSprite *tile59 = blocklayer->tileAt(ccp(59,8)); tile59->setVisible(false);
	CCSprite *tile60 = blocklayer->tileAt(ccp(60,8)); tile60->setVisible(false);

	//불꽃 나열 회전1 시작
	CCSprite *tileT1 = trap01layer->tileAt(ccp(98,5));
	tileT1->setAnchorPoint(ccp(-0.25,-0.25));
	tileT1->setPosition(ccp(tileT1->getPositionX()+24,tileT1->getPositionY()+72));
	CCActionInterval* rotateT01 = CCRotateBy::create(3,360);
	CCAction *rotateT_F01 = CCRepeatForever::create(rotateT01);
	tileT1->runAction(rotateT_F01);

	CCSprite *tileT2 = trap02layer->tileAt(ccp(98,5));
	tileT2->setAnchorPoint(ccp(-1.0,-1.0));
	tileT2->setPosition(ccp(tileT2->getPositionX()+24,tileT2->getPositionY()+72));
	CCActionInterval* rotateT02 = CCRotateBy::create(3,360);
	CCAction *rotateT_F02 = CCRepeatForever::create(rotateT02);
	tileT2->runAction(rotateT_F02);

	CCSprite *tileT3 = trap03layer->tileAt(ccp(98,5));
	tileT3->setAnchorPoint(ccp(-1.75,-1.75));
	tileT3->setPosition(ccp(tileT3->getPositionX()+24,tileT3->getPositionY()+72));
	CCActionInterval* rotateT03 = CCRotateBy::create(3,360);
	CCAction *rotateT_F03 = CCRepeatForever::create(rotateT03);
	tileT3->runAction(rotateT_F03);
	//불꽃 나열 회전1 끝

	//불꽃 나열 회전2 시작
	CCSprite *tileT4 = trap01layer->tileAt(ccp(105,5));
	tileT4->setAnchorPoint(ccp(-0.25,-0.25));
	tileT4->setPosition(ccp(tileT4->getPositionX()+24,tileT4->getPositionY()+72));
	CCActionInterval* rotateT04 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_F04 = CCRepeatForever::create(rotateT04);
	tileT4->runAction(rotateT_F04);

	CCSprite *tileT5 = trap02layer->tileAt(ccp(105,5));
	tileT5->setAnchorPoint(ccp(-1.0,-1.0));
	tileT5->setPosition(ccp(tileT5->getPositionX()+24,tileT5->getPositionY()+72));
	CCActionInterval* rotateT05 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_F05 = CCRepeatForever::create(rotateT05);
	tileT5->runAction(rotateT_F05);

	CCSprite *tileT6 = trap03layer->tileAt(ccp(105,5));
	tileT6->setAnchorPoint(ccp(-1.75,-1.75));
	tileT6->setPosition(ccp(tileT6->getPositionX()+24,tileT6->getPositionY()+72));
	CCActionInterval* rotateT06 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_F06 = CCRepeatForever::create(rotateT06);
	tileT6->runAction(rotateT_F06);
	//불꽃 나열 회전2 끝

	//불꽃 나열 회전3 시작
	CCSprite *FireRot1 = blocklayer->tileAt(ccp(137,6));
	FireRot1->setAnchorPoint(ccp(0.5,0.5));
	FireRot1->setPosition(ccp(FireRot1->getPositionX()+24,FireRot1->getPositionY()+72));
	CCActionInterval* rotateR01 = CCRotateBy::create(3,360);
	CCAction *rotateT_R01 = CCRepeatForever::create(rotateR01);
	FireRot1->runAction(rotateT_R01);

	CCSprite *FireRot2 = trap01layer->tileAt(ccp(137,6));
	FireRot2->setAnchorPoint(ccp(-0.25,-0.25));
	FireRot2->setPosition(ccp(FireRot2->getPositionX()+24,FireRot2->getPositionY()+72));
	CCActionInterval* rotateR02 = CCRotateBy::create(3,360);
	CCAction *rotateT_R02 = CCRepeatForever::create(rotateR02);
	FireRot2->runAction(rotateT_R02);

	CCSprite *FireRot3 = trap02layer->tileAt(ccp(137,6));
	FireRot3->setAnchorPoint(ccp(-1.0,-1.0));
	FireRot3->setPosition(ccp(FireRot3->getPositionX()+24,FireRot3->getPositionY()+72));
	CCActionInterval* rotateR03 = CCRotateBy::create(3,360);
	CCAction *rotateT_R03 = CCRepeatForever::create(rotateR03);
	FireRot3->runAction(rotateT_R03);

	CCSprite *FireRot4 = trap03layer->tileAt(ccp(137,6));
	FireRot4->setAnchorPoint(ccp(-1.75,-1.75));
	FireRot4->setPosition(ccp(FireRot4->getPositionX()+24,FireRot4->getPositionY()+72));
	CCActionInterval* rotateR04 = CCRotateBy::create(3,360);
	CCAction *rotateT_R04 = CCRepeatForever::create(rotateR04);
	FireRot4->runAction(rotateT_R04);
	//불꽃 나열 회전3 끝

	//불꽃 나열 회전4 시작
	CCSprite *FireRot5 = blocklayer->tileAt(ccp(156,5));
	FireRot5->setAnchorPoint(ccp(0.5,0.5));
	FireRot5->setPosition(ccp(FireRot5->getPositionX()+24,FireRot5->getPositionY()+72));
	CCActionInterval* rotateR05 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_R05 = CCRepeatForever::create(rotateR05);
	FireRot5->runAction(rotateT_R05);

	CCSprite *FireRot6 = trap01layer->tileAt(ccp(156,5));
	FireRot6->setAnchorPoint(ccp(-0.25,-0.25));
	FireRot6->setPosition(ccp(FireRot6->getPositionX()+24,FireRot6->getPositionY()+72));
	CCActionInterval* rotateR06 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_R06 = CCRepeatForever::create(rotateR06);
	FireRot6->runAction(rotateT_R06);

	CCSprite *FireRot7 = trap02layer->tileAt(ccp(156,5));
	FireRot7->setAnchorPoint(ccp(-1.0,-1.0));
	FireRot7->setPosition(ccp(FireRot7->getPositionX()+24,FireRot7->getPositionY()+72));
	CCActionInterval* rotateR07 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_R07 = CCRepeatForever::create(rotateR07);
	FireRot7->runAction(rotateT_R07);

	CCSprite *FireRot8 = trap03layer->tileAt(ccp(156,5));
	FireRot8->setAnchorPoint(ccp(-1.75,-1.75));
	FireRot8->setPosition(ccp(FireRot8->getPositionX()+24,FireRot8->getPositionY()+72));
	CCActionInterval* rotateR08 = CCRotateBy::create(1.5,-360);
	CCAction *rotateT_R08 = CCRepeatForever::create(rotateR08);
	FireRot8->runAction(rotateT_R08);
	//불꽃 나열 회전4 끝

	//불꽃 제자리 회전 시작
	CCSprite *tile54_1 = blocklayer->tileAt(ccp(54,5)); tile54_1->setVisible(false);
	tile54_1->setAnchorPoint(ccp(0.5,0.5));
	tile54_1->setPosition(ccp(tile54_1->getPositionX()+24,tile54_1->getPositionY()+24));
	CCActionInterval* rotate01 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F01 = CCRepeatForever::create(rotate01);
	tile54_1->runAction(rotate_F01);

	CCSprite *tile55_1 = blocklayer->tileAt(ccp(55,4)); tile55_1->setVisible(false);
	tile55_1->setAnchorPoint(ccp(0.5,0.5));
	tile55_1->setPosition(ccp(tile55_1->getPositionX()+24,tile55_1->getPositionY()+24));
	CCActionInterval* rotate02 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F02 = CCRepeatForever::create(rotate02);
	tile55_1->runAction(rotate_F02);

	CCSprite *tile59_1 = blocklayer->tileAt(ccp(59,4)); tile59_1->setVisible(false);
	tile59_1->setAnchorPoint(ccp(0.5,0.5));
	tile59_1->setPosition(ccp(tile59_1->getPositionX()+24,tile59_1->getPositionY()+24));
	CCActionInterval* rotate03 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F03 = CCRepeatForever::create(rotate03);
	tile59_1->runAction(rotate_F03);

	CCSprite *tile60_1 = blocklayer->tileAt(ccp(60,5)); tile60_1->setVisible(false);
	tile60_1->setAnchorPoint(ccp(0.5,0.5));
	tile60_1->setPosition(ccp(tile60_1->getPositionX()+24,tile60_1->getPositionY()+24));
	CCActionInterval* rotate04 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F04 = CCRepeatForever::create(rotate04);
	tile60_1->runAction(rotate_F04);

	CCSprite *trap04 = blocklayer->tileAt(ccp(57,6)); trap04->setVisible(false);
	trap04->setAnchorPoint(ccp(0.5,0.5));
	trap04->setPosition(ccp(trap04->getPositionX()+24,trap04->getPositionY()+24));
	CCActionInterval* rotate05 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F05 = CCRepeatForever::create(rotate05);
	trap04->runAction(rotate_F05);

	CCSprite *trap05 = blocklayer->tileAt(ccp(80,9));
	trap05->setAnchorPoint(ccp(0.5,0.5));
	trap05->setPosition(ccp(trap05->getPositionX()+24,trap05->getPositionY()+24));
	CCActionInterval* rotate06 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F06 = CCRepeatForever::create(rotate06);
	trap05->runAction(rotate_F06);

	CCSprite *trap06 = blocklayer->tileAt(ccp(87,9));
	trap06->setAnchorPoint(ccp(0.5,0.5));
	trap06->setPosition(ccp(trap06->getPositionX()+24,trap06->getPositionY()+24));
	CCActionInterval* rotate07 = CCRotateBy::create(0.4,360);
	CCAction *rotate_F07 = CCRepeatForever::create(rotate07);
	trap06->runAction(rotate_F07);
	//불꽃 제자리 회전 끝

	CCSprite *trap03 = blocklayer->tileAt(ccp(57,7)); trap03->setVisible(false);
//------------------------------------------ 투명 함정 1 끝-----------------------------------------------------------//
	//버섯시작
	CCSprite *mush01 = blocklayer->tileAt(ccp(164,7));
	mush01->setVisible(false);

	CCSprite *mush02 = blocklayer->tileAt(ccp(177,7));
	mush02->setVisible(false);


	CCSprite *mush03 = blocklayer->tileAt(ccp(181,7));
	mush03->setVisible(false);

	CCSprite *mush04 = blocklayer->tileAt(ccp(186,7));
	mush04->setVisible(false);
	//버섯끗

}

//블럭과의 충돌구현
void Stage01::collisionCheck()
{
	CCTMXLayer *blocklayer = stageMap->layerNamed("block");
	CCTMXLayer *maplayer = stageMap->layerNamed("map");
	CCTMXLayer *trap01layer = stageMap->layerNamed("trap01");
	CCTMXLayer *trap02layer = stageMap->layerNamed("trap02");
	CCTMXLayer *trap03layer = stageMap->layerNamed("trap03");

	//양 충돌범위 좀 줄임
	CCRect sheepR = sheepRect->boundingBox();
	sheepR.origin.x = sheepR.origin.x + 10;
	sheepR.origin.y = sheepR.origin.y + 20;
	sheepR.size.width = sheepR.size.width - 20;
	sheepR.size.height = sheepR.size.height - 40;

//------------------------------------------ 함정 시작-----------------------------------------------------------//
	//일반 함정 시작
	CCSprite *trap01 = blocklayer->tileAt(ccp(32,7));	if(sheepR.intersectsRect(trap01->boundingBox())) SheepDead();
	CCSprite *trap02 = blocklayer->tileAt(ccp(33,7));	if(sheepR.intersectsRect(trap02->boundingBox())) SheepDead();
	CCSprite *trap03 = blocklayer->tileAt(ccp(57,7));	if(sheepR.intersectsRect(trap03->boundingBox())) SheepDead();
	CCSprite *trap04 = blocklayer->tileAt(ccp(57,6));
	if(sheepR.intersectsRect(trap04->boundingBox())){
		trap04->setVisible(true);
		SheepDead();
	}

	CCSprite *trap05 = blocklayer->tileAt(ccp(80,8));	if(sheepR.intersectsRect(trap05->boundingBox())) SheepDead();
	CCSprite *trap06 = blocklayer->tileAt(ccp(80,9));	if(sheepR.intersectsRect(trap06->boundingBox())) SheepDead();
	CCSprite *trap07 = blocklayer->tileAt(ccp(87,8));	if(sheepR.intersectsRect(trap07->boundingBox())) SheepDead();
	CCSprite *trap08 = blocklayer->tileAt(ccp(87,9));	if(sheepR.intersectsRect(trap08->boundingBox())) SheepDead();

	CCSprite *trap150 = blocklayer->tileAt(ccp(150,8));	if(sheepR.intersectsRect(trap150->boundingBox())) SheepDead();
	CCSprite *trap151 = blocklayer->tileAt(ccp(151,8));	if(sheepR.intersectsRect(trap151->boundingBox())) SheepDead();
	CCSprite *trap152 = blocklayer->tileAt(ccp(152,8));	if(sheepR.intersectsRect(trap152->boundingBox())) SheepDead();
	//일반 함정 끝

	//불꽃 나열 회전 테스트 시작!
	CCSprite *tileT1 = trap01layer->tileAt(ccp(98,5));	if(sheepR.intersectsRect(tileT1->boundingBox())) SheepDead();
	CCSprite *tileT2 = trap02layer->tileAt(ccp(98,5));	if(sheepR.intersectsRect(tileT2->boundingBox())) SheepDead();
	CCSprite *tileT3 = trap03layer->tileAt(ccp(98,5));	if(sheepR.intersectsRect(tileT3->boundingBox())) SheepDead();
	CCSprite *tileT4 = trap01layer->tileAt(ccp(105,5)); if(sheepR.intersectsRect(tileT4->boundingBox())) SheepDead();
	CCSprite *tileT5 = trap02layer->tileAt(ccp(105,5));	if(sheepR.intersectsRect(tileT5->boundingBox())) SheepDead();
	CCSprite *tileT6 = trap03layer->tileAt(ccp(105,5));	if(sheepR.intersectsRect(tileT6->boundingBox())) SheepDead();

	CCSprite *tileF1 = blocklayer->tileAt(ccp(98,4)); if(sheepR.intersectsRect(tileF1->boundingBox())) SheepDead();
	CCSprite *tileF2 = blocklayer->tileAt(ccp(105,4)); if(sheepR.intersectsRect(tileF2->boundingBox()))	SheepDead();

	CCSprite *FireRot1 = blocklayer->tileAt(ccp(137,6)); if(sheepR.intersectsRect(FireRot1->boundingBox())) SheepDead();
	CCSprite *FireRot2 = trap01layer->tileAt(ccp(137,6)); if(sheepR.intersectsRect(FireRot2->boundingBox())) SheepDead();
	CCSprite *FireRot3 = trap02layer->tileAt(ccp(137,6)); if(sheepR.intersectsRect(FireRot3->boundingBox())) SheepDead();
	CCSprite *FireRot4 = trap03layer->tileAt(ccp(137,6)); if(sheepR.intersectsRect(FireRot4->boundingBox())) SheepDead();

	CCSprite *FireRot5 = trap03layer->tileAt(ccp(156,5)); if(sheepR.intersectsRect(FireRot5->boundingBox())) SheepDead();
	CCSprite *FireRot6 = trap03layer->tileAt(ccp(156,5)); if(sheepR.intersectsRect(FireRot6->boundingBox())) SheepDead();
	CCSprite *FireRot7 = trap03layer->tileAt(ccp(156,5)); if(sheepR.intersectsRect(FireRot7->boundingBox())) SheepDead();
	CCSprite *FireRot8 = trap03layer->tileAt(ccp(156,5)); if(sheepR.intersectsRect(FireRot8->boundingBox())) SheepDead();
	//불꽃 나열 회전 테스트 끝!

	//공중 함정 시작
	CCSprite *trapU04 = blocklayer->tileAt(ccp(117,1));	if(sheepR.intersectsRect(trapU04->boundingBox())) SheepDead();
	CCSprite *trapU05 = blocklayer->tileAt(ccp(118,1));	if(sheepR.intersectsRect(trapU05->boundingBox())) SheepDead();
	CCSprite *trapU06 = blocklayer->tileAt(ccp(121,1));	if(sheepR.intersectsRect(trapU06->boundingBox())) SheepDead();
	CCSprite *trapU07 = blocklayer->tileAt(ccp(122,1));	if(sheepR.intersectsRect(trapU07->boundingBox())) SheepDead();
	CCSprite *trapU08 = blocklayer->tileAt(ccp(125,1));	if(sheepR.intersectsRect(trapU08->boundingBox())) SheepDead();
	CCSprite *trapU09 = blocklayer->tileAt(ccp(126,1));	if(sheepR.intersectsRect(trapU09->boundingBox())) SheepDead();

	CCSprite *trapU10 = blocklayer->tileAt(ccp(137,0));	if(sheepR.intersectsRect(trapU10->boundingBox())) SheepDead();

	CCSprite *trapU11 = blocklayer->tileAt(ccp(147,1));	if(sheepR.intersectsRect(trapU11->boundingBox())) SheepDead();
	CCSprite *trapU12 = blocklayer->tileAt(ccp(148,1));	if(sheepR.intersectsRect(trapU12->boundingBox())) SheepDead();
	//공중 함정 끝
//-------------------------------------------- 함정 끝-----------------------------------------------------------//
//------------------------------------------ 스프링 시작-----------------------------------------------------------//
	CCSprite *spring01 = blocklayer->tileAt(ccp(113,7));
	if(sheepR.intersectsRect(spring01->boundingBox())){
		sheep->setPositionY(150);
		SimpleAudioEngine::sharedEngine()->playEffect("sound/reverse.mp3"); //효과음
		gravityReverseFunc();
	}

	CCSprite *spring07 = blocklayer->tileAt(ccp(154,1));
	if(sheepR.intersectsRect(spring07->boundingBox())){
		sheep->setPositionY(380);
		SimpleAudioEngine::sharedEngine()->playEffect("sound/reverse.mp3"); //효과음
		gravityUnReverseFunc();
	}
//------------------------------------------ 스프링   끝-----------------------------------------------------------//
//------------------------------------------ 몬스터 시작-----------------------------------------------------------//
	CCSprite *mob01 = blocklayer->tileAt(ccp(14,7));
	if(sheepR.intersectsRect(mob01->boundingBox())){
		SheepDead();
	}
//------------------------------------------ 몬스터   끝-----------------------------------------------------------//
//------------------------------------------ 블럭 시작-----------------------------------------------------------//
	CCSprite *block01 = blocklayer->tileAt(ccp(22,8));
	if(sheepRect->boundingBox().intersectsRect(block01->boundingBox()))	sheep->setPositionY(block01->getPosition().y+77);

	//투명 함정(HiDe) 0 시작
	CCSprite *blockHD1 = blocklayer->tileAt(ccp(36,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD1->boundingBox())){
		blockHD1->setVisible(true);
		sheep->setPositionY(blockHD1->getPosition().y+77);
	}
	CCSprite *blockHD2 = blocklayer->tileAt(ccp(37,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD2->boundingBox())){
		blockHD2->setVisible(true);
		sheep->setPositionY(blockHD2->getPosition().y+77);
	}
	CCSprite *blockHD3 = blocklayer->tileAt(ccp(38,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD3->boundingBox())){
		blockHD3->setVisible(true);
		sheep->setPositionY(blockHD3->getPosition().y+77);
	}
	CCSprite *blockHD4 = blocklayer->tileAt(ccp(39,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD4->boundingBox())){
		blockHD4->setVisible(true);
		sheep->setPositionY(blockHD4->getPosition().y+77);
	}
	CCSprite *blockHD5 = blocklayer->tileAt(ccp(40,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD5->boundingBox())){
		blockHD5->setVisible(true);
		sheep->setPositionY(blockHD5->getPosition().y+77);
	}
	CCSprite *blockHD6 = blocklayer->tileAt(ccp(41,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD6->boundingBox())){
		blockHD6->setVisible(true);
		sheep->setPositionY(blockHD6->getPosition().y+77);
	}
	CCSprite *blockHD7 = blocklayer->tileAt(ccp(42,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD7->boundingBox())){
		blockHD7->setVisible(true);
		sheep->setPositionY(blockHD7->getPosition().y+77);
	}
	CCSprite *blockHD8 = blocklayer->tileAt(ccp(43,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD8->boundingBox())){
		blockHD8->setVisible(true);
		sheep->setPositionY(blockHD8->getPosition().y+77);
	}
	CCSprite *blockHD9 = blocklayer->tileAt(ccp(44,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD9->boundingBox())){
		blockHD9->setVisible(true);
		sheep->setPositionY(blockHD9->getPosition().y+77);
	}
	CCSprite *blockHD10 = blocklayer->tileAt(ccp(45,8));
	if(sheepRect->boundingBox().intersectsRect(blockHD10->boundingBox())){
		blockHD10->setVisible(true);
		sheep->setPositionY(blockHD10->getPosition().y+77);
	}
	CCSprite *trapTT1 = blocklayer->tileAt(ccp(36,7));
	if(sheepR.intersectsRect(trapTT1->boundingBox())){
		trapTT1->setVisible(true);
		blockHD1->setVisible(true);
		SheepDead();
	}
	CCSprite *trapTT2 = blocklayer->tileAt(ccp(39,7));
	if(sheepR.intersectsRect(trapTT2->boundingBox())){
		trapTT2->setVisible(true);
		blockHD4->setVisible(true);
		SheepDead();
	}
	CCSprite *trapTT3 = blocklayer->tileAt(ccp(42,7));
	if(sheepR.intersectsRect(trapTT3->boundingBox())){
		trapTT3->setVisible(true);
		blockHD7->setVisible(true);
		SheepDead();
	}
	CCSprite *trapTT4 = blocklayer->tileAt(ccp(45,7));
	if(sheepR.intersectsRect(trapTT4->boundingBox())){
		trapTT4->setVisible(true);
		blockHD10->setVisible(true);
		SheepDead();
	}
	//투명 함정 0 끝

	CCSprite *block06 = blocklayer->tileAt(ccp(74,8));
	if(sheepRect->boundingBox().intersectsRect(block06->boundingBox()))	sheep->setPositionY(block06->getPosition().y+77);
	CCSprite *block07 = blocklayer->tileAt(ccp(75,8));
	if(sheepRect->boundingBox().intersectsRect(block07->boundingBox()))	sheep->setPositionY(block07->getPosition().y+77);
	CCSprite *block08 = blocklayer->tileAt(ccp(85,8));
	if(sheepRect->boundingBox().intersectsRect(block08->boundingBox()))	sheep->setPositionY(block08->getPosition().y+77);
	CCSprite *block09 = blocklayer->tileAt(ccp(86,8));
	if(sheepRect->boundingBox().intersectsRect(block09->boundingBox()))	sheep->setPositionY(block09->getPosition().y+77);
	CCSprite *block10 = blocklayer->tileAt(ccp(88,8));
	if(sheepRect->boundingBox().intersectsRect(block10->boundingBox()))	sheep->setPositionY(block10->getPosition().y+77);
	CCSprite *block11 = blocklayer->tileAt(ccp(89,8));
	if(sheepRect->boundingBox().intersectsRect(block11->boundingBox()))	sheep->setPositionY(block11->getPosition().y+77);

	//리버스 움직이는 블록//
	CCSprite *block12 = blocklayer->tileAt(ccp(130,0));
	if(sheepRect->boundingBox().intersectsRect(block12->boundingBox()))	sheep->setPositionY(block12->getPosition().y-38);
	CCSprite *block13 = blocklayer->tileAt(ccp(131,0));
	if(sheepRect->boundingBox().intersectsRect(block13->boundingBox()))	sheep->setPositionY(block13->getPosition().y-38);
	CCSprite *block14 = blocklayer->tileAt(ccp(138,0));
	if(sheepRect->boundingBox().intersectsRect(block14->boundingBox()))	sheep->setPositionY(block14->getPosition().y-38);
	CCSprite *block15 = blocklayer->tileAt(ccp(139,0));
	if(sheepRect->boundingBox().intersectsRect(block15->boundingBox()))	sheep->setPositionY(block15->getPosition().y-38);
	//리버스 움직이는 블록//

//------------------------------------------ 블럭 끝-----------------------------------------------------------//

//------------------------------------------ 타일 시작-----------------------------------------------------------//
	CCSprite *tile08 = maplayer->tileAt(ccp(8,8));
	if(sheepRect->boundingBox().intersectsRect(tile08->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile09 = maplayer->tileAt(ccp(9,8));
	if(sheepRect->boundingBox().intersectsRect(tile09->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile10 = maplayer->tileAt(ccp(10,8));
	if(sheepRect->boundingBox().intersectsRect(tile10->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile11 = maplayer->tileAt(ccp(11,8));
	if(sheepRect->boundingBox().intersectsRect(tile11->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile12 = maplayer->tileAt(ccp(12,8));
	if(sheepRect->boundingBox().intersectsRect(tile12->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile13 = maplayer->tileAt(ccp(13,8));
	if(sheepRect->boundingBox().intersectsRect(tile13->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile14 = maplayer->tileAt(ccp(14,8));
	if(sheepRect->boundingBox().intersectsRect(tile14->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile15 = maplayer->tileAt(ccp(15,8));
	if(sheepRect->boundingBox().intersectsRect(tile15->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile16 = maplayer->tileAt(ccp(16,8));
	if(sheepRect->boundingBox().intersectsRect(tile16->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile17 = maplayer->tileAt(ccp(17,8));
	if(sheepRect->boundingBox().intersectsRect(tile17->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile18 = maplayer->tileAt(ccp(18,8));
	if(sheepRect->boundingBox().intersectsRect(tile18->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile19 = maplayer->tileAt(ccp(19,8));
	if(sheepRect->boundingBox().intersectsRect(tile19->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile20 = maplayer->tileAt(ccp(20,8));
	if(sheepRect->boundingBox().intersectsRect(tile20->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile21 = maplayer->tileAt(ccp(21,8));
	if(sheepRect->boundingBox().intersectsRect(tile21->boundingBox()))	sheep->setPositionY(125);

	CCSprite *tile30 = maplayer->tileAt(ccp(30,8));
	if(sheepRect->boundingBox().intersectsRect(tile30->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile31 = maplayer->tileAt(ccp(31,8));
	if(sheepRect->boundingBox().intersectsRect(tile31->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile32 = maplayer->tileAt(ccp(32,8));
	if(sheepRect->boundingBox().intersectsRect(tile32->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile33 = maplayer->tileAt(ccp(33,8));
	if(sheepRect->boundingBox().intersectsRect(tile33->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile34 = maplayer->tileAt(ccp(34,8));
	if(sheepRect->boundingBox().intersectsRect(tile34->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile35 = maplayer->tileAt(ccp(35,8));
	if(sheepRect->boundingBox().intersectsRect(tile35->boundingBox()))	sheep->setPositionY(125);

	CCSprite *tile46 = maplayer->tileAt(ccp(46,8));
	if(sheepRect->boundingBox().intersectsRect(tile46->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile47 = maplayer->tileAt(ccp(47,8));
	if(sheepRect->boundingBox().intersectsRect(tile47->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile48 = maplayer->tileAt(ccp(48,8));
	if(sheepRect->boundingBox().intersectsRect(tile48->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile49 = maplayer->tileAt(ccp(49,8));
	if(sheepRect->boundingBox().intersectsRect(tile49->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile50 = maplayer->tileAt(ccp(50,8));
	if(sheepRect->boundingBox().intersectsRect(tile50->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile51 = maplayer->tileAt(ccp(51,8));
	if(sheepRect->boundingBox().intersectsRect(tile51->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile52 = maplayer->tileAt(ccp(52,8));
	if(sheepRect->boundingBox().intersectsRect(tile52->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile53 = maplayer->tileAt(ccp(53,8));
	if(sheepRect->boundingBox().intersectsRect(tile53->boundingBox()))	sheep->setPositionY(125);

	//-------------- 투명 함정 1 시작--------------//
	CCSprite *tile54 = blocklayer->tileAt(ccp(54,8));
	CCSprite *tile54_0 = blocklayer->tileAt(ccp(54,9));
	if(sheepRect->boundingBox().intersectsRect(tile54->boundingBox())){
		sheep->setPositionY(125);
		tile54->setVisible(true);
		tile54_0->setVisible(true);
	}

	CCSprite *tile55 = blocklayer->tileAt(ccp(55,8));
	CCSprite *tile55_0 = blocklayer->tileAt(ccp(55,9));
	if(sheepRect->boundingBox().intersectsRect(tile55->boundingBox())){
		sheep->setPositionY(125);
		tile55->setVisible(true);
		tile55_0->setVisible(true);
	}

	CCSprite *tile56 = blocklayer->tileAt(ccp(56,8));
	CCSprite *tile56_0 = blocklayer->tileAt(ccp(56,9));

	CCSprite *tile57 = blocklayer->tileAt(ccp(57,8));
	CCSprite *tile57_0 = blocklayer->tileAt(ccp(57,9));
	if(sheepRect->boundingBox().intersectsRect(tile56->boundingBox())){
		sheep->setPositionY(125);
		trap03->setVisible(true);
		tile56->setVisible(true);
		tile56_0->setVisible(true);
		tile57->setVisible(true);
		tile57_0->setVisible(true);
	}

	CCSprite *tile58 = blocklayer->tileAt(ccp(58,8));
	CCSprite *tile58_0 = blocklayer->tileAt(ccp(58,9));
	if(sheepRect->boundingBox().intersectsRect(tile58->boundingBox())){
		sheep->setPositionY(125);
		tile58->setVisible(true);
		tile58_0->setVisible(true);
	}

	CCSprite *tile59 = blocklayer->tileAt(ccp(59,8));
	CCSprite *tile59_0 = blocklayer->tileAt(ccp(59,9));
	if(sheepRect->boundingBox().intersectsRect(tile59->boundingBox())){
		sheep->setPositionY(125);
		tile59->setVisible(true);
		tile59_0->setVisible(true);
	}

	CCSprite *tile60 = blocklayer->tileAt(ccp(60,8));
	CCSprite *tile60_0 = blocklayer->tileAt(ccp(60,9));
	if(sheepRect->boundingBox().intersectsRect(tile60->boundingBox())){
		sheep->setPositionY(125);
		tile60->setVisible(true);
		tile60_0->setVisible(true);
	}

	CCSprite *tile53_1 = blocklayer->tileAt(ccp(53,5));
	CCSprite *tile54_1 = blocklayer->tileAt(ccp(54,5));
	if(sheepR.intersectsRect(tile54_1->boundingBox())){
		tile54_1->setVisible(true);
		SheepDead();
	}

	CCSprite *tile55_1 = blocklayer->tileAt(ccp(55,4));
	if(sheepR.intersectsRect(tile55_1->boundingBox())){
		tile55_1->setVisible(true);
		SheepDead();
	}

	CCSprite *tile59_1 = blocklayer->tileAt(ccp(59,4));
	if(sheepR.intersectsRect(tile59_1->boundingBox())){
		tile59_1->setVisible(true);
		SheepDead();
	}

	CCSprite *tile60_1 = blocklayer->tileAt(ccp(60,5));
	if(sheepR.intersectsRect(tile60_1->boundingBox())){
		tile60_1->setVisible(true);
		SheepDead();
	}

	CCSprite *tile61_1 = blocklayer->tileAt(ccp(61,5));
	if(sheepR.intersectsRect(tile53_1->boundingBox()) || sheepRect->boundingBox().intersectsRect(tile61_1->boundingBox())){
		SheepDead();
	}
	//-------------- 투명 함정 1   끝--------------//
	CCSprite *tile61 = maplayer->tileAt(ccp(61,8));
	if(sheepRect->boundingBox().intersectsRect(tile61->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile62 = maplayer->tileAt(ccp(62,8));
	if(sheepRect->boundingBox().intersectsRect(tile62->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile63 = maplayer->tileAt(ccp(63,8));
	if(sheepRect->boundingBox().intersectsRect(tile63->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile64 = maplayer->tileAt(ccp(64,8));
	if(sheepRect->boundingBox().intersectsRect(tile64->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile65 = maplayer->tileAt(ccp(65,8));
	if(sheepRect->boundingBox().intersectsRect(tile65->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile66 = maplayer->tileAt(ccp(66,8));
	if(sheepRect->boundingBox().intersectsRect(tile66->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile67 = maplayer->tileAt(ccp(67,8));
	if(sheepRect->boundingBox().intersectsRect(tile67->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile68 = maplayer->tileAt(ccp(68,8));
	if(sheepRect->boundingBox().intersectsRect(tile68->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile69 = maplayer->tileAt(ccp(69,8));
	if(sheepRect->boundingBox().intersectsRect(tile69->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile70 = maplayer->tileAt(ccp(70,8));
	if(sheepRect->boundingBox().intersectsRect(tile70->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile71 = maplayer->tileAt(ccp(71,8));
	if(sheepRect->boundingBox().intersectsRect(tile71->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile72 = maplayer->tileAt(ccp(72,8));
	if(sheepRect->boundingBox().intersectsRect(tile72->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile73 = maplayer->tileAt(ccp(73,8));
	if(sheepRect->boundingBox().intersectsRect(tile73->boundingBox()))	sheep->setPositionY(125);

	CCSprite *tile94 = maplayer->tileAt(ccp(94,8));
	if(sheepRect->boundingBox().intersectsRect(tile94->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile95 = maplayer->tileAt(ccp(95,8));
	if(sheepRect->boundingBox().intersectsRect(tile95->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile96 = maplayer->tileAt(ccp(96,8));
	if(sheepRect->boundingBox().intersectsRect(tile96->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile97 = maplayer->tileAt(ccp(97,8));
	if(sheepRect->boundingBox().intersectsRect(tile97->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile98 = maplayer->tileAt(ccp(98,8));
	if(sheepRect->boundingBox().intersectsRect(tile98->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile99 = maplayer->tileAt(ccp(99,8));
	if(sheepRect->boundingBox().intersectsRect(tile99->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile100 = maplayer->tileAt(ccp(100,8));
	if(sheepRect->boundingBox().intersectsRect(tile100->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile101 = maplayer->tileAt(ccp(101,8));
	if(sheepRect->boundingBox().intersectsRect(tile101->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile102 = maplayer->tileAt(ccp(102,8));
	if(sheepRect->boundingBox().intersectsRect(tile102->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile103 = maplayer->tileAt(ccp(103,8));
	if(sheepRect->boundingBox().intersectsRect(tile103->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile104 = maplayer->tileAt(ccp(104,8));
	if(sheepRect->boundingBox().intersectsRect(tile104->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile105 = maplayer->tileAt(ccp(105,8));
	if(sheepRect->boundingBox().intersectsRect(tile105->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile106 = maplayer->tileAt(ccp(106,8));
	if(sheepRect->boundingBox().intersectsRect(tile106->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile107 = maplayer->tileAt(ccp(107,8));
	if(sheepRect->boundingBox().intersectsRect(tile107->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile108 = maplayer->tileAt(ccp(108,8));
	if(sheepRect->boundingBox().intersectsRect(tile108->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile109 = maplayer->tileAt(ccp(109,8));
	if(sheepRect->boundingBox().intersectsRect(tile109->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile110 = maplayer->tileAt(ccp(110,8));
	if(sheepRect->boundingBox().intersectsRect(tile110->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile111 = maplayer->tileAt(ccp(111,8));
	if(sheepRect->boundingBox().intersectsRect(tile111->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile112 = maplayer->tileAt(ccp(112,8));
	if(sheepRect->boundingBox().intersectsRect(tile112->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile113 = maplayer->tileAt(ccp(113,8));
	if(sheepRect->boundingBox().intersectsRect(tile113->boundingBox()))	sheep->setPositionY(125);

	//---------------------------- 공중 블럭 시작--------------------------------//
	CCSprite *tile110_U = maplayer->tileAt(ccp(110,0));
	if(sheepRect->boundingBox().intersectsRect(tile110_U->boundingBox()))	sheep->setPositionY(tile110_U->getPosition().y-38);
	CCSprite *tile111_U = maplayer->tileAt(ccp(111,0));
	if(sheepRect->boundingBox().intersectsRect(tile111_U->boundingBox()))	sheep->setPositionY(tile111_U->getPosition().y-38);
	CCSprite *tile112_U = maplayer->tileAt(ccp(112,0));
	if(sheepRect->boundingBox().intersectsRect(tile112_U->boundingBox()))	sheep->setPositionY(tile112_U->getPosition().y-38);
	CCSprite *tile113_U = maplayer->tileAt(ccp(113,0));
	if(sheepRect->boundingBox().intersectsRect(tile113_U->boundingBox()))	sheep->setPositionY(tile113_U->getPosition().y-38);
	CCSprite *tile114_U = maplayer->tileAt(ccp(114,0));
	if(sheepRect->boundingBox().intersectsRect(tile114_U->boundingBox()))	sheep->setPositionY(tile114_U->getPosition().y-38);
	CCSprite *tile115_U = maplayer->tileAt(ccp(115,0));
	if(sheepRect->boundingBox().intersectsRect(tile115_U->boundingBox()))	sheep->setPositionY(tile115_U->getPosition().y-38);
	CCSprite *tile116_U = maplayer->tileAt(ccp(116,0));
	if(sheepRect->boundingBox().intersectsRect(tile116_U->boundingBox()))	sheep->setPositionY(tile116_U->getPosition().y-38);
	CCSprite *tile117_U = maplayer->tileAt(ccp(117,0));
	if(sheepRect->boundingBox().intersectsRect(tile117_U->boundingBox()))	sheep->setPositionY(tile117_U->getPosition().y-38);
	CCSprite *tile118_U = maplayer->tileAt(ccp(118,0));
	if(sheepRect->boundingBox().intersectsRect(tile118_U->boundingBox()))	sheep->setPositionY(tile118_U->getPosition().y-38);
	CCSprite *tile119_U = maplayer->tileAt(ccp(119,0));
	if(sheepRect->boundingBox().intersectsRect(tile119_U->boundingBox()))	sheep->setPositionY(tile119_U->getPosition().y-38);
	CCSprite *tile120_U = maplayer->tileAt(ccp(120,0));
	if(sheepRect->boundingBox().intersectsRect(tile120_U->boundingBox()))	sheep->setPositionY(tile120_U->getPosition().y-38);
	CCSprite *tile121_U = maplayer->tileAt(ccp(121,0));
	if(sheepRect->boundingBox().intersectsRect(tile121_U->boundingBox()))	sheep->setPositionY(tile121_U->getPosition().y-38);
	CCSprite *tile122_U = maplayer->tileAt(ccp(122,0));
	if(sheepRect->boundingBox().intersectsRect(tile122_U->boundingBox()))	sheep->setPositionY(tile122_U->getPosition().y-38);
	CCSprite *tile123_U = maplayer->tileAt(ccp(123,0));
	if(sheepRect->boundingBox().intersectsRect(tile123_U->boundingBox()))	sheep->setPositionY(tile123_U->getPosition().y-38);
	CCSprite *tile124_U = maplayer->tileAt(ccp(124,0));
	if(sheepRect->boundingBox().intersectsRect(tile124_U->boundingBox()))	sheep->setPositionY(tile124_U->getPosition().y-38);
	CCSprite *tile125_U = maplayer->tileAt(ccp(125,0));
	if(sheepRect->boundingBox().intersectsRect(tile125_U->boundingBox()))	sheep->setPositionY(tile125_U->getPosition().y-38);
	CCSprite *tile126_U = maplayer->tileAt(ccp(126,0));
	if(sheepRect->boundingBox().intersectsRect(tile126_U->boundingBox()))	sheep->setPositionY(tile126_U->getPosition().y-38);
	CCSprite *tile127_U = maplayer->tileAt(ccp(127,0));
	if(sheepRect->boundingBox().intersectsRect(tile127_U->boundingBox()))	sheep->setPositionY(tile127_U->getPosition().y-38);
	CCSprite *tile128_U = maplayer->tileAt(ccp(128,0));
	if(sheepRect->boundingBox().intersectsRect(tile128_U->boundingBox()))	sheep->setPositionY(tile128_U->getPosition().y-38);
	CCSprite *tile129_U = maplayer->tileAt(ccp(129,0));
	if(sheepRect->boundingBox().intersectsRect(tile129_U->boundingBox()))	sheep->setPositionY(tile129_U->getPosition().y-38);

	CCSprite *tile145_U = maplayer->tileAt(ccp(145,0));
	if(sheepRect->boundingBox().intersectsRect(tile145_U->boundingBox()))	sheep->setPositionY(tile145_U->getPosition().y-38);
	CCSprite *tile146_U = maplayer->tileAt(ccp(146,0));
	if(sheepRect->boundingBox().intersectsRect(tile146_U->boundingBox()))	sheep->setPositionY(tile146_U->getPosition().y-38);
	CCSprite *tile147_U = maplayer->tileAt(ccp(147,0));
	if(sheepRect->boundingBox().intersectsRect(tile147_U->boundingBox()))	sheep->setPositionY(tile147_U->getPosition().y-38);
	CCSprite *tile148_U = maplayer->tileAt(ccp(148,0));
	if(sheepRect->boundingBox().intersectsRect(tile148_U->boundingBox()))	sheep->setPositionY(tile148_U->getPosition().y-38);
	CCSprite *tile149_U = maplayer->tileAt(ccp(149,0));
	if(sheepRect->boundingBox().intersectsRect(tile149_U->boundingBox()))	sheep->setPositionY(tile149_U->getPosition().y-38);
	CCSprite *tile150_U = maplayer->tileAt(ccp(150,0));
	if(sheepRect->boundingBox().intersectsRect(tile150_U->boundingBox()))	sheep->setPositionY(tile150_U->getPosition().y-38);
	CCSprite *tile151_U = maplayer->tileAt(ccp(151,0));
	if(sheepRect->boundingBox().intersectsRect(tile151_U->boundingBox()))	sheep->setPositionY(tile151_U->getPosition().y-38);
	CCSprite *tile152_U = maplayer->tileAt(ccp(152,0));
	if(sheepRect->boundingBox().intersectsRect(tile152_U->boundingBox()))	sheep->setPositionY(tile152_U->getPosition().y-38);
	CCSprite *tile153_U = maplayer->tileAt(ccp(153,0));
	if(sheepRect->boundingBox().intersectsRect(tile153_U->boundingBox()))	sheep->setPositionY(tile153_U->getPosition().y-38);
	CCSprite *tile154_U = maplayer->tileAt(ccp(154,0));
	if(sheepRect->boundingBox().intersectsRect(tile154_U->boundingBox()))	sheep->setPositionY(tile154_U->getPosition().y-38);
	CCSprite *tile155_U = maplayer->tileAt(ccp(155,0));
	if(sheepRect->boundingBox().intersectsRect(tile155_U->boundingBox()))	sheep->setPositionY(tile155_U->getPosition().y-38);
	CCSprite *tile156_U = maplayer->tileAt(ccp(156,0));
	if(sheepRect->boundingBox().intersectsRect(tile156_U->boundingBox()))	sheep->setPositionY(tile156_U->getPosition().y-38);
	CCSprite *tile157_U = maplayer->tileAt(ccp(157,0));
	if(sheepRect->boundingBox().intersectsRect(tile157_U->boundingBox()))	sheep->setPositionY(tile157_U->getPosition().y-38);
	//---------------------------- 공중 블럭 끝--------------------------------//

	CCSprite *tile153 = maplayer->tileAt(ccp(153,8));
	if(sheepRect->boundingBox().intersectsRect(tile153->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile154 = maplayer->tileAt(ccp(154,8));
	if(sheepRect->boundingBox().intersectsRect(tile154->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile155 = maplayer->tileAt(ccp(155,8));
	if(sheepRect->boundingBox().intersectsRect(tile155->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile156 = maplayer->tileAt(ccp(156,8));
	if(sheepRect->boundingBox().intersectsRect(tile156->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile157 = maplayer->tileAt(ccp(157,8));
	if(sheepRect->boundingBox().intersectsRect(tile157->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile158 = maplayer->tileAt(ccp(158,8));
	if(sheepRect->boundingBox().intersectsRect(tile158->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile159 = maplayer->tileAt(ccp(159,8));
	if(sheepRect->boundingBox().intersectsRect(tile159->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile160 = maplayer->tileAt(ccp(160,8));
	if(sheepRect->boundingBox().intersectsRect(tile160->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile161 = maplayer->tileAt(ccp(161,8));
	if(sheepRect->boundingBox().intersectsRect(tile161->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile162 = maplayer->tileAt(ccp(162,8));
	if(sheepRect->boundingBox().intersectsRect(tile162->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile163 = maplayer->tileAt(ccp(163,8));
	if(sheepRect->boundingBox().intersectsRect(tile163->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile164 = maplayer->tileAt(ccp(164,8));
	if(sheepRect->boundingBox().intersectsRect(tile164->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile165 = maplayer->tileAt(ccp(165,8));
	if(sheepRect->boundingBox().intersectsRect(tile165->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile166 = maplayer->tileAt(ccp(166,8));
	if(sheepRect->boundingBox().intersectsRect(tile166->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile167 = maplayer->tileAt(ccp(167,8));
	if(sheepRect->boundingBox().intersectsRect(tile167->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile168 = maplayer->tileAt(ccp(168,8));
	if(sheepRect->boundingBox().intersectsRect(tile168->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile169 = maplayer->tileAt(ccp(169,8));
	if(sheepRect->boundingBox().intersectsRect(tile169->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile170 = maplayer->tileAt(ccp(170,8));
	if(sheepRect->boundingBox().intersectsRect(tile170->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile171 = maplayer->tileAt(ccp(171,8));
	if(sheepRect->boundingBox().intersectsRect(tile171->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile172 = maplayer->tileAt(ccp(172,8));
	if(sheepRect->boundingBox().intersectsRect(tile172->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile173 = maplayer->tileAt(ccp(173,8));
	if(sheepRect->boundingBox().intersectsRect(tile173->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile174 = maplayer->tileAt(ccp(174,8));
	if(sheepRect->boundingBox().intersectsRect(tile174->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile175 = maplayer->tileAt(ccp(175,8));
	if(sheepRect->boundingBox().intersectsRect(tile175->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile176 = maplayer->tileAt(ccp(176,8));
	if(sheepRect->boundingBox().intersectsRect(tile176->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile177 = maplayer->tileAt(ccp(177,8));
	if(sheepRect->boundingBox().intersectsRect(tile177->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile178 = maplayer->tileAt(ccp(178,8));
	if(sheepRect->boundingBox().intersectsRect(tile178->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile179 = maplayer->tileAt(ccp(179,8));
	if(sheepRect->boundingBox().intersectsRect(tile179->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile180 = maplayer->tileAt(ccp(180,8));
	if(sheepRect->boundingBox().intersectsRect(tile180->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile181 = maplayer->tileAt(ccp(181,8));
	if(sheepRect->boundingBox().intersectsRect(tile181->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile182 = maplayer->tileAt(ccp(182,8));
	if(sheepRect->boundingBox().intersectsRect(tile182->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile183 = maplayer->tileAt(ccp(183,8));
	if(sheepRect->boundingBox().intersectsRect(tile183->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile184 = maplayer->tileAt(ccp(184,8));
	if(sheepRect->boundingBox().intersectsRect(tile184->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile185 = maplayer->tileAt(ccp(185,8));
	if(sheepRect->boundingBox().intersectsRect(tile185->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile186 = maplayer->tileAt(ccp(186,8));
	if(sheepRect->boundingBox().intersectsRect(tile186->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile187 = maplayer->tileAt(ccp(187,8));
	if(sheepRect->boundingBox().intersectsRect(tile187->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile188 = maplayer->tileAt(ccp(188,8));
	if(sheepRect->boundingBox().intersectsRect(tile188->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile189 = maplayer->tileAt(ccp(189,8));
	if(sheepRect->boundingBox().intersectsRect(tile189->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile190 = maplayer->tileAt(ccp(190,8));
	if(sheepRect->boundingBox().intersectsRect(tile190->boundingBox()))	sheep->setPositionY(125);
	CCSprite *tile191 = maplayer->tileAt(ccp(191,8));
	if(sheepRect->boundingBox().intersectsRect(tile191->boundingBox()))	sheep->setPositionY(125);

	//티모사망
	CCSprite *Teemo = blocklayer->tileAt(ccp(170,7));
	if(sheepRect->boundingBox().intersectsRect(Teemo->boundingBox())){
		SheepTeemoDead();
	}

	//버섯시작
	CCSprite *mush01 = blocklayer->tileAt(ccp(164,7));
	if(sheepRect->boundingBox().intersectsRect(mush01->boundingBox())){
		mush01->setVisible(true);
		SheepMushDead();
	}

	CCSprite *mush02 = blocklayer->tileAt(ccp(177,7));
	if(sheepRect->boundingBox().intersectsRect(mush02->boundingBox())){
		mush02->setVisible(true);
		SheepMushDead();
	}

	CCSprite *mush03 = blocklayer->tileAt(ccp(181,7));
	if(sheepRect->boundingBox().intersectsRect(mush03->boundingBox())){
		mush03->setVisible(true);
		SheepMushDead();
	}

	CCSprite *mush04 = blocklayer->tileAt(ccp(186,7));
	if(sheepRect->boundingBox().intersectsRect(mush04->boundingBox())){
		mush04->setVisible(true);
		SheepMushDead();
	}
	//버섯끗
//------------------------------------------ 타일 끝-----------------------------------------------------------//
}
