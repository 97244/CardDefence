#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCSGUIReader.h"
#include "cocostudio/CocoStudio.h"
using namespace cocos2d::ui;
USING_NS_CC;

class TollgateSelectScene : public Layer {
public:
	static Scene*createScene();
	virtual bool init();
	CREATE_FUNC(TollgateSelectScene);
private:
	void level_1(Ref* targer, TouchEventType type);
	void level_2(Ref* targer, TouchEventType type);
	void level_3(Ref* targer, TouchEventType type);
};