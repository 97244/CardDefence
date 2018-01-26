#pragma once
#include "cocos2d.h"
USING_NS_CC;

#define TAG_MAP_LAYER 1
#define TAG_DATA_LAYER 2

class TollgateScene :public Layer
{
public:
	static Scene*createScene();
	virtual bool init();
	CREATE_FUNC(TollgateScene);
};