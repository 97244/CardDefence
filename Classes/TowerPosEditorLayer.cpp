#include "TowerPosEditorLayer.h"
#include "PosLoadUtil.h"
#include "CCPlatformConfig.h"
#include "MonsterPos.h"
bool TowerPosEditorLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [](Touch* touch, Event *event) {
		return true;
	};
	listener->onTouchEnded = [&](Touch* touch, Event *event) {
		Point pos = Director::getInstance()->convertToGL(touch->getLocationInView());
		switch (m_enMode)
		{
			case enTowerPos:
				editTowerPos(pos);
				break;
			case enMonsterPos:
				editMonsterPos(pos);
				break;
		}
		
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->loadConfigFile();
	return true;
}

void TowerPosEditorLayer::editTowerPos(Point pos)
{
	PosBase * existPos = findExistTowerPos(pos);
	if (existPos != NULL)
	{
		deleteTowerPos(existPos);
	}
	else
	{
		createTowerPos(pos);
	}

}

PosBase*TowerPosEditorLayer::findExistTowerPos(Point pos)
{
	for (auto basePos : m_towerPosList)
	{
		if (basePos->isClickMe(pos))
		{
			return basePos;
		}
	}

	return NULL;
}

void TowerPosEditorLayer::createTowerPos(Point pos)
{
	TowerPos *tPos = TowerPos::create(pos, true);
	this->addChild(tPos, 100);
	m_towerPosList.pushBack(tPos);
}

void TowerPosEditorLayer::deleteTowerPos(PosBase*existPos)
{
	this->removeChild(existPos);
	m_towerPosList.eraseObject(existPos);
}

TowerPosEditorLayer::TowerPosEditorLayer()
{
	m_iCurLevel = 1;
	m_enMode = enTowerPos;
}

TowerPosEditorLayer::~TowerPosEditorLayer()
{

}

void TowerPosEditorLayer::deleteAllPos()
{
	this->removeAllChildrenWithCleanup(true);
	m_towerPosList.clear();
	m_monsterPosList.clear();
}
void TowerPosEditorLayer::changeMode()
{
	if (m_enMode == enMonsterPos)
	{
		m_enMode = enTowerPos;
	}
	else
	{
		m_enMode = enMonsterPos;
	}
}

int TowerPosEditorLayer::nextLvl() {
	deleteAllPos();		/* ɾ����ǰ���е�������� */
	m_iCurLevel++;		/* �ؿ�������1 */
	loadConfigFile();	/* ���¶�ȡ�����ļ� */

	return m_iCurLevel;
}

int TowerPosEditorLayer::preLvl() {
	deleteAllPos();		/* ɾ����ǰ���е�������� */
	m_iCurLevel--;		/* �ؿ�������1 */
	loadConfigFile();	/* ���¶�ȡ�����ļ� */

	return m_iCurLevel;
}

void TowerPosEditorLayer::outputPosToPlistFile() {
	/* �����̨���������ļ� */
	std::string sTowerPosPath = StringUtils::format("tollgate/towerPos_level_%d.plist", m_iCurLevel);
	outputPosToPlistFile(m_towerPosList, sTowerPosPath.c_str());

	/* ����������������ļ� */
	std::string sMonsterPosPath = StringUtils::format("tollgate/monsterPos_level_%d.plist", m_iCurLevel);
	outputPosToPlistFile(m_monsterPosList, sMonsterPosPath.c_str());
}

void TowerPosEditorLayer::outputPosToPlistFile(Vector<PosBase*> posList, const char * sFilePath)
{
	ValueMap fileDataMap;
	int index = 1;
	for (auto posBase : posList)
	{
		ValueMap data;
		data["x"] = posBase->getPos().x;
		data["y"] = posBase->getPos().y;
		fileDataMap[StringUtils::toString(index)] = Value(data);
		index++;
	}
	FileUtils::getInstance()->writeToFile(fileDataMap, sFilePath);
}

void TowerPosEditorLayer::loadConfigFile()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//��ӵ�ͼ����
	std::string sBG = StringUtils::format("tollgate/level_%d.jpg",m_iCurLevel);
	Sprite *map = Sprite::create(sBG.c_str());
	map->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
	this->addChild(map,1);

	//�������������
	std::string sTowerPosPath = StringUtils::format("tollgate/towerPos_level_%d.plist", m_iCurLevel);
	Vector<PosBase*> towerPosList = PosLoadUtil::getInstance()->loadPosWithFile(sTowerPosPath.c_str(),enTowerPos, this, 10, true);
	
	m_towerPosList.pushBack(towerPosList);

	//���ع����������
	std::string sMonsterPosPath = StringUtils::format("tollgate/monsterPos_level_%d.plist", m_iCurLevel);
	Vector<PosBase*> monsterPosList = PosLoadUtil::getInstance()->loadPosWithFile(sMonsterPosPath.c_str(),enMonsterPos, this, 10, true);

	m_monsterPosList.pushBack(monsterPosList);


}

void TowerPosEditorLayer::editMonsterPos(Point pos)
{
	PosBase *existPos = findExistMonsterPos(pos);
	if (existPos != NULL)
	{
		deleteMonsterpos(existPos);
	}
	else
	{
		createMonsterPos(pos);
	}
}

PosBase *TowerPosEditorLayer::findExistMonsterPos(Point pos)
{
	for (auto basePos:m_monsterPosList)
	{
		if (basePos->isClickMe(pos))
		{
			return basePos;
		}
	}
	return NULL;
}

void TowerPosEditorLayer::createMonsterPos(Point pos)
{
	MonsterPos *tpos = MonsterPos::create(pos, true);
	this->addChild(tpos, 10);
	m_monsterPosList.pushBack(tpos);
}

void TowerPosEditorLayer::deleteMonsterpos(PosBase*existPos)
{
	this->removeChild(existPos);
	m_monsterPosList.eraseObject(existPos);
}

Vector<PosBase*>TowerPosEditorLayer::getMonsterPosList()
{
	return m_monsterPosList;
}