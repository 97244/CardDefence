#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define TOWER_POS_LAYER_LVL 5       // ������Ĳ��
#define TOWER_BORDER_LAYER_LVL 8    // ��̨�Ĳ��
#define TOWER_LAYER_LVL 10          // ���Ĳ��

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
	/* ������������������ */
	Vector<PosBase*> m_towerPosList;

	/* ���������̨���� */
	Vector<TowerBorder*> m_towerBorderList;

	/* ������̨ */
	void createTowerBorder(int iCurLevel);

	/* �������꣬������������� */
	void createTowerPos(Point pos);

	/* �ҵ�����������̨���� */
	TowerBorder* findClickTowerBorder(Point pos);

	
};
