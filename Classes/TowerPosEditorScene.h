#pragma once
#include "cocos2d.h"
USING_NS_CC;

class TowerPosEditorScene : public Layer {
public:
	TowerPosEditorScene();
	~TowerPosEditorScene();

	static Scene*createScene();
	virtual bool init();
	CREATE_FUNC(TowerPosEditorScene);
};