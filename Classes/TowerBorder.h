#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "Entity.h"
#include "Hero.h"
class TowerBorder:public Entity
{
public:
	TowerBorder();
	~TowerBorder();
	CREATE_FUNC(TowerBorder);
	virtual bool init();
	void upgrade();

	bool isClickMe(Point pos);
	void bindHero(Hero *hero);
	Hero *getHero();
	void deleteHero();

	void showTowerOprBtns();
	void deleteOprBtns();
	void resetOprBtns();

	
protected:
private:
	Hero *m_hero;
	bool m_isOprBtnShow;
	Button * m_cancelBtn;
	Button * m_deleteBtn;
	Button * m_upgradeBtn;

	void cancelClick(Ref*pSender, TouchEventType type);
	void deleteClick(Ref*pSender, TouchEventType type);
	void upgradeClick(Ref*pSender, TouchEventType type);
};