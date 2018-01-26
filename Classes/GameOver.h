#pragma once
#include "cocos2d.h"
USING_NS_CC;

class GameOver :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameOver);
private:
	void backToTollgateSelectScene(float dt);
};