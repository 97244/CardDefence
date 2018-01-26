#include "Hero.h"
#include "CsvUtil.h"
#include "GlobalPath.h"
#include "EnumHeroPropConfType.h"
#include "BulletManager.h"
#include "TollgateDataLayer.h"
#include "GlobalDefine.h"
#include "TollgateScene.h"
Hero::Hero() {
	m_atkMonster = NULL;
	m_isAtkCoolDown = false;
}

Hero::~Hero() {
}

Hero* Hero::create(Sprite* sprite) {
	Hero* hero = new Hero();
	if (hero && hero->init(sprite)) {
		hero->autorelease();
	}
	else {
		CC_SAFE_DELETE(hero);
	}
	return hero;
}

bool Hero::init(Sprite* sprite) {
	bool bRet = false;
	do {
		CC_BREAK_IF(!sprite);
		bindSprite(sprite);

		m_bulletMgr = BulletManager::create();
		this->addChild(m_bulletMgr);
		bRet = true;
	} while (0);

	return bRet;
}

Hero* Hero::createFromCsvFileByID(int iHeroID) {
	Hero* hero = new Hero();
	if (hero && hero->initFromCsvFileByID(iHeroID)) {
		hero->autorelease();
	}
	else {
		CC_SAFE_DELETE(hero);
	}
	return hero;
}
void Hero::checkAtkMonster(float ft, Vector<Monster *> monsterList)
{
	if (m_atkMonster != NULL) {
		/* 怪物已死亡 */
		if (m_atkMonster->isDead()) {
			/* 从怪物列表中删除怪物 */
			monsterList.eraseObject(m_atkMonster);

			/* 清除锁定的怪物引用 */
			m_atkMonster = NULL;
			return;
		}
		/* 攻击冷却结束，可以攻击 */
		if (m_isAtkCoolDown == false) {
			atk();
		}

		/* 判断怪物是否离开攻击范围 */
		checkAimIsOutOfRange(monsterList);
	}
	else {
		/* 选择一个进入攻击范围的怪物 */
		chooseAim(monsterList);
	}
}
void Hero::atk()
{
	log("atk!!!!");
	BulletBase * bullet = m_bulletMgr->getAnyUnUsedBullet();
	if (bullet != NULL)
	{
		Point heroWorldPos = this->getParent()->convertToWorldSpace(getPosition());
		bullet->setPosition(bullet->getParent()->convertToNodeSpace(heroWorldPos));
		bullet->setiAtkValue(getiCurAtk());
		bullet->lockAim(m_atkMonster);
		m_isAtkCoolDown = true;
		this->scheduleOnce(schedule_selector(Hero::atkCollDownEnd), getiAtkSpeed() / 1000.0f);

	}
	
}

void Hero::atkCollDownEnd(float dt)
{
	m_isAtkCoolDown = false;
}


void Hero::checkAimIsOutOfRange(Vector<Monster*>monsterList)
{
	if (m_atkMonster != NULL)
	{
		if (isInAtkRange(m_atkMonster->getPosition()) == false)
		{
			missAtkMonster();
		}
	}
}

void Hero::missAtkMonster()
{
	log("Out Of Range!!!");
	m_atkMonster = NULL;
}
void Hero::chooseAim(Vector<Monster*> monsterList)
{
	for (auto monster:monsterList)
	{
		if (monster->isVisible() && isInAtkRange(monster->getPosition()))
		{
			chooseAtkMonster(monster);
			log("InAtkRange!!!!");
			break;
		}
	}
}

bool Hero::isInAtkRange(Point pos)
{
	int iDoubleAtkRange = getiAtkRange();
	Point heroPos = getPosition();
	float length = pos.getDistanceSq(heroPos);
	if (length <= iDoubleAtkRange*iDoubleAtkRange)
	{
		return true;
	}
	return false;
}

void Hero::chooseAtkMonster(Monster *monster)
{
	m_atkMonster = monster;
}
bool Hero::initFromCsvFileByID(int iHeroID) {
	bool bRet = false;

	do {
		CsvUtil* csvUtil = CsvUtil::getInstance();

		std::string sHeroID = StringUtils::toString(iHeroID);

		/* 寻找ID所在的行 */
		int iLine = csvUtil->findValueInWithLine(
			sHeroID.c_str(), enHeroPropConf_ID, PATH_CSV_HERO_CONF);

		CC_BREAK_IF(iLine < 0);

		setID(iHeroID);
		setiModelID(csvUtil->getInt(iLine, enHeroPropConf_ModelID, PATH_CSV_HERO_CONF));
		setiBaseAtk(csvUtil->getInt(iLine, enHeroPropConf_BaseAtk, PATH_CSV_HERO_CONF));
		setiCurAtk(getiBaseAtk());
		setiAtkSpeed(csvUtil->getInt(iLine, enHeroPropConf_AtkSpeed, PATH_CSV_HERO_CONF));
		setiAtkRange(csvUtil->getInt(iLine, enHeroPropConf_AtkRange, PATH_CSV_HERO_CONF));
		setiUpgradeCostBase(csvUtil->getInt(iLine, enHeroPropConf_UpgradeCostBase, PATH_CSV_HERO_CONF));
		setfUpgradeAtkBase(csvUtil->getFloat(iLine, enHeroPropConf_UpgradeAtkBase, PATH_CSV_HERO_CONF));

		Sprite* sprite = Sprite::create(StringUtils::format("sprite/hero/hero_%d.png", iHeroID).c_str());
		CC_BREAK_IF(!sprite);

		CC_BREAK_IF(!init(sprite));

		bRet = true;
	} while (0);

	return bRet;
}

void Hero::upgrade()
{
	Sprite* sprite = getSprite();
	if (sprite == NULL || m_iLevel >=4)
	{
		return;
	}

	auto dataLayer = (TollgateDataLayer*)Director::getInstance()->getRunningScene()->getChildByTag(TAG_DATA_LAYER);

	int icurMgaicNum = dataLayer->getiTowerSoulNum();
	int iCostTowerSoul = m_iUpgradeCostBase*m_iLevel;
	if (iCostTowerSoul > icurMgaicNum)
	{
		return;
	}

	NOTIFY->postNotification("TowerSoulChange", (Ref*)iCostTowerSoul);
	m_iLevel++;

	if (m_iLevel == 2)
	{
		Sprite*heroTop1 = Sprite::create("sprite/hero/hero_top_1.png");
		this->addChild(heroTop1);
	}

	if (m_iLevel == 3)
	{
		Sprite*heroTop2 = Sprite::create("sprite/hero/hero_top_2.png");
		this->addChild(heroTop2);

		auto rotateBy = RotateBy::create(25.0f, 360, 360);
		auto repeat = RepeatForever::create(rotateBy);
		heroTop2->runAction(repeat);
	}

	if (m_iLevel == 4)
	{
		Sprite*heroTop3 = Sprite::create("sprite/hero/hero_top_3.png");
		this->addChild(heroTop3);

		auto rotateBy = RotateBy::create(10.00f, 360, 360);
		auto repeat = RepeatForever::create(rotateBy);
		heroTop3->runAction(repeat);
	}

	setiBaseAtk(getiBaseAtk()*m_fUpgradeAtkBase);
	setiCurAtk(getiBaseAtk());
}