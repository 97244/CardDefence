#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
#include "HeroManager.h"
#include "MonsterManager.h"
class TollgateMapLayer :public Layer
{
public:
	TollgateMapLayer();
	~TollgateMapLayer();
	CREATE_FUNC(TollgateMapLayer);
	virtual bool init();
	void initData();
private:
	int m_iCurLevel;

	void loadConfig();
	void logic(float dt);

	void createEndPoint();
	void createStartPoint();
	HeroManager* m_heroMgr;
	MonsterManager* m_monsterMgr;
};