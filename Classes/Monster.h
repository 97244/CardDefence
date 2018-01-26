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

	/* ��������ID���������ļ��ж�ȡ�������� */
	static Monster* createFromCsvFileByID(int iMonsterID);
	bool initFromCsvFileByID(int iMonsterID);

	
public:
	/* ���ո�����������ƶ� */
	void moveByPosList(Vector<PosBase*> posList);

private:
	ControllerSimpleMove* m_moveController;	    // �ƶ�������

	CC_SYNTHESIZE(int, m_iLevel, iLevel);       // �ȼ�
	CC_SYNTHESIZE(float, m_fShowTime, fShowTime);   // �����������
	CC_SYNTHESIZE(bool, m_isMoveEnd, isMoveEnd);

protected:
	virtual void onDead() override;
	virtual void onBindSprite() override;
	virtual void onHurt(int iHurtValue) override;
private:
	LoadingBar *m_hPBar;
	int m_iMaxHP;

};