#include "HeroManager.h"
#include "PosLoadUtil.h"
HeroManager::HeroManager()
{

}
HeroManager::~HeroManager()
{

}

HeroManager*HeroManager::createWithLevel(int iCurLevel)
{
	HeroManager*herMgr = new HeroManager();
	if (herMgr && herMgr->initWithLevel(iCurLevel))
	{
		herMgr->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(herMgr);
	}

	return herMgr;
}

bool HeroManager::initWithLevel(int iCurLevel)
{
	std::string sTowerPosPath = StringUtils::format("tollgate/towerPos_level_%d.plist", iCurLevel);
	Vector<PosBase*>posList = PosLoadUtil::getInstance()->loadPosWithFile(sTowerPosPath.c_str(), enTowerPos, this, 10, false);
	m_towerPosList.pushBack(posList);

	createTowerBorder(iCurLevel);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch *touch, Event*event) {
		return true;
	};
	listener->onTouchEnded = [&](Touch *touch, Event*event) {

		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		TowerBorder *clickBroder = findClickTowerBorder(pos);
		if (clickBroder == NULL)
		{
			return;
		}

		if (clickBroder->getHero() == NULL)
		{
			Hero* hero = Hero::createFromCsvFileByID(1);
			hero->setPosition(clickBroder->getPosition());
			this->addChild(hero, TOWER_LAYER_LVL);

			clickBroder->bindHero(hero);
		}
		else
		{
			clickBroder->showTowerOprBtns();
		}
	};
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

void HeroManager::createTowerBorder(int iCurLevel)
{
	for (auto tpos:m_towerPosList)
	{
		TowerBorder* border = TowerBorder::create();
		border->upgrade();
		border->upgrade();
		border->setPosition(tpos->getPos());
		this->addChild(border);
		m_towerBorderList.pushBack(border);
	}
}

void HeroManager::createTowerPos(Point pos)
{
	TowerPos *tpos = TowerPos::create(pos, true);
	this->addChild(tpos, TOWER_POS_LAYER_LVL);
	m_towerPosList.pushBack(tpos);
}

TowerBorder* HeroManager::findClickTowerBorder(Point pos)
{
	for (auto tBorder : m_towerBorderList)
	{
		if (tBorder->isClickMe(pos))
		{
			return tBorder;
		}
	}
	return NULL;
}

void HeroManager::logic(float dt, Vector<Monster*> monsterList)
{
	for (auto tBorder : m_towerBorderList)
	{
		if (tBorder->getHero() != NULL)
		{
			tBorder->getHero()->checkAtkMonster(dt, monsterList);
		}
	}
}