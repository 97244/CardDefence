#include "TollgateMapLayer.h"
#include "GlobalDefine.h"
#define HOME_LAYER_LVL 3  // 堡垒的层次
#define HERO_LAYER_LVL 10    // 英雄的层次
#define MONSTER_LAYER_LVL 15    // 怪物的层次
#define BULLET_LAYER_LVL 20  // 子弹的层次
#include "GlobalClient.h"
TollgateMapLayer::TollgateMapLayer()
{
	m_iCurLevel = GlobalClient::getInstance()->getiCurTollgateLevel();
}
TollgateMapLayer::~TollgateMapLayer()
{

}

bool TollgateMapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	loadConfig();

	m_heroMgr = HeroManager::createWithLevel(m_iCurLevel);
	this->addChild(m_heroMgr, HERO_LAYER_LVL);

	m_monsterMgr = MonsterManager::createWithLevel(m_iCurLevel);
	this->addChild(m_monsterMgr, MONSTER_LAYER_LVL);

	this->schedule(schedule_selector(TollgateMapLayer::logic));
	
	createStartPoint();
	createEndPoint();
	return true;
}
void TollgateMapLayer::createStartPoint()
{
	MonsterPos *pos = m_monsterMgr->getMonsterStartPos();
	Sprite * startSp = Sprite::create("sprite/start.png");
	startSp->setPosition(pos->getPos());

	auto rotateBy = RotateBy::create(15.0f, 360, 360);
	auto repeat = RepeatForever::create(rotateBy);
	startSp->runAction(repeat);
	this->addChild(startSp, HOME_LAYER_LVL);
}
void TollgateMapLayer::createEndPoint()
{
	MonsterPos *pos = m_monsterMgr->getMonsterEndPos();
	Sprite * endSp = Sprite::create("sprite/end.png");
	endSp->setPosition(pos->getPos());

	auto rotateBy = RotateBy::create(15.0f, 360, 360);
	auto repeat = RepeatForever::create(rotateBy);
	endSp->runAction(repeat);
	this->addChild(endSp, HOME_LAYER_LVL);
}
void TollgateMapLayer::logic(float dt)
{
	m_heroMgr->logic(dt,m_monsterMgr->getMonsterList());
}
void TollgateMapLayer::loadConfig()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(StringUtils::format("music/tollgate_%d.mp3", m_iCurLevel).c_str(), true);

	std::string sBg = StringUtils::format("tollgate/level_%d.jpg", m_iCurLevel);
	Sprite *map = Sprite::create(sBg.c_str());
	map->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(map, 1);

}

void TollgateMapLayer::initData() {
	/* 初始化塔魂、怪物和魔力数量 */
	int iTowerSoulNum = 5;                                          /* 塔魂数量 */
	int iMonsterNum = m_monsterMgr->getNotShowMonsterCount();       /* 怪物数量 */
	int iMagicNum = 100;                                            /* 魔力数量 */

	NOTIFY->postNotification("TowerSoulChange", (Ref*)iTowerSoulNum);
	NOTIFY->postNotification("MonsterNumChange", (Ref*)iMonsterNum);
	NOTIFY->postNotification("MagicChange", (Ref*)iMagicNum);
}
