//------ 작성자:김명식 ------- 작성일:2013년 11월 20일 수요일 --------//
#ifndef sa_Stage01
#define sa_Stage01

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

static CCDictionary s_dic;

class Stage01 : public CCLayer
{
public:
	virtual bool init();

	static CCScene* scene();

	CREATE_FUNC(Stage01);

	void update(float dt);

	//터치 메소드
	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *event);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *event);
	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *event);

	//배경음 1초후 재생
	void introTick();

	//타일맵
	CCTMXTiledMap *stageMap;
	CCPoint World;
	CCSprite *sheepRect;

	void collisionCheck();

	CCPoint tilePosition(CCPoint position);

	//패럴렉스 노드 메소드
	void createBackgroundParallax();

	//버튼 메소드
	void createButtons();

	//터치 유효 확인 메소드
	bool isTouchInside(CCSprite *sprite, CCTouch *touch);

	//배경 움직임 메소드
	void startMovingBackground();

	//배경 멈춤 메소드
	void stopMovingBackground();

	//배경 이동 조건 메소드
	void moveBackground(float f);

	//캐릭터 이동 조건 메소드
	void moveSheep(CCNode *BackgroundNode, const CCPoint &moveStep, const CCPoint &BackgroundPos);

	//점프 콜백 메소드
	void JumpEnd();

	//점프 여부
	bool jumpYN;

	//터치 스프라이트
	CCSprite *rightSprite;
	CCSprite *rightPressedSprite;
	CCSprite *leftSprite;
	CCSprite *leftPressedSprite;
	CCSprite *JumpSprite;
	CCSprite *JumpPressedSprite;
	CCSprite *JumpBrokenSprite;

	//화면 사이즈
	CCSize winSize;

	//버튼 눌름 여부 확인
	bool isLeftPressed;
	bool isRightPressed;
	bool isJumpPressed;

	//주인공
	CCSprite *sheep;
	CCSprite *sheepM;
	CCSprite *sheepJ;

	void createSheep();
	void movingSheep();
	bool moving;

	//몬스터
	CCSprite *monster01;

	//게임 피니쉬,오버
	void SheepDead();
	void SheepMushDead();
	void SheepTeemoDead();
	void GameFinish();
	void GameOver();

	//뒤로가기 버튼
	void BackButton();
	void BackTouch(CCObject *sender);

	//터치시작
	void TouchStart();

	//타일 움직임
	void MovingTile();

	//파티클
	void doParticles();
	void doParticles2();
	void doParticles3();

	//중력반전 적용,해제
	void gravityReverse();
	void gravityReverseFunc();
	void gravityUnReverseFunc();
};
#endif
