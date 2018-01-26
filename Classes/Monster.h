#pragma once

#include "Entity.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
#define MONSTER_SPEED_INIT 1

class ControllerSimpleMove;
class PosBase;
class Monster : public Entity {
public:
	Monster();
	~Monster();
	CREATE_FUNC(Monster);
	virtual bool init();

	/* 给定怪物ID，从配置文件中读取怪物数据 */
	static Monster* createFromCsvFileByID(int iMonsterID);
	bool initFromCsvFileByID(int iMonsterID);

	
public:
	/* 按照给定的坐标点移动 */
	void moveByPosList(Vector<PosBase*> posList);

private:
	ControllerSimpleMove* m_moveController;	    // 移动控制器

	CC_SYNTHESIZE(int, m_iLevel, iLevel);       // 等级
	CC_SYNTHESIZE(float, m_fShowTime, fShowTime);   // 出场间隔：秒
	CC_SYNTHESIZE(bool, m_isMoveEnd, isMoveEnd);

protected:
	virtual void onDead() override;
	virtual void onBindSprite() override;
	virtual void onHurt(int iHurtValue) override;
private:
	LoadingBar *m_hPBar;
	int m_iMaxHP;

};