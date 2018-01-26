#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "TowerPosEditorScene.h"
#include "TollgateScene.h"
#include "TollgateSelectScene.h"
#include "WinScene.h"
#include "GameOver.h"
class SceneManager :public Ref
{
public:
	enum EnumSceneType
	{
		en_TollgateSelectScene,
		en_TollgateScene,
		en_TollgateEditorScene,
		en_WinScene,
		en_GameOverScene,
	};

	static SceneManager*getInstance();

	virtual bool init();
	void changeScene(EnumSceneType enSceneType);
private:
	static SceneManager* m_SceneManager;
};

