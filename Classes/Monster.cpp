#include "Monster.h"
#include "CsvUtil.h"
#include "GlobalPath.h"
#include "PosBase.h"
#include "ControllerSimpleMove.h"
#include "EnumMonsterPropConfType.h"
#include "GlobalDefine.h"
Monster::Monster() {
	m_moveController = NULL;
	m_iSpeed = MONSTER_SPEED_INIT;
	m_iLevel = 1;
	m_isMoveEnd = false;
}

Monster::~Monster() {
}

bool Monster::init() {
	m_moveController = ControllerSimpleMove::create(this);
	this->addChild(m_moveController);

	m_moveController->bindMoveEndFunc([&]() {
	
		int iMagicChange = -getiLevel() * 10;
		NOTIFY->postNotification("MagicChange", (Ref*)iMagicChange);
		m_isMoveEnd = true;
	});
	return true;
}

Monster* Monster::createFromCsvFileByID(int iMonsterID) {
	Monster* monster = new Monster();

	if (monster && monster->initFromCsvFileByID(iMonsterID)) {
		monster->autorelease();
	}
	else {
		CC_SAFE_DELETE(monster);
	}
	return monster;
}

bool Monster::initFromCsvFileByID(int iMonsterID) {
	bool bRet = false;

	do {
		CsvUtil* csvUtil = CsvUtil::getInstance();

		std::string sMonsterID = StringUtils::format("%d", iMonsterID);

		/* 寻找ID所在的行 */
		int iLine = csvUtil->findValueInWithLine(sMonsterID.c_str(),
			enMonsterPropConf_ID, PATH_CSV_MONSTER_CONF);

		CC_BREAK_IF(iLine < 0);

		setID(iMonsterID);
		setiLevel(csvUtil->getInt(iLine, enMonsterPropConf_Level, PATH_CSV_MONSTER_CONF));
		setiModelID(csvUtil->getInt(iLine, enMonsterPropConf_ModelID, PATH_CSV_MONSTER_CONF));
		setiDefense(csvUtil->getInt(iLine, enMonsterPropConf_Defense, PATH_CSV_MONSTER_CONF));
		setiHP(csvUtil->getInt(iLine, enMonsterPropConf_Hp, PATH_CSV_MONSTER_CONF));
		setiSpeed(csvUtil->getInt(iLine, enMonsterPropConf_Speed, PATH_CSV_MONSTER_CONF));

		CC_BREAK_IF(!init());

		bRet = true;
	} while (0);

	return bRet;
}

void Monster::moveByPosList(Vector<PosBase*> posList) {
	if (posList.size() < 1) {
		return;
	}
	m_moveController->moveByPosList(posList, 2, getiSpeed());
}

void Monster::onDead() {
	this->removeFromParent();

	int iTowerSoulNumChange = 3 * getiLevel();
	NOTIFY->postNotification("TowerSoulChange", (Ref*)iTowerSoulNumChange);
}

void Monster::onBindSprite() {
	auto UI = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HpBar/HpBar_1.ExportJson");
	this->addChild(UI);
	Size size = this->getContentSize();
	UI->setPosition(Point(size.width*0.5f, size.height));

	m_hPBar = (LoadingBar *)Helper::seekWidgetByName(UI, "hpbar");
	m_hPBar->setPercent(100);

	m_iMaxHP = getiHP();
}

void Monster::onHurt(int iHurtValue) {
	m_hPBar->setPercent(getiHP() / (float)m_iMaxHP * 100);
}