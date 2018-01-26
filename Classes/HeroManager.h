#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define TOWER_POS_LAYER_LVL 5       // 塔坐标的层次
#define TOWER_BORDER_LAYER_LVL 8    // 炮台的层次
#define TOWER_LAYER_LVL 10          // 塔的层次

class PosBase;
#include "TowerBorder.h"
#include "TowerPos.h"
class HeroManager : public Node {
public:
	HeroManager();
	~HeroManager();
	static HeroManager* createWithLevel(int iCurLevel);
	bool initWithLevel(int iCurLevel);
	void logic(float dt, Vector<Monster*> monsterList);
private:
	/* 存放所有塔的坐标对象 */
	Vector<PosBase*> m_towerPosList;

	/* 存放所有炮台对象 */
	Vector<TowerBorder*> m_towerBorderList;

	/* 创建炮台 */
	void createTowerBorder(int iCurLevel);

	/* 给定坐标，生成塔坐标对象 */
	void createTowerPos(Point pos);

	/* 找到被单击的炮台对象 */
	TowerBorder* findClickTowerBorder(Point pos);

	
};
